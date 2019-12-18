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
struct mbigen_device {int /*<<< orphan*/  base; } ;
struct irq_fwspec {int dummy; } ;
struct irq_domain {int dummy; } ;
typedef  scalar_t__ irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  irq_domain_set_hwirq_and_chip (struct irq_domain*,unsigned int,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mbigen_domain_translate (struct irq_domain*,struct irq_fwspec*,scalar_t__*,unsigned int*) ; 
 int /*<<< orphan*/  mbigen_irq_chip ; 
 int platform_msi_domain_alloc (struct irq_domain*,unsigned int,unsigned int) ; 
 struct mbigen_device* platform_msi_get_host_data (struct irq_domain*) ; 

__attribute__((used)) static int mbigen_irq_domain_alloc(struct irq_domain *domain,
					unsigned int virq,
					unsigned int nr_irqs,
					void *args)
{
	struct irq_fwspec *fwspec = args;
	irq_hw_number_t hwirq;
	unsigned int type;
	struct mbigen_device *mgn_chip;
	int i, err;

	err = mbigen_domain_translate(domain, fwspec, &hwirq, &type);
	if (err)
		return err;

	err = platform_msi_domain_alloc(domain, virq, nr_irqs);
	if (err)
		return err;

	mgn_chip = platform_msi_get_host_data(domain);

	for (i = 0; i < nr_irqs; i++)
		irq_domain_set_hwirq_and_chip(domain, virq + i, hwirq + i,
				      &mbigen_irq_chip, mgn_chip->base);

	return 0;
}