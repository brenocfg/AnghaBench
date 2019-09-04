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
struct task_struct {int dummy; } ;
struct stack_trace {int dummy; } ;

/* Variables and functions */
 scalar_t__ KSTK_ESP (struct task_struct*) ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  save_stack_address_nosched ; 
 int /*<<< orphan*/  unwind_stack (struct stack_trace*,unsigned long*,int /*<<< orphan*/ ) ; 

void save_stack_trace_tsk(struct task_struct *tsk, struct stack_trace *trace)
{
	unsigned long *sp = NULL;

	if (tsk == current)
		sp = (unsigned long *) &sp;
	else
		sp = (unsigned long *) KSTK_ESP(tsk);

	unwind_stack(trace, sp, save_stack_address_nosched);
}