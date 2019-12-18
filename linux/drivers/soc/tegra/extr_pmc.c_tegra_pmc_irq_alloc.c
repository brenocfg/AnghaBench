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
struct TYPE_6__ {scalar_t__ instance; scalar_t__ pin; } ;
struct tegra_wake_event {scalar_t__ id; scalar_t__ irq; TYPE_3__ gpio; } ;
struct tegra_pmc_soc {unsigned int num_wake_events; struct tegra_wake_event* wake_events; } ;
struct tegra_pmc {int /*<<< orphan*/  irq; TYPE_2__* dev; struct tegra_pmc_soc* soc; } ;
struct irq_fwspec {int param_count; scalar_t__* param; int /*<<< orphan*/ * fwnode; } ;
struct irq_domain {struct tegra_pmc* host_data; } ;
struct TYPE_5__ {TYPE_1__* of_node; } ;
struct TYPE_4__ {int /*<<< orphan*/  fwnode; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ GIC_SPI ; 
 scalar_t__ ULONG_MAX ; 
 scalar_t__ WARN_ON (int) ; 
 int irq_domain_alloc_irqs_parent (struct irq_domain*,unsigned int,unsigned int,struct irq_fwspec*) ; 
 int irq_domain_set_hwirq_and_chip (struct irq_domain*,unsigned int,scalar_t__,int /*<<< orphan*/ *,struct tegra_pmc*) ; 

__attribute__((used)) static int tegra_pmc_irq_alloc(struct irq_domain *domain, unsigned int virq,
			       unsigned int num_irqs, void *data)
{
	struct tegra_pmc *pmc = domain->host_data;
	const struct tegra_pmc_soc *soc = pmc->soc;
	struct irq_fwspec *fwspec = data;
	unsigned int i;
	int err = 0;

	if (WARN_ON(num_irqs > 1))
		return -EINVAL;

	for (i = 0; i < soc->num_wake_events; i++) {
		const struct tegra_wake_event *event = &soc->wake_events[i];

		if (fwspec->param_count == 2) {
			struct irq_fwspec spec;

			if (event->id != fwspec->param[0])
				continue;

			err = irq_domain_set_hwirq_and_chip(domain, virq,
							    event->id,
							    &pmc->irq, pmc);
			if (err < 0)
				break;

			spec.fwnode = &pmc->dev->of_node->fwnode;
			spec.param_count = 3;
			spec.param[0] = GIC_SPI;
			spec.param[1] = event->irq;
			spec.param[2] = fwspec->param[1];

			err = irq_domain_alloc_irqs_parent(domain, virq,
							   num_irqs, &spec);

			break;
		}

		if (fwspec->param_count == 3) {
			if (event->gpio.instance != fwspec->param[0] ||
			    event->gpio.pin != fwspec->param[1])
				continue;

			err = irq_domain_set_hwirq_and_chip(domain, virq,
							    event->id,
							    &pmc->irq, pmc);

			break;
		}
	}

	/*
	 * For interrupts that don't have associated wake events, assign a
	 * dummy hardware IRQ number. This is used in the ->irq_set_type()
	 * and ->irq_set_wake() callbacks to return early for these IRQs.
	 */
	if (i == soc->num_wake_events)
		err = irq_domain_set_hwirq_and_chip(domain, virq, ULONG_MAX,
						    &pmc->irq, pmc);

	return err;
}