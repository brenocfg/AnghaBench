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
struct irq_data {scalar_t__ hwirq; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ GPMC_NR_NAND_IRQS ; 
 unsigned int IRQ_TYPE_EDGE_FALLING ; 
 unsigned int IRQ_TYPE_EDGE_RISING ; 
 int /*<<< orphan*/  gpmc_irq_edge_config (scalar_t__,int) ; 

__attribute__((used)) static int gpmc_irq_set_type(struct irq_data *d, unsigned int trigger)
{
	/* can't set type for NAND IRQs */
	if (d->hwirq < GPMC_NR_NAND_IRQS)
		return -EINVAL;

	/* We can support either rising or falling edge at a time */
	if (trigger == IRQ_TYPE_EDGE_FALLING)
		gpmc_irq_edge_config(d->hwirq, false);
	else if (trigger == IRQ_TYPE_EDGE_RISING)
		gpmc_irq_edge_config(d->hwirq, true);
	else
		return -EINVAL;

	return 0;
}