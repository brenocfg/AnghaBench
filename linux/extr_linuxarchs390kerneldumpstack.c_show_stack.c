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
struct TYPE_2__ {unsigned long ksp; } ;
struct task_struct {TYPE_1__ thread; } ;

/* Variables and functions */
 struct task_struct* current ; 
 unsigned long current_stack_pointer () ; 
 int /*<<< orphan*/  debug_show_held_locks (struct task_struct*) ; 
 int /*<<< orphan*/  dump_trace (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct task_struct*,unsigned long) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  show_address ; 

void show_stack(struct task_struct *task, unsigned long *stack)
{
	unsigned long sp = (unsigned long) stack;

	if (!sp)
		sp = task ? task->thread.ksp : current_stack_pointer();
	printk("Call Trace:\n");
	dump_trace(show_address, NULL, task, sp);
	if (!task)
		task = current;
	debug_show_held_locks(task);
}