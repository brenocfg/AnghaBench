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
struct pt_regs {int flags; } ;

/* Variables and functions */
 int X86_EFLAGS_IF ; 
 int X86_VM_MASK ; 
 int /*<<< orphan*/  irq_work_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mce_irq_work ; 
 int /*<<< orphan*/  mce_notify_irq () ; 
 int /*<<< orphan*/  mce_schedule_work () ; 

__attribute__((used)) static void mce_report_event(struct pt_regs *regs)
{
	if (regs->flags & (X86_VM_MASK|X86_EFLAGS_IF)) {
		mce_notify_irq();
		/*
		 * Triggering the work queue here is just an insurance
		 * policy in case the syscall exit notify handler
		 * doesn't run soon enough or ends up running on the
		 * wrong CPU (can happen when audit sleeps)
		 */
		mce_schedule_work();
		return;
	}

	irq_work_queue(&mce_irq_work);
}