#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sas_task {int task_state_flags; } ;

/* Variables and functions */
 int SAS_TASK_NEED_DEV_RESET ; 
 int TMF_RESP_FUNC_FAILED ; 
 int TMF_RESP_FUNC_SUCC ; 

int isci_task_query_task(
	struct sas_task *task)
{
	/* See if there is a pending device reset for this device. */
	if (task->task_state_flags & SAS_TASK_NEED_DEV_RESET)
		return TMF_RESP_FUNC_FAILED;
	else
		return TMF_RESP_FUNC_SUCC;
}