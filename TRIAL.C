
#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>
#include<time.h>

int level=0,ec_iwd,rep=0,pr=0,ec_iht,lc_x,rc_x,rc_y,frc_x,frc_y,difx,dify,large,carwidth,posn,carheight,left_x,midx,right_x,maxx,i,maxy,horizon_y,dx,dy,l;
double xfact,yfact,incx,incy,dxx,treeheight,treewidth,ftreeheight,ftreewidth,dyy,rt_y,rt_x,incr_rx,incr_ry,incr_lx,incr_ly,r_ht,l_ht,r_wd,l_wd,lt_x,lt_y;

int set()
{
maxy=getmaxy();
maxx=getmaxx();
horizon_y=maxy/2;
midx=maxx/2;
left_x=midx/1.5;
right_x=midx*1.3;
treeheight=horizon_y/4;
treewidth=maxx/64;
//setting the dda values for right tree
rt_x=right_x;
rt_y=horizon_y;
dx=maxx-rt_x;
dy=maxy-rt_y;
l=(dx>dy)?dx:dy;
dxx=(double)dx/l;
dyy=(double)dy/l;

//setting up tree magnification variables
ftreeheight=treeheight*3;
ftreewidth=treewidth*1;
incr_rx=(ftreewidth-treewidth)/(maxx-right_x);
incr_ry=(ftreeheight-treeheight)/(maxy-horizon_y);
incr_lx=(ftreewidth-treewidth)/(maxx-right_x);
incr_ly=(ftreeheight-treeheight)/(maxy-horizon_y);
r_ht=treeheight;
r_wd=treewidth;
l_ht=(ftreeheight-treeheight)/2;
l_wd=(ftreewidth-treewidth)/2;
//setting initial co-ordinates of left tree
lt_x=left_x/2;
lt_y=horizon_y+((maxy-horizon_y)/2);

//Setting players car width and height
carwidth=maxx/8;
carheight=horizon_y/3;
posn=maxx/2;

//setting up right side enemys car
rc_x=(midx+right_x)/2;
lc_x=(left_x+midx)/2;
rc_y=horizon_y;
frc_x=midx+(midx/2);
frc_y=maxy;
difx=frc_x-rc_x;
dify=frc_y-rc_y;
large=(difx>dify)?difx:dify;
incx=(float)difx/large;
incy=(float)dify/large;
//setting up enemy cars height and width
ec_iwd=carwidth/3;
ec_iht=carheight/10;

//setting up magnification variables of enemy car
xfact=(double)((carwidth/1.5)-ec_iwd)/(frc_x-rc_x);
yfact=(double)((carheight*1)-ec_iht)/(maxy-horizon_y);
//printf("%d / %d, %2f",caheight-ec_iht,maxy-horizon_y,yfact);

return 0;
}


int drawroad()
{
line(0,horizon_y,maxx,horizon_y);
line(midx,horizon_y,midx,maxy);
line(left_x,horizon_y,0,maxy);
line(right_x,horizon_y,maxx,maxy);
return 0;
}

int drawtree(int x,int y,int clr,double height,double width)
{
float floor,one_inner,baseheight,bspace;
int h=height,w=width;
if(clr==1)
{
setcolor(15);
}
else
{
setcolor(0);
}

//rectangle(x-width,y-height,x+width,y);

bspace=(w*2)/3;
baseheight=h/4;
one_inner=w*2/3;
floor=h/8;



line(x-w+bspace,y,x+w-bspace,y);
line(x-w+bspace,y,x-w+bspace,y-baseheight);
line(x-w+bspace,y-baseheight,x-w,y-baseheight);
line(x-w,y-baseheight,x-w+one_inner,y-baseheight-2*floor);
line(x-w+one_inner,y-baseheight-2*floor,x-w+(w/10),y-baseheight-floor);
line(x-w+(w/10),y-baseheight-floor,x,y-h);
line(x,y-h,x+w-(w/10),y-baseheight-floor);
line(x+w-(w/10),y-baseheight-floor,x+w-one_inner,y-baseheight-2*floor);
line(x+w-one_inner,y-baseheight-2*floor,x+w,y-baseheight);
line(x+w,y-baseheight,x+w-bspace,y-baseheight);

line(x+w-bspace,y,x+w-bspace,y-baseheight);

setcolor(15);
return 0;
}
int sidetrees()
{
rt_x+=dxx;
rt_y+=dyy;
lt_x-=dxx;
lt_y+=dyy;
r_ht+=incr_ry;
r_wd+=incr_rx;
l_ht+=incr_ly;
l_wd+=incr_lx;

incr_rx+=0.001;
incr_ry+=0.001;

incr_lx+=0.001;
incr_ly+=0.001;

if(rt_x>=(maxx-r_wd))
{
rt_x=right_x;
rt_y=horizon_y;
r_ht=treeheight;
r_wd=treewidth;
incr_rx=(ftreewidth-treewidth)/(maxx-right_x);
incr_ry=(ftreeheight-treeheight)/(maxy-horizon_y);
}

if(lt_x<=l_wd)
{
lt_x=left_x;
lt_y=horizon_y;
l_ht=treeheight;
l_wd=treewidth;
incr_lx=(ftreewidth-treewidth)/(maxx-right_x);
incr_ly=(ftreeheight-treeheight)/(maxy-horizon_y);
}
return 0;
}
//Drawing our cAAAR
int mycar(int x,int clr)
{
int tirewidth,rx,lx,y,h,w;
float dy,aarsa_y,l_aarsa_x,r_aarsa_x;
if(clr==1)
{setcolor(15);}
else
{setcolor(0);}
//outtextxy(20,2,"Your points:%d %d %d",level,rep,pr);
//rectangle(x-carwidth,maxy-carheight-5,x+carwidth,maxy-5);

y=maxy-5;
h=carheight;
w=carwidth;
//rectangle(x-w,y-h,x+w,y);
rectangle(0,0,getmaxx(),getmaxy());

dy=y-(h*2/3);
rx=x-(w*3/4);
lx=x+(w*3/4);
tirewidth=w/5;
r_aarsa_x=x+w;
aarsa_y=y-(h/3);
l_aarsa_x=x-w;

line(r_aarsa_x,aarsa_y,r_aarsa_x+tirewidth,aarsa_y-tirewidth);
line(r_aarsa_x+tirewidth,aarsa_y-tirewidth,r_aarsa_x,aarsa_y-tirewidth);

line(l_aarsa_x,aarsa_y,l_aarsa_x-tirewidth,aarsa_y-tirewidth);
line(l_aarsa_x-tirewidth,aarsa_y-tirewidth,l_aarsa_x,aarsa_y-tirewidth);


line(rx,dy,lx,dy);
line(x-w,y-(h/3),rx,dy);
line(x+w,y-(h/3),lx,dy);
line(x-w,y-(h/3),rx,y-h);
line(x+w,y-(h/3),lx,y-h);
line(rx,dy,rx,y-h);
line(lx,dy,lx,y-h);
line(rx,y-h,lx,y-h);
//transformers
line(x-w,y-(h/10),x-w,y-(h/3));
line(x-w,y-(h/10),x-w+(w/10),y-(h/10));
line(x-w+(w/10),y-(h/10),x-w+(w/10),y);
line(x-w+(w/10),y,x-w+(w/10)+tirewidth,y);
line(x-w+(w/10)+tirewidth,y,x-w+(w/10)+tirewidth,y-(h/10));
line(x-w+(w/10)+tirewidth,y-(h/10),x+w-(w/10)-tirewidth,y-(h/10));

// transformers 2
line(x+w,y-(h/10),x+w,y-(h/3));
line(x+w,y-(h/10),x+w-(w/10),y-(h/10));
line(x+w-(w/10),y-(h/10),x+w-(w/10),y);
line(x+w-(w/10),y,x+w-(w/10)-tirewidth,y);
line(x+w-(w/10)-tirewidth,y,x+w-(w/10)-tirewidth,y-(h/10));
line(x+w,y-(h/10),x-w,y-(h/10));
line(x+w,y-(h/3),x-w,y-(h/3));














setcolor(15);
return 0;
}

int draw_enemycar(int x, int y,int height,int width,int clr)
{
int tireheight,tirewidth,dy,h,w;
float vargap,rgap,topgap;
if(clr==1)
{setcolor(15);}
else
{setcolor(0);}
//rectangle(x-width,y-height,x+width,y);

h=height;
w=width;
//rectangle(x-w,y-h,x+w,y);
rectangle(0,0,getmaxx(),getmaxy());


dy=h/2;
topgap=(w*40/100);
rgap=(w*25/100);
vargap=(w*45/100);


tirewidth=w/5;
tireheight=h/7;

// windshield
line(x-w+rgap,y-((h*2)/3),x+w-rgap,y-((h*2)/3));
line(x-w+rgap,y-((h*2)/3),x-w+vargap,y-h+(h/10));
line(x-w+vargap,y-h+(h/10),x+w-vargap,y-h+(h/10));
line(x+w-vargap,y-h+(h/10),x+w-rgap,y-((h*2)/3));

//headlights
circle(x-w+rgap,y-dy,(tireheight/2));
circle(x+w-rgap,y-dy,(tireheight/2));

//carborator stuff

rectangle(x-w+rgap+(tireheight/2),y-(tireheight*3),x+w-rgap-(tireheight/2),y-tireheight-(h/10));







line(x-w+topgap,y-h,x-w,y-dy);
line(x-w+topgap,y-h,x+w-topgap,y-h);
line(x+w-topgap,y-h,x+w,y-dy);
line(x+w,y-dy,x+w,y-tireheight);
line(x+w,y-tireheight,x+w-(w/5),y-tireheight);
line(x+w-(w/5),y-tireheight,x+w-(w/5),y);
line(x+w-(w/5),y,x+w-(w/5)-tirewidth,y);
line(x+w-(w/5)-tirewidth,y,x+w-(w/5)-tirewidth,y-tireheight);
line(x+w-(w/5)-tirewidth,y-tireheight,x-w+(w/5)+tirewidth,y-tireheight);
line(x-w+(w/5)+tirewidth,y-tireheight,x-w+(w/5)+tirewidth,y);
line(x-w+(w/5)+tirewidth,y,x-w+(w/5),y);
line(x-w+(w/5),y,x-w+(w/5),y-tireheight);
line(x-w+(w/5),y-tireheight,x-w,y-tireheight);
line(x-w,y-tireheight,x-w,y-dy);
line(x-w,y-tireheight,x+w,y-tireheight);















setcolor(15);
return 0;
}
//welcome
int welcome(int color)
{
setcolor(color);
settextstyle(3,0,6);
outtextxy(100,2," Car Extreme Racing ");
settextstyle(6,0,2);
outtextxy(20,80," Use a and d Keys To go Left and Right");
outtextxy(20,140,"Press esc to Escape Any Time");
outtextxy(20,160,"Press Any Key To Continue ");
return 0;
}
int game_over()
{
clrscr();
setcolor(15);
settextstyle(3,0,5);
outtextxy(50,2,"you just hit a car...");
outtextxy(50,75," Game Over...!!!!!! ");
/*settextstyle(6,0,2);
outtextxy(20,80,"");
outtextxy(20,140,"Press esc to Escape Any Time");*/
outtextxy(20,160,"Press Any Key To Continue ");
return 0;
}

int chk_cont(int n)
{
if(n==pr)
{
rep++;
}
else
{
rep=0;
pr=n;
}
if(rep>rand()%3)
{
n=(n==0)?1:0;
rep=0;
}
return n;
}

int main(void)
{
int del=10,sensitivity=5,gm,gd=DETECT,car_ok=1,side;
char ch,out;
double ecwd,echt,ecx,ecy;
srand(time(NULL));
side=rand()%2;
initgraph(&gd,&gm,"C:\\turboc3\\bgi");
set();

ecx=(side==0)?lc_x:rc_x;
ecy=rc_y;
ecwd=ec_iwd;
echt=ec_iht;
welcome(15);
ch=getch();
if(ch==27) exit(0);
welcome(0);

while(car_ok)
{
rectangle(0,0,maxx,maxy);
drawroad();
drawtree(rt_x,rt_y,1,r_ht,r_wd);
drawtree(lt_x,lt_y,1,l_ht,l_wd);
mycar(posn,1);
draw_enemycar(ecx,ecy,ecwd,echt,1);

delay(del);
draw_enemycar(ecx,ecy,ecwd,echt,0);
mycar(posn,0);
drawtree(rt_x,rt_y,0,r_ht,r_wd);
drawtree(lt_x,lt_y,0,l_ht,l_wd);
sidetrees();

if(side==1)
{
ecx=ecx+incx;
}
else
{
ecx-=incx;
}
ecy+=incy;
ecwd+=xfact;
echt+=yfact;
if(ecy==maxy)
{
side=rand()%2;
side=chk_cont(side);
ecx=(side==0)?lc_x:rc_x;
ecy=rc_y;
ecwd=ec_iwd;
echt=ec_iht;
level++;
if(level>=10&&del>0)
{
del--;
sensitivity+=3;
level=0;
}
}
if(kbhit())
{
	ch=getch();
	if(ch==97)
	{
	posn-=sensitivity;
																																																																																																																																	}
	else if(ch==100)
	{
	posn+=sensitivity;
	}
	else if(ch==27)
	{
	car_ok=0;
	}
 //	printf(" %d,%d",maxx,posn);
}
//is_car_damaged();

if((posn<carwidth)||(posn>maxx-carwidth)||(ecy>maxy-6-carheight&&(((ecx+ecwd>posn-carwidth)&&(ecx-ecwd<posn+carwidth))||((ecx-ecwd<posn+carwidth)&&(ecx+ecwd>posn-carwidth)))))
{
car_ok=0;
game_over();
}
}
loop:out=getch();
	if(out==97||out==100)
	{
	goto loop;
	}
	closegraph();
	return 0;
}

