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
struct irq_fwspec {int dummy; } ;
struct irq_domain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_domain_set_hwirq_and_chip (struct irq_domain*,unsigned int,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ti_sci_intr_alloc_gic_irq (struct irq_domain*,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  ti_sci_intr_irq_chip ; 
 int ti_sci_intr_irq_domain_translate (struct irq_domain*,struct irq_fwspec*,unsigned long*,unsigned int*) ; 

__attribute__((used)) static int ti_sci_intr_irq_domain_alloc(struct irq_domain *domain,
					unsigned int virq, unsigned int nr_irqs,
					void *data)
{
	struct irq_fwspec *fwspec = data;
	unsigned long hwirq;
	unsigned int flags;
	int err;

	err = ti_sci_intr_irq_domain_translate(domain, fwspec, &hwirq, &flags);
	if (err)
		return err;

	err = ti_sci_intr_alloc_gic_irq(domain, virq, hwirq);
	if (err)
		return err;

	irq_domain_set_hwirq_and_chip(domain, virq, hwirq,
				      &ti_sci_intr_irq_chip, NULL);

	return 0;
}