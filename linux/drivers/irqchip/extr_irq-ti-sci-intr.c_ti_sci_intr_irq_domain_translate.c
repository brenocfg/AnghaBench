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
struct ti_sci_intr_irq_domain {unsigned int type; } ;
struct irq_fwspec {int param_count; int /*<<< orphan*/ * param; } ;
struct irq_domain {struct ti_sci_intr_irq_domain* host_data; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long TO_HWIRQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ti_sci_intr_irq_domain_translate(struct irq_domain *domain,
					    struct irq_fwspec *fwspec,
					    unsigned long *hwirq,
					    unsigned int *type)
{
	struct ti_sci_intr_irq_domain *intr = domain->host_data;

	if (fwspec->param_count != 2)
		return -EINVAL;

	*hwirq = TO_HWIRQ(fwspec->param[0], fwspec->param[1]);
	*type = intr->type;

	return 0;
}