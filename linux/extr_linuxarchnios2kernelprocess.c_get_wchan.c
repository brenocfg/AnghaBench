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
struct TYPE_2__ {scalar_t__ ksp; } ;
struct task_struct {scalar_t__ state; TYPE_1__ thread; } ;
struct switch_stack {unsigned long fp; } ;

/* Variables and functions */
 scalar_t__ TASK_RUNNING ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  in_sched_functions (unsigned long) ; 

unsigned long get_wchan(struct task_struct *p)
{
	unsigned long fp, pc;
	unsigned long stack_page;
	int count = 0;

	if (!p || p == current || p->state == TASK_RUNNING)
		return 0;

	stack_page = (unsigned long)p;
	fp = ((struct switch_stack *)p->thread.ksp)->fp;	/* ;dgt2 */
	do {
		if (fp < stack_page+sizeof(struct task_struct) ||
			fp >= 8184+stack_page)	/* ;dgt2;tmp */
			return 0;
		pc = ((unsigned long *)fp)[1];
		if (!in_sched_functions(pc))
			return pc;
		fp = *(unsigned long *) fp;
	} while (count++ < 16);		/* ;dgt2;tmp */
	return 0;
}