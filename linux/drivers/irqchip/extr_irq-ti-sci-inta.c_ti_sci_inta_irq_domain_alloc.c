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
struct irq_domain {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  hwirq; } ;
typedef  TYPE_1__ msi_alloc_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  irq_domain_set_info (struct irq_domain*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ti_sci_inta_irq_chip ; 

__attribute__((used)) static int ti_sci_inta_irq_domain_alloc(struct irq_domain *domain,
					unsigned int virq, unsigned int nr_irqs,
					void *data)
{
	msi_alloc_info_t *arg = data;

	irq_domain_set_info(domain, virq, arg->hwirq, &ti_sci_inta_irq_chip,
			    NULL, handle_edge_irq, NULL, NULL);

	return 0;
}