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
struct irq_domain {int dummy; } ;
struct irq_data {int dummy; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  GIC_HWIRQ_TO_SHARED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ipi_available ; 
 struct irq_data* irq_get_irq_data (unsigned int) ; 
 int /*<<< orphan*/  irqd_to_hwirq (struct irq_data*) ; 

void gic_ipi_domain_free(struct irq_domain *d, unsigned int virq,
			 unsigned int nr_irqs)
{
	irq_hw_number_t base_hwirq;
	struct irq_data *data;

	data = irq_get_irq_data(virq);
	if (!data)
		return;

	base_hwirq = GIC_HWIRQ_TO_SHARED(irqd_to_hwirq(data));
	bitmap_set(ipi_available, base_hwirq, nr_irqs);
}