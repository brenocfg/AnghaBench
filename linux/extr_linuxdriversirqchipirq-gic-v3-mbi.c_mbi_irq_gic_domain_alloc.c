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
struct irq_domain {TYPE_2__* parent; } ;
struct irq_data {TYPE_1__* chip; } ;
typedef  scalar_t__ irq_hw_number_t ;
struct TYPE_4__ {int /*<<< orphan*/  fwnode; } ;
struct TYPE_3__ {int (* irq_set_type ) (struct irq_data*,scalar_t__) ;} ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IRQ_TYPE_EDGE_RISING ; 
 int irq_domain_alloc_irqs_parent (struct irq_domain*,unsigned int,int,struct irq_fwspec*) ; 
 struct irq_data* irq_domain_get_irq_data (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  is_of_node (int /*<<< orphan*/ ) ; 
 int stub1 (struct irq_data*,scalar_t__) ; 

__attribute__((used)) static int mbi_irq_gic_domain_alloc(struct irq_domain *domain,
				       unsigned int virq,
				       irq_hw_number_t hwirq)
{
	struct irq_fwspec fwspec;
	struct irq_data *d;
	int err;

	/*
	 * Using ACPI? There is no MBI support in the spec, you
	 * shouldn't even be here.
	 */
	if (!is_of_node(domain->parent->fwnode))
		return -EINVAL;

	/*
	 * Let's default to edge. This is consistent with traditional
	 * MSIs, and systems requiring level signaling will just
	 * enforce the trigger on their own.
	 */
	fwspec.fwnode = domain->parent->fwnode;
	fwspec.param_count = 3;
	fwspec.param[0] = 0;
	fwspec.param[1] = hwirq - 32;
	fwspec.param[2] = IRQ_TYPE_EDGE_RISING;

	err = irq_domain_alloc_irqs_parent(domain, virq, 1, &fwspec);
	if (err)
		return err;

	d = irq_domain_get_irq_data(domain->parent, virq);
	return d->chip->irq_set_type(d, IRQ_TYPE_EDGE_RISING);
}