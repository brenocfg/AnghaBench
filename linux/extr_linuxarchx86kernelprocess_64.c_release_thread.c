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
struct task_struct {scalar_t__ mm; } ;

/* Variables and functions */

void release_thread(struct task_struct *dead_task)
{
	if (dead_task->mm) {
#ifdef CONFIG_MODIFY_LDT_SYSCALL
		if (dead_task->mm->context.ldt) {
			pr_warn("WARNING: dead process %s still has LDT? <%p/%d>\n",
				dead_task->comm,
				dead_task->mm->context.ldt->entries,
				dead_task->mm->context.ldt->nr_entries);
			BUG();
		}
#endif
	}
}