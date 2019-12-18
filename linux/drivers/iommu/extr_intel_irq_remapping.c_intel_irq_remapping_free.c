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
struct irq_domain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_free_irq_resources (struct irq_domain*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  irq_domain_free_irqs_common (struct irq_domain*,unsigned int,unsigned int) ; 

__attribute__((used)) static void intel_irq_remapping_free(struct irq_domain *domain,
				     unsigned int virq, unsigned int nr_irqs)
{
	intel_free_irq_resources(domain, virq, nr_irqs);
	irq_domain_free_irqs_common(domain, virq, nr_irqs);
}