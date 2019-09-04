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
struct irq_data {int hwirq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IAR ; 
 int /*<<< orphan*/  SIE ; 
 scalar_t__ irqd_is_level_type (struct irq_data*) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  xintc_write (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void intc_enable_or_unmask(struct irq_data *d)
{
	unsigned long mask = 1 << d->hwirq;

	pr_debug("irq-xilinx: enable_or_unmask: %ld\n", d->hwirq);

	/* ack level irqs because they can't be acked during
	 * ack function since the handle_level_irq function
	 * acks the irq before calling the interrupt handler
	 */
	if (irqd_is_level_type(d))
		xintc_write(IAR, mask);

	xintc_write(SIE, mask);
}