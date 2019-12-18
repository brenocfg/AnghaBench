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
struct spmi_pmic_arb {int dummy; } ;
struct irq_fwspec {int dummy; } ;
struct irq_domain {struct spmi_pmic_arb* host_data; } ;
typedef  scalar_t__ irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  qpnpint_irq_domain_map (struct spmi_pmic_arb*,struct irq_domain*,unsigned int,scalar_t__,unsigned int) ; 
 int qpnpint_irq_domain_translate (struct irq_domain*,struct irq_fwspec*,scalar_t__*,unsigned int*) ; 

__attribute__((used)) static int qpnpint_irq_domain_alloc(struct irq_domain *domain,
				    unsigned int virq, unsigned int nr_irqs,
				    void *data)
{
	struct spmi_pmic_arb *pmic_arb = domain->host_data;
	struct irq_fwspec *fwspec = data;
	irq_hw_number_t hwirq;
	unsigned int type;
	int ret, i;

	ret = qpnpint_irq_domain_translate(domain, fwspec, &hwirq, &type);
	if (ret)
		return ret;

	for (i = 0; i < nr_irqs; i++)
		qpnpint_irq_domain_map(pmic_arb, domain, virq + i, hwirq + i,
				       type);

	return 0;
}