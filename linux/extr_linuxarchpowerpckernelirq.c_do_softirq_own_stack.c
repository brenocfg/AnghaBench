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
struct thread_info {scalar_t__ flags; int /*<<< orphan*/ * task; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_do_softirq (struct thread_info*) ; 
 struct thread_info* current_thread_info () ; 
 int /*<<< orphan*/  set_bits (scalar_t__,scalar_t__*) ; 
 size_t smp_processor_id () ; 
 struct thread_info** softirq_ctx ; 

void do_softirq_own_stack(void)
{
	struct thread_info *curtp, *irqtp;

	curtp = current_thread_info();
	irqtp = softirq_ctx[smp_processor_id()];
	irqtp->task = curtp->task;
	irqtp->flags = 0;
	call_do_softirq(irqtp);
	irqtp->task = NULL;

	/* Set any flag that may have been set on the
	 * alternate stack
	 */
	if (irqtp->flags)
		set_bits(irqtp->flags, &curtp->flags);
}