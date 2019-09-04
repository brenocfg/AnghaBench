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
struct pt_regs {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void stack_overflow_check(struct pt_regs *regs)
{
#ifdef CONFIG_DEBUG_STACKOVERFLOW
	#define STACK_MARGIN	(256*6)

	/* Our stack starts directly behind the thread_info struct. */
	unsigned long stack_start = (unsigned long) current_thread_info();
	unsigned long sp = regs->gr[30];
	unsigned long stack_usage;
	unsigned int *last_usage;
	int cpu = smp_processor_id();

	/* if sr7 != 0, we interrupted a userspace process which we do not want
	 * to check for stack overflow. We will only check the kernel stack. */
	if (regs->sr[7])
		return;

	/* exit if already in panic */
	if (sysctl_panic_on_stackoverflow < 0)
		return;

	/* calculate kernel stack usage */
	stack_usage = sp - stack_start;
#ifdef CONFIG_IRQSTACKS
	if (likely(stack_usage <= THREAD_SIZE))
		goto check_kernel_stack; /* found kernel stack */

	/* check irq stack usage */
	stack_start = (unsigned long) &per_cpu(irq_stack_union, cpu).stack;
	stack_usage = sp - stack_start;

	last_usage = &per_cpu(irq_stat.irq_stack_usage, cpu);
	if (unlikely(stack_usage > *last_usage))
		*last_usage = stack_usage;

	if (likely(stack_usage < (IRQ_STACK_SIZE - STACK_MARGIN)))
		return;

	pr_emerg("stackcheck: %s will most likely overflow irq stack "
		 "(sp:%lx, stk bottom-top:%lx-%lx)\n",
		current->comm, sp, stack_start, stack_start + IRQ_STACK_SIZE);
	goto panic_check;

check_kernel_stack:
#endif

	/* check kernel stack usage */
	last_usage = &per_cpu(irq_stat.kernel_stack_usage, cpu);

	if (unlikely(stack_usage > *last_usage))
		*last_usage = stack_usage;

	if (likely(stack_usage < (THREAD_SIZE - STACK_MARGIN)))
		return;

	pr_emerg("stackcheck: %s will most likely overflow kernel stack "
		 "(sp:%lx, stk bottom-top:%lx-%lx)\n",
		current->comm, sp, stack_start, stack_start + THREAD_SIZE);

#ifdef CONFIG_IRQSTACKS
panic_check:
#endif
	if (sysctl_panic_on_stackoverflow) {
		sysctl_panic_on_stackoverflow = -1; /* disable further checks */
		panic("low stack detected by irq handler - check messages\n");
	}
#endif
}