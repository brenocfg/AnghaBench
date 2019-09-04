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
struct TYPE_2__ {int /*<<< orphan*/ * last_hit_ubp; } ;
struct task_struct {TYPE_1__ thread; } ;
struct pt_regs {int /*<<< orphan*/  msr; } ;
struct arch_hw_breakpoint {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_SE ; 
 int /*<<< orphan*/  __set_breakpoint (struct arch_hw_breakpoint*) ; 
 struct arch_hw_breakpoint* counter_arch_bp (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 

void thread_change_pc(struct task_struct *tsk, struct pt_regs *regs)
{
	struct arch_hw_breakpoint *info;

	if (likely(!tsk->thread.last_hit_ubp))
		return;

	info = counter_arch_bp(tsk->thread.last_hit_ubp);
	regs->msr &= ~MSR_SE;
	__set_breakpoint(info);
	tsk->thread.last_hit_ubp = NULL;
}