#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct eznps_dp {void* gpa1; void* eflags; } ;
struct TYPE_2__ {struct eznps_dp dp; } ;
struct task_struct {TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTOP_AUX_EFLAGS ; 
 int /*<<< orphan*/  CTOP_AUX_GPA1 ; 
 void* read_aux_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_aux_reg (int /*<<< orphan*/ ,void*) ; 

void dp_save_restore(struct task_struct *prev, struct task_struct *next)
{
	struct eznps_dp *prev_task_dp = &prev->thread.dp;
	struct eznps_dp *next_task_dp = &next->thread.dp;

	/* Here we save all Data Plane related auxiliary registers */
	prev_task_dp->eflags = read_aux_reg(CTOP_AUX_EFLAGS);
	write_aux_reg(CTOP_AUX_EFLAGS, next_task_dp->eflags);

	prev_task_dp->gpa1 = read_aux_reg(CTOP_AUX_GPA1);
	write_aux_reg(CTOP_AUX_GPA1, next_task_dp->gpa1);
}