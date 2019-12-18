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
struct irq_fwspec {int param_count; scalar_t__* param; int /*<<< orphan*/  fwnode; } ;
struct irq_domain {TYPE_2__* parent; int /*<<< orphan*/  host_data; } ;
typedef  scalar_t__ irq_hw_number_t ;
struct TYPE_4__ {int /*<<< orphan*/  fwnode; } ;
struct TYPE_3__ {scalar_t__ is_nvic; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ GIC_SPI ; 
 int irq_domain_alloc_irqs_parent (struct irq_domain*,unsigned int,unsigned int,struct irq_fwspec*) ; 
 int /*<<< orphan*/  irq_domain_get_of_node (TYPE_2__*) ; 
 int /*<<< orphan*/  irq_domain_set_hwirq_and_chip (struct irq_domain*,unsigned int,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* mscm_ir_data ; 
 int /*<<< orphan*/  vf610_mscm_ir_irq_chip ; 

__attribute__((used)) static int vf610_mscm_ir_domain_alloc(struct irq_domain *domain, unsigned int virq,
				      unsigned int nr_irqs, void *arg)
{
	int i;
	irq_hw_number_t hwirq;
	struct irq_fwspec *fwspec = arg;
	struct irq_fwspec parent_fwspec;

	if (!irq_domain_get_of_node(domain->parent))
		return -EINVAL;

	if (fwspec->param_count != 2)
		return -EINVAL;

	hwirq = fwspec->param[0];
	for (i = 0; i < nr_irqs; i++)
		irq_domain_set_hwirq_and_chip(domain, virq + i, hwirq + i,
					      &vf610_mscm_ir_irq_chip,
					      domain->host_data);

	parent_fwspec.fwnode = domain->parent->fwnode;

	if (mscm_ir_data->is_nvic) {
		parent_fwspec.param_count = 1;
		parent_fwspec.param[0] = fwspec->param[0];
	} else {
		parent_fwspec.param_count = 3;
		parent_fwspec.param[0] = GIC_SPI;
		parent_fwspec.param[1] = fwspec->param[0];
		parent_fwspec.param[2] = fwspec->param[1];
	}

	return irq_domain_alloc_irqs_parent(domain, virq, nr_irqs,
					    &parent_fwspec);
}