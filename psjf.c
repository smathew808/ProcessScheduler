/* ******************************************************************* *
* PSJF_base.c:                                                         *
*                                                                      *
* This C program simulates a short-term process scheduler for          *
* "Premptive Priority Non-Preemptive SJF (Shortest Job First)"         *
* short-term process scheduling algorithm.                             *
*                                                                      *
* This program takes a two-dimensional array ("process_list") that     *
* define each process "i" using the following attributes:              *
*                                                                      *
*   REQUIRED PARAMETERS (for Process i) ------------------------------ *
*   (0) process_list[i][0] = 0;     // process ID                      *
*   (1) process_list[i][1] = 1;     // start time                      *
*   (2) process_list[i][2] = 15;    // total execution time            *
*   (3) process_list[i][3] = 9;     // process priority                *
*   ------------------------------------------------------------------ *
*                                                                      *
* Each process is defined in a module, "initialize_process_list".      *
* For the process priority, the smaller the priority number is, the    *
* higher the priority is (i.e., '0' means the highest priority).       *
*                                                                      *
* The outputs from this simulator are:                                 *
*   (a) process start time (when it starts running)                    *
*   (b) how long a process is executed (in time units)                 *
*   (c) stop time (completed or preempted time)                        *
*   (d) - optional - if it is completed or preempted                   *
*                                                                      *
* Compile: cc PSJF_base.c                                              *
*                                                                      *
* Host: os.cs.siue.edu                                                 *
*                                                                      *
* Last Updated at: 19:12, Januray 12, 2018                             *
*                                                                      *
* Place: Edwardsville, IL                                              *
*                                                                      *
* ******************************************************************** */
#include <string.h>                    // for strerror()               //
#include <stdio.h>                     // for printf                   //
#include <stdlib.h>

#define NUM_PROCESSES      10          // Number of processes          //
#define TRUE               1           // TRUE label                   //
#define FALSE              0           // FALSE label                  //

#define CANTRUN            9999		   // this is a junk value that says that this id cant run for this round for picking the next process 		  

#define NUM_ELEMENTS       4           // the number of elements       //

/* Prototype --------------------------------------------------------- */
void initialize_process_list(void);  // initialize the process definitions
int  find_earliest_process(void);    // find the very first process to begin with
									 //int  actual_exec_time1(int);        // the scheduled execution time for the very first process

									 int  next_process(int processorId);             // find the next process to run
									 int  actual_exec_time1(int processorId);
									 int  actual_exec_time2(int processorId);        // the scheduled execution time of the next process to execute

									 int  are_all_done(void);             // TRUE if all processes completed
									 // FALSE otherwise

									 /* Global variables --------------------------------------------------- */
int current_time;                    // the current time     //
									 // YOU CAN ADD YOUR GLOBAL VARIABLES
//
//int processID; //this is the ID for each process in the 2d array, which is index [i][0], this will break the tie
//int processStartTime; //this is the value that holds the process start time, which is index [i][1]
//int processExecutiontime; //this value holds the execution time for each process. this is at index [i][2]
//int processExecutionPriority; //this value holds the priority for the process to be executed, where 0 is the highest priority value, which is at index [i][3]
//

							  /* Function prototypes ------------------------------------------------ */
int process_list[10][4];  // the thread list      //
						  // YOU CAN ADD YOUR FUNCTIONS

//this array will be populated with bools first, all with false. then as each process runs, then the values will change in each while loop itteration
int hasProcessRanYetList[10] = { FALSE };

//array for the all the processes that are ready to be chosen for the next processs
int processesReadyToRun[10];

						  /* the MAIN ----------------------------------------------------------- */
void main(void)
{
	int                 i;       // loop counter

	int next_proc_to_run;        // The process ID for the next process to run
	int all_processes_completed; // the "completion" flag
	int exec_time;

 

	

	//processStartTime = 1;
	// YOU CAN ADD YOUR VARIABLES ------------------------------------

	// worry about how to find the first process to run
	// how do i select a process? run through 3 while or for loops i suppose or could think of better way
	//  the 3 while or for loops will include the selection of looking for shortest start time, if it finds more than 
	// 1 start time that is equal, then proceeed to next if statement which will compare the execution priority
	// if it finds 1 process that has the same execution priority, then move on to third while
	// once here will look for the shortest execution time. next if that doesnt work then pick between
	// the lower user IDs it should work otherwise im dead
	// also ask about what to do about the other functions that are dot dot dot, comment those out when running? or should i being using those too




	// initialzie the current time -----------------------------------
	current_time = 1;

	// initialzie the thread list ------------------------------------
	initialize_process_list();

	// find the first thread to run ----------------------------------
	next_proc_to_run = find_earliest_process();


	// set the execution time length (Phase 2 and 3) -----------------
	exec_time = actual_exec_time1(next_proc_to_run);

	current_time = process_list[next_proc_to_run][1];
	// advance the simulation time -----------------------------------
	//sleep(exec_time);                         // skip the time


	printf("the first process is sucessfully identified ...\n");
	printf("the first process to start: %d\n", next_proc_to_run);
	printf("start time: %d\n", process_list[next_proc_to_run][1]);

	


	// display the progress ---------------------------------------
	printf("Process %d starts at time %d ...\n",
		next_proc_to_run, current_time);

	// display the running time -----------------------------------
	printf("    process %d runs for %d time units ...\n",
		next_proc_to_run, exec_time);

	current_time = exec_time + current_time;

	//display the finished time
	printf("    process %d finishes at %d ...\n",
		next_proc_to_run, current_time);

// repeat until all the processes are completed ------------------
	do
	{
		// find the next process to run -------------------------------
		next_proc_to_run = next_process(next_proc_to_run);

		// find the execution duration of the next thread -------------
		exec_time = actual_exec_time2(next_proc_to_run);


		// display the progress ---------------------------------------
		printf("Process %d starts at time %d ...\n",
			next_proc_to_run, current_time);

		// display the running time -----------------------------------
		printf("    process %d runs for %d time units ...\n",
			next_proc_to_run, exec_time);


		// update the current time ------------------------------------
		//sleep(exec_time);                         // skip the time
		current_time = current_time + exec_time;     // update the clock

		//display the finished time
		printf("    process %d finishes at %d ...\n",
			next_proc_to_run, current_time);

													 // check if all the processes are completed -------------------
		all_processes_completed = are_all_done();

	} while ((all_processes_completed == FALSE) && (next_proc_to_run >= 0));

	system("pause");
}

// THE END OF MODULE MAIN ====================================================

/* actual_exec_time1 --------------------------------------------------- */
int actual_exec_time1(int processorId)
{
	int time_to_run;               // how long more can I use the processor

	time_to_run = process_list[processorId][2];

	return(time_to_run);
}
// actual_exec_time1 ///////////////////////////////////////////////////////


/* actual_exec_time2---------------------------------------------------- */
int actual_exec_time2(int processorId)
{
	int more_execution_time;       // at least one unit time

	more_execution_time = process_list[processorId][2];

	return(more_execution_time);
}
// actual_exec_time2 ///////////////////////////////////////////////////////



/* next_process -------------------------------------------------------- *
*                                                                        *
* This module finds the process that should be executed next.            *
* This module returns the process ID of the next process that should be  *
* executed.                                                              *
* ---------------------------------------------------------------------- */
int next_process(int processorId)
{
	int next_process_ID;   // the ID of the chosen process (final)

	 //initialize the process_id = to first id in the list

	//while the processor id is isn't 0!
	//figure out a way to check if all the processes ran or not
	//while all the items in the list arent false
	
	
	//while the next process is == to a proccess that hasn't ran yet

	//this counter counts up to 10, if it counts up to 10, then increment time by 1 and keep doing it until you reach a time that works
	int cantRunCounter = 0;

	//set to a meaningless value for loop purposes
	int winner = -1;

	next_process_ID = 0;
	
		for (int i = 0; i < NUM_PROCESSES; i++)
		{
			if (processesReadyToRun[i] == CANTRUN)
			{
				cantRunCounter++;

			}

		}


		//check whos start time is smaller in the hasProcessRanYetList's index, that index is the id that process
		
		

		//run through processes to see who has an earlier start time than the other

		if (cantRunCounter == 10)
		{
			for (int i = 0; i < NUM_PROCESSES; i++)
			{
				
				//if the process hasn't ran yet, then set the winner to i'th process
				if ((hasProcessRanYetList[i] == FALSE))
				{
					//winner
					next_process_ID = i;
					current_time = process_list[i][1];

					
					//if the winner's start time is greater than the i's start time, after a couple itterations in the for loop, then set the winner to the new i

									//winner
					if (process_list[next_process_ID][1] > process_list[i][1])
					{
						//winner
						next_process_ID = i;
						current_time = process_list[i][1];
					}
					
				}
				
			}

			
		}

	//if the start time of a process is smaller than the other, then gotta use the smaller start time
	

	//checks whether the start time for the the current proccess id is bigger than the current time, if it is, then change


	while ( (hasProcessRanYetList[next_process_ID] == TRUE) || (process_list[next_process_ID][1] > current_time))
	{
		next_process_ID++;
	}

	

	//
	//be the next process			//the current time

	//for loop that fills up ready array with the ready processes

	for (int i = 0; i < NUM_PROCESSES; i++)
	{
		//if the processId's start time is less than the current time, then put the id into the processesReadyToRun Array 
		// and if a process in the processRanYetList isn't = to true, if it is then it has ran already and shouldn't run
		if ( (process_list[i][1] <= current_time) && (hasProcessRanYetList[i] == FALSE) ) {

			processesReadyToRun[i] = process_list[i][0];
		}

		else
		{
			processesReadyToRun[i] = CANTRUN;
		}

	}

	
	// while all the itterations cant run, then add 1 to current time


	
	
	//which has the least processor time
	for (int i = 1; i < NUM_PROCESSES; i++) {

		
			//if the currently selected process to run next is greater than the curr time, then skip it

			//checks to see if the start time of the i's id is less than or = to the current time
		if (processesReadyToRun[i] != CANTRUN) {



			//if the execution time of i is less than the current process chosen, then reassign process to i
			if (process_list[next_process_ID][3] > process_list[i][3]) {

				next_process_ID = i;

			}
			//checks if there are duplicate values to the execution time, if there is, then compare their ExecutionPriority
			else if (process_list[i][3] == process_list[next_process_ID][3]) {

				if (process_list[next_process_ID][2] > process_list[i][2]) {

					next_process_ID = i;

				}
				//checks if there are duplicate values to the earliest startTime, if there is, then compare their ExecutionPriority
				else if (process_list[i][2] == process_list[next_process_ID][2]) {



					//moving onto check who has smaller ID
					if (process_list[next_process_ID][0] > process_list[i][0]) {
						next_process_ID = i;

					}
				}
			}

		}

		
	}

	processesReadyToRun[next_process_ID] = CANTRUN;
	hasProcessRanYetList[next_process_ID] = TRUE;
	return(next_process_ID);

}
// next_process ////////////////////////////////////////////////////////////



/* find_earliest_process ------------------------------------------------- */
int find_earliest_process(void)
{
	// this is where i do the 4 loops perhaps? 
	int the_earliest_process;   // the ID of the process that is supposed to
								// be executed first for each simulation run
								//int *zero = 0;

								//int *ProcessId = 0;
								//int *startTime = 1;
								//int *executionTime = 2;
								//int *ProcessPriority = 3;



								//gets size of Array
	




	//this for loop checks for the least value in the array first
	//then i need another loop that checks if all the values are less than it
	// to garuntee that earliest process is the least value in the array
	//otherwise if it isnt after the check loop then proceed to the next checker thing

	the_earliest_process = 0;

	for (int i = 1; i < NUM_PROCESSES; i++) {
		//which is the least process start time?

		//assigns the value in the the startTime part of the array to the earliest process if loop finds a smaller value than earliestProcess
		if (process_list[the_earliest_process][1] > process_list[i][1]) {

			the_earliest_process = i;
		}

		//checks if there are duplicate values to the earliest startTime, if there is, then compare their ExecutionPriority
		else if (process_list[i][1] == process_list[the_earliest_process][1]) {

			//assign the earliestProcess to the next array's index value and will compare that to the value next to it
			//the_earliest_process = NUM_PROCESSES[i][ProcessPriority];

			//moving onto checking for ExecutionPriority
			if (process_list[the_earliest_process][3] > process_list[i][3]) {
				the_earliest_process = i;

			}

			//check if there are duplicates for the processPriority
			else if (process_list[i][3] == process_list[the_earliest_process][3]) {

				//assign the executionTime Array value at index i 
				//the_earliest_process = NUM_PROCESSES[i][executionTime];

				if (process_list[the_earliest_process][2] > process_list[i][2]) {

					hasProcessRanYetList[i] = TRUE;
					the_earliest_process = i;

				}

				else if (process_list[i][3] == process_list[the_earliest_process][3]) {

					//the_earliest_process = NUM_PROCESSES[i][ProcessId];

					if (process_list[the_earliest_process][0] > process_list[i][0]) {

						the_earliest_process = i;
						hasProcessRanYetList[i] = TRUE;

					}
				}

			}

		}

	}

	hasProcessRanYetList[the_earliest_process] = TRUE;
	return(the_earliest_process);
}
// find_earliest_process ///////////////////////////////////////////////////





/* are_all_done --------------------------------------------------------- *
*                                                                         *
*  This module returns "TRUE", if all processes are completed.            *
*  Otherwsie, it returns "FALSE".                                         *
* ----------------------------------------------------------------------- */
int are_all_done(void)
{
	int status = TRUE;      // status (result) code
	
	
	for  (int i = 1; i < NUM_PROCESSES; i++)
	{
		if (hasProcessRanYetList[i] == TRUE) {
			status = TRUE;
		}

		if (hasProcessRanYetList[i] == FALSE)
		{
			//break
			status = FALSE;
			break;
		}
	}


	return(status);
}
// are_all_done ////////////////////////////////////////////////////////////



/* initialize the process list ----------------------------------------- */
void initialize_process_list(void)
{
	// process #0 ----------------------------------------
	process_list[0][0] = 0;     // process ID
	process_list[0][1] = 6;     // start time
	process_list[0][2] = 4;     // total execution time
	process_list[0][3] = 0;     // execution priority

								// process #1 ----------------------------------------
	process_list[1][0] = 1;     // process ID
	process_list[1][1] = 6;     // start time
	process_list[1][2] = 4;     // total execution time
	process_list[1][3] = 1;     // execution priority

								// process #2 ----------------------------------------
	process_list[2][0] = 2;     // process ID
	process_list[2][1] = 4;     // start time
	process_list[2][2] = 3;     // total execution time
	process_list[2][3] = 1;     // execution priority

								// process #3 ----------------------------------------
	process_list[3][0] = 3;     // process ID
	process_list[3][1] = 8;     // start time
	process_list[3][2] = 3;     // total execution time
	process_list[3][3] = 0;     // execution priority

								// process #4 ----------------------------------------
	process_list[4][0] = 4;     // process ID
	process_list[4][1] = 23;    // start time
	process_list[4][2] = 3;     // total execution time
	process_list[4][3] = 1;     // execution priority

								// process #5 ----------------------------------------
	process_list[5][0] = 5;     // process ID
	process_list[5][1] = 60;    // start time
	process_list[5][2] = 2;     // total execution time
	process_list[5][3] = 1;     // execution priority

								// process #6 ----------------------------------------
	process_list[6][0] = 6;     // process ID
	process_list[6][1] = 6;     // start time
	process_list[6][2] = 1;     // total execution time
	process_list[6][3] = 1;     // execution priority

								// process #7 ----------------------------------------
	process_list[7][0] = 7;     // process ID
	process_list[7][1] = 3;     // start time
	process_list[7][2] = 4;     // total execution time
	process_list[7][3] = 1;     // execution priority

								// process #8 ----------------------------------------
	process_list[8][0] = 8;     // process ID
	process_list[8][1] = 3;     // start time
	process_list[8][2] = 5;     // total execution time
	process_list[8][3] = 0;     // execution priority

								// process #9 ----------------------------------------
	process_list[9][0] = 9;     // process ID
	process_list[9][1] = 50;    // start time
	process_list[9][2] = 1;     // total execution time
	process_list[9][3] = 1;     // execution priority

}