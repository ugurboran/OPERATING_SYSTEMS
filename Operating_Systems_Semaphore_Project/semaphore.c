//Ahmet Melih TÜRKMEN - Uður BORAN
#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */
#include <errno.h>      /* Errors */
#include <stdio.h>      /* Input/Output */
#include <stdlib.h>     /* General Utilities */
#include <pthread.h>    /* POSIX Threads */
#include <string.h>     /* String handling */
#include <semaphore.h>  /* Semaphore */
#include <fcntl.h>

int seatnumber = 3;
sem_t * sem;
sem_t * awroom;



int TATurn(){
	
	
	//While someone comes to TA office free seat is increasing for another student
	//which is waiting in outside. After TA solves question looking if someone is waiting
	//if not he is sleeping. After wake up if no one waits he is going.If someone is waiting
	// access wait room is setting by TA to 1 for another student comes in to office.
	
	while(1){
		
	sem_post(sem);
	seatnumber = seatnumber +1;
	
	sleep(1);
	
	printf("Question solved\n");
	
	if(seatnumber == 3 ){
		printf("Sleeping time\n");
		sleep(8);
		
		if(seatnumber == 3){
			return 0;
		}
	}
	
	sem_post(awroom);
		
	
}
}	

int StudentTurn(){
	
	//Students are first looking if free seats are avaible or not. If it is avaible
	//they are sitting one of them and decreasing number of free seats and waits for
	//TA signal for comes in to TA office. But there is a little bit sleep time to
	//new comers cant enter TA Room before waiting students. If no seat avaible
	//they are waiting 2 sec and come back again.
	
	while(1){
	
	if(seatnumber>0){
		seatnumber = seatnumber -1;
		sleep(5);
		sem_wait(sem);
		sem_wait(awroom);
		return 0;
		
	}
	
	else{
		sleep(2);
	}		
	
}	
}

//Created a student which comes very late to check all functionalities are working correct.
// Other things are same as normal students.

int LateStudent(){
	while(1){
		
		sleep(12);
	
	if(seatnumber>0){
		seatnumber = seatnumber -1;
		sleep(2);
		sem_wait(sem);
		sem_wait(awroom);
		printf("Late Student Finished\n");
		return 0;
		
	}
	
	else{
		sleep(9);
	}		
	
}	
}	

//Creating student and TA threads and necessary semaphores.


int main(){

	pthread_t std;
	pthread_t TA;
	
	sem = sem_open("firstsema", O_CREAT, 0644, seatnumber);
	awroom = sem_open("firstsema", O_CREAT, 0644, 1);
	
	pthread_create(&TA,NULL,(void*)&TATurn,NULL);
	int k=0;
	while(k<5){
		pthread_create(&std,NULL,(void*)&StudentTurn,NULL);
		k++;
	}
	
	pthread_create(&std,NULL,(void*)&LateStudent,NULL);
	
	
	pthread_join(TA,NULL);
	printf("Finished\n");
	return 0;
	
	
}
