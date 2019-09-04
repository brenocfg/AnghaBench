#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  spurious_irqs; } ;
struct TYPE_3__ {unsigned int (* get_irq ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  __this_cpu_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_stack_overflow () ; 
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 
 int /*<<< orphan*/  irq_enter () ; 
 int /*<<< orphan*/  irq_exit () ; 
 TYPE_2__ irq_stat ; 
 int /*<<< orphan*/  may_hard_irq_enable () ; 
 TYPE_1__ ppc_md ; 
 unsigned int stub1 () ; 
 int /*<<< orphan*/  trace_irq_entry (struct pt_regs*) ; 
 int /*<<< orphan*/  trace_irq_exit (struct pt_regs*) ; 
 scalar_t__ unlikely (int) ; 

void __do_irq(struct pt_regs *regs)
{
	unsigned int irq;

	irq_enter();

	trace_irq_entry(regs);

	check_stack_overflow();

	/*
	 * Query the platform PIC for the interrupt & ack it.
	 *
	 * This will typically lower the interrupt line to the CPU
	 */
	irq = ppc_md.get_irq();

	/* We can hard enable interrupts now to allow perf interrupts */
	may_hard_irq_enable();

	/* And finally process it */
	if (unlikely(!irq))
		__this_cpu_inc(irq_stat.spurious_irqs);
	else
		generic_handle_irq(irq);

	trace_irq_exit(regs);

	irq_exit();
}