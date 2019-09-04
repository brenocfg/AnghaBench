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
struct irq_data {int dummy; } ;

/* Variables and functions */
 struct irq_data* irq_domain_get_irq_data (struct irq_domain*,unsigned int) ; 
 int /*<<< orphan*/  irq_domain_reset_irq_data (struct irq_data*) ; 

__attribute__((used)) static void stm32_exti_free(struct irq_domain *d, unsigned int virq,
			    unsigned int nr_irqs)
{
	struct irq_data *data = irq_domain_get_irq_data(d, virq);

	irq_domain_reset_irq_data(data);
}