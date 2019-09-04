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
struct thunderx_line {int /*<<< orphan*/  line; } ;
struct irq_domain {int dummy; } ;

/* Variables and functions */
 int irq_domain_set_hwirq_and_chip (struct irq_domain*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct thunderx_line*) ; 
 int /*<<< orphan*/  thunderx_gpio_irq_chip ; 

__attribute__((used)) static int thunderx_gpio_irq_alloc(struct irq_domain *d, unsigned int virq,
				   unsigned int nr_irqs, void *arg)
{
	struct thunderx_line *txline = arg;

	return irq_domain_set_hwirq_and_chip(d, virq, txline->line,
					     &thunderx_gpio_irq_chip, txline);
}