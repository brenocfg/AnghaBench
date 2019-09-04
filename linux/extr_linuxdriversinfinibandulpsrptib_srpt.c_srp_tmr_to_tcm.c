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

/* Variables and functions */
#define  SRP_TSK_ABORT_TASK 132 
#define  SRP_TSK_ABORT_TASK_SET 131 
#define  SRP_TSK_CLEAR_ACA 130 
#define  SRP_TSK_CLEAR_TASK_SET 129 
#define  SRP_TSK_LUN_RESET 128 
 int TMR_ABORT_TASK ; 
 int TMR_ABORT_TASK_SET ; 
 int TMR_CLEAR_ACA ; 
 int TMR_CLEAR_TASK_SET ; 
 int TMR_LUN_RESET ; 

__attribute__((used)) static int srp_tmr_to_tcm(int fn)
{
	switch (fn) {
	case SRP_TSK_ABORT_TASK:
		return TMR_ABORT_TASK;
	case SRP_TSK_ABORT_TASK_SET:
		return TMR_ABORT_TASK_SET;
	case SRP_TSK_CLEAR_TASK_SET:
		return TMR_CLEAR_TASK_SET;
	case SRP_TSK_LUN_RESET:
		return TMR_LUN_RESET;
	case SRP_TSK_CLEAR_ACA:
		return TMR_CLEAR_ACA;
	default:
		return -1;
	}
}