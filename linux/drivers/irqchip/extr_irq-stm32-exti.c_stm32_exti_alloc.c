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
struct irq_fwspec {int /*<<< orphan*/ * param; } ;
struct irq_domain {int dummy; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  irq_map_generic_chip (struct irq_domain*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_exti_alloc(struct irq_domain *d, unsigned int virq,
			    unsigned int nr_irqs, void *data)
{
	struct irq_fwspec *fwspec = data;
	irq_hw_number_t hwirq;

	hwirq = fwspec->param[0];

	irq_map_generic_chip(d, virq, hwirq);

	return 0;
}