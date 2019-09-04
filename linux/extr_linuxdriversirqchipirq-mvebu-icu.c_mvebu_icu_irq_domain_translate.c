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
struct mvebu_icu {int /*<<< orphan*/  dev; } ;
struct irq_fwspec {int param_count; unsigned int* param; } ;
struct irq_domain {struct mvebu_icu* host_data; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int ICU_GRP_NSR ; 
 unsigned int ICU_GRP_REI ; 
 unsigned int ICU_GRP_SEI ; 
 unsigned int ICU_GRP_SR ; 
 unsigned long ICU_MAX_IRQS ; 
 unsigned int IRQ_TYPE_SENSE_MASK ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned long) ; 

__attribute__((used)) static int
mvebu_icu_irq_domain_translate(struct irq_domain *d, struct irq_fwspec *fwspec,
			       unsigned long *hwirq, unsigned int *type)
{
	struct mvebu_icu *icu = d->host_data;
	unsigned int icu_group;

	/* Check the count of the parameters in dt */
	if (WARN_ON(fwspec->param_count < 3)) {
		dev_err(icu->dev, "wrong ICU parameter count %d\n",
			fwspec->param_count);
		return -EINVAL;
	}

	/* Only ICU group type is handled */
	icu_group = fwspec->param[0];
	if (icu_group != ICU_GRP_NSR && icu_group != ICU_GRP_SR &&
	    icu_group != ICU_GRP_SEI && icu_group != ICU_GRP_REI) {
		dev_err(icu->dev, "wrong ICU group type %x\n", icu_group);
		return -EINVAL;
	}

	*hwirq = fwspec->param[1];
	if (*hwirq >= ICU_MAX_IRQS) {
		dev_err(icu->dev, "invalid interrupt number %ld\n", *hwirq);
		return -EINVAL;
	}

	/* Mask the type to prevent wrong DT configuration */
	*type = fwspec->param[2] & IRQ_TYPE_SENSE_MASK;

	return 0;
}