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
struct mvebu_icu_msi_data {TYPE_1__* subset_data; } ;
struct mvebu_icu {int /*<<< orphan*/  dev; } ;
struct irq_fwspec {unsigned int param_count; unsigned long* param; } ;
struct irq_domain {int dummy; } ;
struct TYPE_2__ {scalar_t__ icu_group; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int ICU_GRP_NSR ; 
 scalar_t__ ICU_GRP_SEI ; 
 unsigned long ICU_MAX_IRQS ; 
 unsigned int IRQ_TYPE_EDGE_RISING ; 
 unsigned int IRQ_TYPE_SENSE_MASK ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned long) ; 
 int /*<<< orphan*/  legacy_bindings ; 
 void* platform_msi_get_host_data (struct irq_domain*) ; 
 scalar_t__ static_branch_unlikely (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mvebu_icu_irq_domain_translate(struct irq_domain *d, struct irq_fwspec *fwspec,
			       unsigned long *hwirq, unsigned int *type)
{
	struct mvebu_icu_msi_data *msi_data = platform_msi_get_host_data(d);
	struct mvebu_icu *icu = platform_msi_get_host_data(d);
	unsigned int param_count = static_branch_unlikely(&legacy_bindings) ? 3 : 2;

	/* Check the count of the parameters in dt */
	if (WARN_ON(fwspec->param_count != param_count)) {
		dev_err(icu->dev, "wrong ICU parameter count %d\n",
			fwspec->param_count);
		return -EINVAL;
	}

	if (static_branch_unlikely(&legacy_bindings)) {
		*hwirq = fwspec->param[1];
		*type = fwspec->param[2] & IRQ_TYPE_SENSE_MASK;
		if (fwspec->param[0] != ICU_GRP_NSR) {
			dev_err(icu->dev, "wrong ICU group type %x\n",
				fwspec->param[0]);
			return -EINVAL;
		}
	} else {
		*hwirq = fwspec->param[0];
		*type = fwspec->param[1] & IRQ_TYPE_SENSE_MASK;

		/*
		 * The ICU receives level interrupts. While the NSR are also
		 * level interrupts, SEI are edge interrupts. Force the type
		 * here in this case. Please note that this makes the interrupt
		 * handling unreliable.
		 */
		if (msi_data->subset_data->icu_group == ICU_GRP_SEI)
			*type = IRQ_TYPE_EDGE_RISING;
	}

	if (*hwirq >= ICU_MAX_IRQS) {
		dev_err(icu->dev, "invalid interrupt number %ld\n", *hwirq);
		return -EINVAL;
	}

	return 0;
}