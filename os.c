#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>


int NumBowls[20];
sem_t s1;
void *func1();
void *func2();
pthread_mutex_t m1;
int j,n,m,c,a;
int main()

{
	pthread_mutex_init(&m1,NULL);

	printf("enter the no. of bowls");
	scanf("%d",&n);
	sem_init(&s1,2,n);
	sem_init(&s2,2,0);

int i;
for(i=0;i<n;i++){
	NumBowls[i]=rand()%181;
}

printf("enter the no. of mice");
scanf("%d",&m);

printf("enter the no. of cats");
scanf("%d",&c);
	pthread_t th1[m],th2[c];

for(i=0;i<c;i++)
{
	pthread_create(&th1[i],NULL,func1,NULL);
	}
for(j=0;j<m;j++)
{
	pthread_create(&th2[j],NULL,func2,NULL);

}
for(i=0;i<c;i++)
{
	pthread_join(th1[i],NULL);
}
for(j=0;j<m;j++)
{	pthread_join(th2[j],NULL);
}

}
void *func1()
{sem_wait(&s1);
pthread_mutex_lock(&m1);
int bowl=rand()%n;
if( NumBowls[bowl]!=0){
printf("\n cat is eating food : %d . from bowl : %d",NumBowls[bowl],bowl);
NumBowls[bowl]=0;
}
else
printf("\nBowl number %d is not available for cat.",bowl);
sleep(1);
pthread_mutex_unlock(&m1);
sem_post(&s2);
}
void *func2()
{sem_wait(&s2);
pthread_mutex_lock(&m1);
int bowl=rand()%n;
if(NumBowls[bowl]!=0){
printf("\n mouse is eating food : %d. from bowl : %d",NumBowls[bowl],bowl);
NumBowls[bowl]=0;
}
else
printf("\nBowl number %d is not available for mouse.",bowl);
sleep(1);
pthread_mutex_unlock(&m1);
sem_post(&s1);
}

