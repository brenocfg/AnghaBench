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
struct mvebu_icu_irq_data {struct mvebu_icu* icu; int /*<<< orphan*/  icu_group; int /*<<< orphan*/  type; } ;
struct mvebu_icu {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq_chip; } ;
struct irq_fwspec {int /*<<< orphan*/ * param; } ;
struct irq_domain {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQCHIP_STATE_PENDING ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int irq_domain_set_hwirq_and_chip (struct irq_domain*,unsigned int,unsigned long,int /*<<< orphan*/ *,struct mvebu_icu_irq_data*) ; 
 int irq_set_irqchip_state (unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct mvebu_icu_irq_data*) ; 
 struct mvebu_icu_irq_data* kmalloc (int,int /*<<< orphan*/ ) ; 
 int mvebu_icu_irq_domain_translate (struct irq_domain*,struct irq_fwspec*,unsigned long*,int /*<<< orphan*/ *) ; 
 int platform_msi_domain_alloc (struct irq_domain*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  platform_msi_domain_free (struct irq_domain*,unsigned int,unsigned int) ; 
 struct mvebu_icu* platform_msi_get_host_data (struct irq_domain*) ; 

__attribute__((used)) static int
mvebu_icu_irq_domain_alloc(struct irq_domain *domain, unsigned int virq,
			   unsigned int nr_irqs, void *args)
{
	int err;
	unsigned long hwirq;
	struct irq_fwspec *fwspec = args;
	struct mvebu_icu *icu = platform_msi_get_host_data(domain);
	struct mvebu_icu_irq_data *icu_irqd;

	icu_irqd = kmalloc(sizeof(*icu_irqd), GFP_KERNEL);
	if (!icu_irqd)
		return -ENOMEM;

	err = mvebu_icu_irq_domain_translate(domain, fwspec, &hwirq,
					     &icu_irqd->type);
	if (err) {
		dev_err(icu->dev, "failed to translate ICU parameters\n");
		goto free_irqd;
	}

	icu_irqd->icu_group = fwspec->param[0];
	icu_irqd->icu = icu;

	err = platform_msi_domain_alloc(domain, virq, nr_irqs);
	if (err) {
		dev_err(icu->dev, "failed to allocate ICU interrupt in parent domain\n");
		goto free_irqd;
	}

	/* Make sure there is no interrupt left pending by the firmware */
	err = irq_set_irqchip_state(virq, IRQCHIP_STATE_PENDING, false);
	if (err)
		goto free_msi;

	err = irq_domain_set_hwirq_and_chip(domain, virq, hwirq,
					    &icu->irq_chip, icu_irqd);
	if (err) {
		dev_err(icu->dev, "failed to set the data to IRQ domain\n");
		goto free_msi;
	}

	return 0;

free_msi:
	platform_msi_domain_free(domain, virq, nr_irqs);
free_irqd:
	kfree(icu_irqd);
	return err;
}