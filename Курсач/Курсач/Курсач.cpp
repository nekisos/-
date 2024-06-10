#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <malloc.h>
#include <clocale>
#include <windows.h>
using namespace std;
using namespace System;
using namespace System::IO;
#define ENTER 13
#define ESC 27
#define UP 72
#define DOWN 80
#define HOME 71
#define END 79

int NC;
struct z {
char name[30];
char pol[20];
char rab[20];
char data[11];
char skot[20];
long zp;
long kap;
};
struct sp {
char fio[20];
long zp;
long kap;
struct sp* pred;
struct sp* sled;
} *spisok;

int menu(int);
void alfavit(struct z*,int);
void hard(struct z*,int);
void sum(struct z*,int);
void rabb(struct z*,int);
void vstavka(struct z*,char*,int);
void st60(struct z*,int);
void kid(struct z *,int);
void skot(struct z *,int);
void maxx(struct z*,int);
void alfalist(struct z*,int);
void text_data(char *,char *);
void listing(struct z*,int);
void diagram(struct z*,int);
int main(array<System::String ^> ^args)
{
char dan[8][60]={
"Самая высокая з/п деревни Романово                       ",
"Прямой и обратный алфавитный список жителей              ",
"Самый пожилой житель деревни                             ",
"Список жителей, чья з/п больше выше указанной суммы      ",
"Количество человек, введенного пола, имеющих свой скот   ",
"Диаграмма. Процентное соотношение зарплат населения      ",
"Первые мужчина и женщина,у которых одинаковые сбережения ",  
 "Выход                                                     "
};
char BlankLine[ ]="                                                           ";
int NC;
int i,n;
FILE *in;
struct z *villagers;
setlocale(LC_ALL,"Russian");
Console::CursorVisible::set(false);
Console::BufferHeight=Console::WindowHeight;
Console::BufferWidth=Console::WindowWidth;
if((in=fopen("fam.txt","r"))==NULL)
{
printf("\nФайл fam.txt не открыт !");
getch(); exit(1);
}
fscanf(in,"%d",&NC);
villagers=(struct z*)malloc(NC*sizeof(struct z));
for(i=0;i<NC;i++)
fscanf(in,"%s%s%s%s%s%ld%ld",villagers[i].name,
villagers[i].pol, villagers[i].rab,
villagers[i].data,villagers[i].skot,&villagers[i].zp,&villagers[i].kap);
for(i=0;i<NC;i++)
printf("\n%-20s %-20s %-20s %-20s %-20s %7ld %7ld",
villagers[i].name,
villagers[i].pol, villagers[i].rab,
villagers[i].data,villagers[i].skot,villagers[i].zp,villagers[i].kap);
getch();
while(1)
{
Console::ForegroundColor=ConsoleColor::Red;
Console::BackgroundColor=ConsoleColor::Blue;
Console::Clear();
Console::ForegroundColor=ConsoleColor::Blue;
Console::BackgroundColor=ConsoleColor::Red;
Console::CursorLeft=10;
Console::CursorTop=4;
printf(BlankLine);
for(i=0;i<7;i++)
{
Console::CursorLeft=10;
Console::CursorTop=i+5;
printf(" %s ",dan[i]);
}
Console::CursorLeft=10;
Console::CursorTop=12;
printf(BlankLine);
n=menu(8);
switch(n) {
case 1: maxx(villagers,NC);break;
case 2: alfalist(villagers,NC);break;
case 3: st60(villagers,NC);break;
case 4: listing(villagers,NC);break;
case 5: skot(villagers,NC);break;
case 6: diagram(villagers,NC);break;
case 7: hard(villagers,NC);break;
case 8: exit(0);
}
}
return 0;
}
int menu(int n)
{
int NC;
char dan[8][60]={
"Самая высокая з/п деревни Романово                       ",
"Прямой и обратный алфавитный список жителей              ",
"Самый пожилой житель деревни                             ",
"Список жителей, чья з/п больше выше указанной суммы      ",
"Количество человек, введенного пола, имеющих свой скот   ",
"Диаграмма. Процентное соотношение зарплат населения      ",
"Первые мужчина и женщина,у которых одинаковые сбережения ",  
 "Выход                                                     "
};
char BlankLine[ ]="                                                           ";
int y1=0,y2=n-1;
char c=1;
while (c!=ESC)
{
switch(c) {
case DOWN: y2=y1; y1++; break;
case UP: y2=y1; y1--; break;
case ENTER: return y1+1;
case HOME: y2=y1;y1=0;break;
case END: y2=y1; y1=6; break;
}
if(y1>n-1){y2=n-1;y1=0;}
if(y1<0) {y2=0;y1=n-1;}
Console::ForegroundColor=ConsoleColor::Green;
Console::BackgroundColor=ConsoleColor::Yellow;
Console::CursorLeft=11;
Console::CursorTop=y1+5;
printf("%s",dan[y1]);
Console::ForegroundColor=ConsoleColor::Blue;
Console::BackgroundColor=ConsoleColor::Red;
Console::CursorLeft=11;
Console::CursorTop=y2+5;
printf("%s",dan[y2]);
c=getch();
} // конец while(c!=ESC)...
exit(0);
}


void sum(struct z *villager,int NC)
{
int i,k=0;
for(i=0;i<NC;i++)
if (strcmp(villager[i].name,"")==1)
k++;
Console::ForegroundColor=ConsoleColor::White;
Console::BackgroundColor=ConsoleColor::Magenta;
Console::CursorLeft=10;
Console::CursorTop=15;
printf("Численность населения деревни Романово : %d",k);printf(" человек");
getch();
}
void skot(struct z *villager,int NC)
{
int i,k=0;
Console::ForegroundColor=ConsoleColor::Yellow;
Console::BackgroundColor=ConsoleColor::Magenta;
Console::Clear();
printf("Введите пол человека : ");
char poll[40];
SetConsoleCP(1251);
gets(poll);
SetConsoleCP(866);
for(i=0;i<NC;i++)
if (strcmp(villager[i].pol,poll)==0)
	if (strcmp(villager[i].skot,"Скот_есть")==0)
		k++;
Console::ForegroundColor=ConsoleColor::White;
Console::BackgroundColor=ConsoleColor::Magenta;
Console::CursorLeft=10;
Console::CursorTop=15;
printf("Жителей %s, имеющие свой скот : %d ",poll,k);
getch();
}

void rabb(struct z *villager,int NC)
{
int i,h=0,k=0;
for(i=0;i<NC;i++)
if (strcmp(villager[i].rab,"Без_работы")==0)
k++;
Console::ForegroundColor=ConsoleColor::White;
Console::BackgroundColor=ConsoleColor::Magenta;
Console::CursorLeft=10;
Console::CursorTop=15;
printf("Жители, которые не имеют работу");
printf(" Всего : %d",k);
getch();
}
void text_data(char *s,char *sd)
{
char s0[3],month[12][9]={
"января","февраля","марта","апреля","мая","июня",
"июля","августа","сентября","октября","ноября","декабря"};
strcpy(s,sd+8);
strcat(s," ");
strncpy(s0,sd+5,2); s0[2]=0;
strcat(s,month[ atoi(s0)-1]);
strcat(s," ");
strncat(s,sd,4);
return;
}
void st60(struct z* villager,int NC)
{
int i;
char s[17];
struct z* best=villager;
for(i=1;i<NC;i++)
if (strcmp(villager[i].data,best->data)<0)
	best=&villager[i];
		text_data(s,best->data);
Console::ForegroundColor=ConsoleColor::White;
Console::BackgroundColor=ConsoleColor::Magenta;
Console::CursorLeft=10;
Console::CursorTop=15;
Console::CursorLeft=10;
Console::CursorTop=16;
printf("Самый пожилой житель деревни : %s",best->name);
Console::CursorLeft=10;
Console::CursorTop=17;
printf("Он/Она родилась : %s ",s);
getch();

}
/*void alfalist(struct z* villager)
{
int i;
struct sp* nt,*mt;
Console::ForegroundColor=ConsoleColor::Black;
Console::BackgroundColor=ConsoleColor::Gray;
Console::Clear();
printf("\n Алфавитный список жителей деревни");
printf("\n ===============================\n");
if(!spisok)
for(i=0;i<NC;i++)
vstavka(villager,villager[i].name);
Console::Clear();
for(nt=spisok; nt!=0; nt=nt->sled)
printf("\n %-20s %ld",nt->fio,nt->zp);
getch();
}*/
void vstavka(struct z* villager,char* fio,int NC)
{
int i;
struct sp *nov,*nt,*z=0;
for(nt=spisok; nt!=0 && strcmp(nt->fio,fio)<0; z=nt, nt=nt->sled);
if(nt && strcmp(nt->fio,fio)==0) return;
nov=(struct sp *) malloc(sizeof(struct sp));
strcpy(nov->fio,fio);
nov->sled=nt;
nov->zp=0;
for(i=0;i<NC;i++)
if(strcmp(villager[i].name,fio)==0)
nov->zp+=villager[i].zp;
if(!z) spisok=nov;
else z->sled=nov;
return;
}
void maxx(struct z* villager,int NC)
{
int i=0; struct z best;
strcpy(best.name,villager[0].name);
best.zp=villager[0].zp;
for(i=1;i<NC;i++)
if (villager[i].zp>best.zp)
{
strcpy(best.name,villager[i].name);
best.zp=villager[i].zp;
}
Console::ForegroundColor=ConsoleColor::White;
Console::BackgroundColor=ConsoleColor::Magenta;
Console::CursorLeft=10;
Console::CursorTop=15;
printf("Максимальная з/п %ld рублей",best.zp);
Console::CursorLeft=10;
Console::CursorTop=16;
printf("Зарабатывает : %s",best.name);
getch();
}

void diagram(struct z *villager,int NC)
{
struct sp *nt;
int len,i,NColor;
long sum = 0 ;
char str1[20];
char str2[20];
System::ConsoleColor Color;
Console::ForegroundColor=ConsoleColor::White;
Console::BackgroundColor=ConsoleColor::DarkYellow;
Console::Clear();
for(i=0;i<NC;i++) sum = sum+villager[i].zp ;
if(!spisok)
for(i=0;i<NC;i++)
vstavka(villager,villager[i].name,NC);
Color=ConsoleColor::Black; NColor=0;
printf("   ");
printf("Процентное соотношение зарплат населения");
for(nt=spisok,i=0; nt!=0; nt=nt->sled,i++)
{
sprintf(str1,"%s",nt->fio);
sprintf(str2,"%3.1f%%",(nt->zp*100./sum));
Console::ForegroundColor=ConsoleColor::White;
Console::BackgroundColor= ConsoleColor::DarkYellow;
Console::CursorLeft=5; Console::CursorTop=i+1;
printf(str1);
Console::CursorLeft=20;
printf("%s",str2);
Console::BackgroundColor=++Color; NColor++;
Console::CursorLeft=30;
for(len=0; len<nt->zp*100/sum; len++) printf(" ");
if(NColor==14)
{ Color=ConsoleColor::Black; NColor=0; }
}
getch();
return ;
}
void listing(struct z* villager,int NC)
{
int i,vvod;
Console::ForegroundColor=ConsoleColor::Yellow;
Console::BackgroundColor=ConsoleColor::Magenta;
Console::Clear();
printf("Введите указанную сумму : ");
scanf("%ld",&vvod);
struct z* nt;
Console::ForegroundColor=ConsoleColor::Yellow;
Console::BackgroundColor=ConsoleColor::Magenta;
Console::Clear();
printf("\n\r Список жителей, чья з/п больше выше %d тыс. рублей",vvod);
printf("\n\r=====================================================\n\r");
for(i=0,nt=villager;i<NC;nt++,i++)
if (nt->zp>vvod && strcmp(nt->rab,"Работает")==0)
printf("\n\r %-20s %ld руб.",nt->name,nt->zp);
getch();
}
void hard(struct z* villager,int NC)
{
int i,j;
int flag = 0;
Console::ForegroundColor=ConsoleColor::Yellow;
Console::BackgroundColor=ConsoleColor::Magenta;
Console::Clear();
for(i=0;i<NC;i++)
{
	for (j = i+1; j < NC; j++)
		{
		if (strcmp(villager[i].pol, villager[j].pol) && (villager[i].kap == villager[j].kap))
		{
			printf("\n  Инициалы: %s, Пол : %s, Капитал: %ld, --- Инициалы: %s, Пол: %s, Капитал: %ld.",villager[i].name,villager[i].pol,villager[i].kap,villager[j].name, villager[j].pol,villager[j].kap);
			flag = 1;
			break;}
		}
		if (flag == 1) {break;}
		if (flag == 0) {printf("Таких совпадений нет!"); break;}
}
getch();
}

void vstavka2(char* fio, int zp,int NC) //вставка в список
{
struct sp *nov,*nt,*z=0;
for(nt=spisok; nt!=0 && strcmp(nt->fio,fio)<0; z=nt, nt=nt->sled);
if(nt && strcmp(nt->fio,fio)==0) return;
nov=(struct sp *) malloc(sizeof(struct sp));
strcpy(nov->fio,fio);
nov->zp=zp;
nov->pred=z;
nov->sled=nt;
if(!z) spisok=nov;
else z->sled=nov;
if(nt) nt->pred=nov;
return;
}
void alfalist(struct z* villagers,int NC) //Формирование списка
{
int i,n;
struct sp *nt, *mt;
n=NC;
Console::ForegroundColor=ConsoleColor::Yellow;
Console::BackgroundColor=ConsoleColor::Magenta;
Console::Clear();
printf("\n\t Алфавитный список");
printf("\t\t\t\tОбратный список");
printf("\n\t");
printf("\t\n");
if(!spisok)
for(i=0;i<NC;i++)
vstavka2(villagers[i].name, villagers[i].zp,NC);
for(nt=spisok; nt!=0; nt=nt->sled)
printf("\n\t %-20s %d",nt->fio,nt->zp);
for(nt=spisok, mt=0; nt!=0; mt=nt, nt=nt->sled);
Console::CursorTop=4;
for(nt=mt,i=0;nt!=0; i++,nt=nt->pred){
Console::CursorLeft=56;
printf("%-20s %d",nt->fio,nt->zp);
Console::CursorTop+=1;
}
getch();
}
