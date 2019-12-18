#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mvebu_sei {TYPE_3__* caps; } ;
struct irq_fwspec {int param_count; scalar_t__* param; int /*<<< orphan*/  fwnode; } ;
struct irq_domain {TYPE_1__* parent; struct mvebu_sei* host_data; } ;
struct TYPE_5__ {scalar_t__ first; } ;
struct TYPE_6__ {TYPE_2__ ap_range; } ;
struct TYPE_4__ {int /*<<< orphan*/  fwnode; } ;

/* Variables and functions */
 int /*<<< orphan*/  handle_level_irq ; 
 int irq_domain_alloc_irqs_parent (struct irq_domain*,unsigned int,int,struct irq_fwspec*) ; 
 int /*<<< orphan*/  irq_domain_set_info (struct irq_domain*,unsigned int,unsigned long,int /*<<< orphan*/ *,struct mvebu_sei*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_probe (unsigned int) ; 
 int /*<<< orphan*/  mvebu_sei_ap_irq_chip ; 
 int /*<<< orphan*/  mvebu_sei_ap_translate (struct irq_domain*,void*,unsigned long*,unsigned int*) ; 

__attribute__((used)) static int mvebu_sei_ap_alloc(struct irq_domain *domain, unsigned int virq,
			      unsigned int nr_irqs, void *arg)
{
	struct mvebu_sei *sei = domain->host_data;
	struct irq_fwspec fwspec;
	unsigned long hwirq;
	unsigned int type;
	int err;

	mvebu_sei_ap_translate(domain, arg, &hwirq, &type);

	fwspec.fwnode = domain->parent->fwnode;
	fwspec.param_count = 1;
	fwspec.param[0] = hwirq + sei->caps->ap_range.first;

	err = irq_domain_alloc_irqs_parent(domain, virq, 1, &fwspec);
	if (err)
		return err;

	irq_domain_set_info(domain, virq, hwirq,
			    &mvebu_sei_ap_irq_chip, sei,
			    handle_level_irq, NULL, NULL);
	irq_set_probe(virq);

	return 0;
}