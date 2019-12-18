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
struct irq_fwspec {int param_count; unsigned long* param; int /*<<< orphan*/  fwnode; } ;
struct irq_domain {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int IRQ_TYPE_NONE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ is_fwnode_irqchip (int /*<<< orphan*/ ) ; 
 scalar_t__ is_of_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ixp4xx_irq_domain_translate(struct irq_domain *domain,
				       struct irq_fwspec *fwspec,
				       unsigned long *hwirq,
				       unsigned int *type)
{
	/* We support standard DT translation */
	if (is_of_node(fwspec->fwnode) && fwspec->param_count == 2) {
		*hwirq = fwspec->param[0];
		*type = fwspec->param[1];
		return 0;
	}

	if (is_fwnode_irqchip(fwspec->fwnode)) {
		if (fwspec->param_count != 2)
			return -EINVAL;
		*hwirq = fwspec->param[0];
		*type = fwspec->param[1];
		WARN_ON(*type == IRQ_TYPE_NONE);
		return 0;
	}

	return -EINVAL;
}