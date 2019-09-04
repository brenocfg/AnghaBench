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
struct irq_fwspec {int param_count; unsigned int* param; int /*<<< orphan*/  fwnode; } ;
struct irq_domain {TYPE_1__* parent; int /*<<< orphan*/  host_data; } ;
typedef  scalar_t__ irq_hw_number_t ;
struct TYPE_2__ {int /*<<< orphan*/  fwnode; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 scalar_t__ UNIPHIER_AIDET_NR_IRQS ; 
 int irq_domain_alloc_irqs_parent (struct irq_domain*,unsigned int,int,struct irq_fwspec*) ; 
 int irq_domain_set_hwirq_and_chip (struct irq_domain*,unsigned int,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int uniphier_aidet_domain_translate (struct irq_domain*,void*,scalar_t__*,unsigned int*) ; 
 int /*<<< orphan*/  uniphier_aidet_irq_chip ; 

__attribute__((used)) static int uniphier_aidet_domain_alloc(struct irq_domain *domain,
				       unsigned int virq, unsigned int nr_irqs,
				       void *arg)
{
	struct irq_fwspec parent_fwspec;
	irq_hw_number_t hwirq;
	unsigned int type;
	int ret;

	if (nr_irqs != 1)
		return -EINVAL;

	ret = uniphier_aidet_domain_translate(domain, arg, &hwirq, &type);
	if (ret)
		return ret;

	switch (type) {
	case IRQ_TYPE_EDGE_RISING:
	case IRQ_TYPE_LEVEL_HIGH:
		break;
	case IRQ_TYPE_EDGE_FALLING:
		type = IRQ_TYPE_EDGE_RISING;
		break;
	case IRQ_TYPE_LEVEL_LOW:
		type = IRQ_TYPE_LEVEL_HIGH;
		break;
	default:
		return -EINVAL;
	}

	if (hwirq >= UNIPHIER_AIDET_NR_IRQS)
		return -ENXIO;

	ret = irq_domain_set_hwirq_and_chip(domain, virq, hwirq,
					    &uniphier_aidet_irq_chip,
					    domain->host_data);
	if (ret)
		return ret;

	/* parent is GIC */
	parent_fwspec.fwnode = domain->parent->fwnode;
	parent_fwspec.param_count = 3;
	parent_fwspec.param[0] = 0;		/* SPI */
	parent_fwspec.param[1] = hwirq;
	parent_fwspec.param[2] = type;

	return irq_domain_alloc_irqs_parent(domain, virq, 1, &parent_fwspec);
}