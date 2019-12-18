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
struct irq_fwspec {int param_count; scalar_t__* param; int /*<<< orphan*/  fwnode; } ;
struct irq_domain {TYPE_1__* parent; struct exiu_irq_data* host_data; } ;
struct exiu_irq_data {scalar_t__ spi_base; } ;
typedef  scalar_t__ irq_hw_number_t ;
struct TYPE_2__ {int /*<<< orphan*/  fwnode; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ GIC_SPI ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  exiu_irq_chip ; 
 int irq_domain_alloc_irqs_parent (struct irq_domain*,unsigned int,unsigned int,struct irq_fwspec*) ; 
 int /*<<< orphan*/  irq_domain_set_hwirq_and_chip (struct irq_domain*,unsigned int,scalar_t__,int /*<<< orphan*/ *,struct exiu_irq_data*) ; 
 scalar_t__ is_of_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int exiu_domain_alloc(struct irq_domain *dom, unsigned int virq,
			     unsigned int nr_irqs, void *data)
{
	struct irq_fwspec *fwspec = data;
	struct irq_fwspec parent_fwspec;
	struct exiu_irq_data *info = dom->host_data;
	irq_hw_number_t hwirq;

	parent_fwspec = *fwspec;
	if (is_of_node(dom->parent->fwnode)) {
		if (fwspec->param_count != 3)
			return -EINVAL;	/* Not GIC compliant */
		if (fwspec->param[0] != GIC_SPI)
			return -EINVAL;	/* No PPI should point to this domain */

		hwirq = fwspec->param[1] - info->spi_base;
	} else {
		hwirq = fwspec->param[0];
		parent_fwspec.param[0] = hwirq + info->spi_base + 32;
	}
	WARN_ON(nr_irqs != 1);
	irq_domain_set_hwirq_and_chip(dom, virq, hwirq, &exiu_irq_chip, info);

	parent_fwspec.fwnode = dom->parent->fwnode;
	return irq_domain_alloc_irqs_parent(dom, virq, nr_irqs, &parent_fwspec);
}