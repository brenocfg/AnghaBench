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

/* Variables and functions */
 unsigned long THREAD_SIZE ; 
 struct task_struct* current ; 
 int kstack_depth_to_print ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long) ; 
 int /*<<< orphan*/  show_trace (unsigned long*,unsigned long*) ; 
 scalar_t__ thread_saved_ksp (struct task_struct*) ; 

void show_stack(struct task_struct *task, unsigned long *stack)
{
	unsigned long *p, *endstack;
	int i;

	if (!stack) {
		if (task && task != current)
			/* We know this is a kernel stack,
			   so this is the start/end */
			stack = (unsigned long *)thread_saved_ksp(task);
		else
			stack = (unsigned long *)&stack;
	}
	endstack = (unsigned long *)(((unsigned long)stack + THREAD_SIZE - 1)
				     & -THREAD_SIZE);

	pr_debug("Stack from %08lx:", (unsigned long)stack);
	for (i = 0, p = stack; i < kstack_depth_to_print; i++) {
		if (p + 1 > endstack)
			break;
		if (i % 8 == 0)
			pr_cont("\n	    ");
		pr_cont(" %08lx", *p++);
	}
	pr_cont("\n");
	show_trace(stack, endstack);
}