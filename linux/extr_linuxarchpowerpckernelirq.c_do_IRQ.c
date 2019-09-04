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
struct thread_info {scalar_t__ flags; int /*<<< orphan*/ * task; int /*<<< orphan*/  preempt_count; } ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __do_irq (struct pt_regs*) ; 
 int /*<<< orphan*/  call_do_irq (struct pt_regs*,struct thread_info*) ; 
 struct thread_info* current_thread_info () ; 
 struct thread_info** hardirq_ctx ; 
 size_t raw_smp_processor_id () ; 
 int /*<<< orphan*/  set_bits (scalar_t__,scalar_t__*) ; 
 struct pt_regs* set_irq_regs (struct pt_regs*) ; 
 struct thread_info** softirq_ctx ; 
 scalar_t__ unlikely (int) ; 

void do_IRQ(struct pt_regs *regs)
{
	struct pt_regs *old_regs = set_irq_regs(regs);
	struct thread_info *curtp, *irqtp, *sirqtp;

	/* Switch to the irq stack to handle this */
	curtp = current_thread_info();
	irqtp = hardirq_ctx[raw_smp_processor_id()];
	sirqtp = softirq_ctx[raw_smp_processor_id()];

	/* Already there ? */
	if (unlikely(curtp == irqtp || curtp == sirqtp)) {
		__do_irq(regs);
		set_irq_regs(old_regs);
		return;
	}

	/* Prepare the thread_info in the irq stack */
	irqtp->task = curtp->task;
	irqtp->flags = 0;

	/* Copy the preempt_count so that the [soft]irq checks work. */
	irqtp->preempt_count = curtp->preempt_count;

	/* Switch stack and call */
	call_do_irq(regs, irqtp);

	/* Restore stack limit */
	irqtp->task = NULL;

	/* Copy back updates to the thread_info */
	if (irqtp->flags)
		set_bits(irqtp->flags, &curtp->flags);

	set_irq_regs(old_regs);
}