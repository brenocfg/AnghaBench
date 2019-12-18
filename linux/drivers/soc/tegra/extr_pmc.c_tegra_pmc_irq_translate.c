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
struct irq_fwspec {int param_count; unsigned long* param; } ;
struct irq_domain {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 

__attribute__((used)) static int tegra_pmc_irq_translate(struct irq_domain *domain,
				   struct irq_fwspec *fwspec,
				   unsigned long *hwirq,
				   unsigned int *type)
{
	if (WARN_ON(fwspec->param_count < 2))
		return -EINVAL;

	*hwirq = fwspec->param[0];
	*type = fwspec->param[1];

	return 0;
}