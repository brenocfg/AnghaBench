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
struct irq_fwspec {int param_count; unsigned long* param; int /*<<< orphan*/  fwnode; } ;
struct irq_domain {TYPE_1__* parent; } ;
typedef  unsigned long irq_hw_number_t ;
struct TYPE_2__ {int /*<<< orphan*/  fwnode; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int IRQ_TYPE_EDGE_BOTH ; 
 unsigned int IRQ_TYPE_EDGE_RISING ; 
 unsigned int IRQ_TYPE_LEVEL_HIGH ; 
 unsigned int IRQ_TYPE_LEVEL_MASK ; 
 unsigned long get_parent_hwirq (unsigned long) ; 
 int irq_domain_alloc_irqs_parent (struct irq_domain*,unsigned int,unsigned int,struct irq_fwspec*) ; 
 int irq_domain_set_hwirq_and_chip (struct irq_domain*,unsigned int,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qcom_pdc_gic_chip ; 
 int qcom_pdc_translate (struct irq_domain*,struct irq_fwspec*,unsigned long*,unsigned int*) ; 

__attribute__((used)) static int qcom_pdc_alloc(struct irq_domain *domain, unsigned int virq,
			  unsigned int nr_irqs, void *data)
{
	struct irq_fwspec *fwspec = data;
	struct irq_fwspec parent_fwspec;
	irq_hw_number_t hwirq, parent_hwirq;
	unsigned int type;
	int ret;

	ret = qcom_pdc_translate(domain, fwspec, &hwirq, &type);
	if (ret)
		return -EINVAL;

	parent_hwirq = get_parent_hwirq(hwirq);
	if (parent_hwirq == ~0UL)
		return -EINVAL;

	ret  = irq_domain_set_hwirq_and_chip(domain, virq, hwirq,
					     &qcom_pdc_gic_chip, NULL);
	if (ret)
		return ret;

	if (type & IRQ_TYPE_EDGE_BOTH)
		type = IRQ_TYPE_EDGE_RISING;

	if (type & IRQ_TYPE_LEVEL_MASK)
		type = IRQ_TYPE_LEVEL_HIGH;

	parent_fwspec.fwnode      = domain->parent->fwnode;
	parent_fwspec.param_count = 3;
	parent_fwspec.param[0]    = 0;
	parent_fwspec.param[1]    = parent_hwirq;
	parent_fwspec.param[2]    = type;

	return irq_domain_alloc_irqs_parent(domain, virq, nr_irqs,
					    &parent_fwspec);
}