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
struct irq_fwspec {int /*<<< orphan*/  fwnode; } ;
struct irq_domain {TYPE_1__* parent; int /*<<< orphan*/  host_data; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;
struct TYPE_2__ {int /*<<< orphan*/  fwnode; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int irq_domain_alloc_irqs_parent (struct irq_domain*,unsigned int,unsigned int,struct irq_fwspec*) ; 
 int /*<<< orphan*/  irq_domain_set_hwirq_and_chip (struct irq_domain*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_cirq_chip ; 
 int mtk_cirq_domain_translate (struct irq_domain*,struct irq_fwspec*,int /*<<< orphan*/ *,unsigned int*) ; 

__attribute__((used)) static int mtk_cirq_domain_alloc(struct irq_domain *domain, unsigned int virq,
				 unsigned int nr_irqs, void *arg)
{
	int ret;
	irq_hw_number_t hwirq;
	unsigned int type;
	struct irq_fwspec *fwspec = arg;
	struct irq_fwspec parent_fwspec = *fwspec;

	ret = mtk_cirq_domain_translate(domain, fwspec, &hwirq, &type);
	if (ret)
		return ret;

	if (WARN_ON(nr_irqs != 1))
		return -EINVAL;

	irq_domain_set_hwirq_and_chip(domain, virq, hwirq,
				      &mtk_cirq_chip,
				      domain->host_data);

	parent_fwspec.fwnode = domain->parent->fwnode;
	return irq_domain_alloc_irqs_parent(domain, virq, nr_irqs,
					    &parent_fwspec);
}