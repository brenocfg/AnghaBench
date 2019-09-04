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
struct TYPE_2__ {scalar_t__ regs; } ;
struct task_struct {TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  save_all (struct task_struct*) ; 

void flush_all_to_thread(struct task_struct *tsk)
{
	if (tsk->thread.regs) {
		preempt_disable();
		BUG_ON(tsk != current);
		save_all(tsk);

#ifdef CONFIG_SPE
		if (tsk->thread.regs->msr & MSR_SPE)
			tsk->thread.spefscr = mfspr(SPRN_SPEFSCR);
#endif

		preempt_enable();
	}
}