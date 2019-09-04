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
typedef  scalar_t__ irq_hw_number_t ;
struct TYPE_2__ {int /*<<< orphan*/  fwnode; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ GPC_MAX_IRQS ; 
 int /*<<< orphan*/  gpcv2_irqchip_data_chip ; 
 int imx_gpcv2_domain_translate (struct irq_domain*,struct irq_fwspec*,scalar_t__*,unsigned int*) ; 
 int irq_domain_alloc_irqs_parent (struct irq_domain*,unsigned int,unsigned int,struct irq_fwspec*) ; 
 int /*<<< orphan*/  irq_domain_set_hwirq_and_chip (struct irq_domain*,unsigned int,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imx_gpcv2_domain_alloc(struct irq_domain *domain,
				  unsigned int irq, unsigned int nr_irqs,
				  void *data)
{
	struct irq_fwspec *fwspec = data;
	struct irq_fwspec parent_fwspec;
	irq_hw_number_t hwirq;
	unsigned int type;
	int err;
	int i;

	err = imx_gpcv2_domain_translate(domain, fwspec, &hwirq, &type);
	if (err)
		return err;

	if (hwirq >= GPC_MAX_IRQS)
		return -EINVAL;

	for (i = 0; i < nr_irqs; i++) {
		irq_domain_set_hwirq_and_chip(domain, irq + i, hwirq + i,
				&gpcv2_irqchip_data_chip, domain->host_data);
	}

	parent_fwspec = *fwspec;
	parent_fwspec.fwnode = domain->parent->fwnode;
	return irq_domain_alloc_irqs_parent(domain, irq, nr_irqs,
					    &parent_fwspec);
}