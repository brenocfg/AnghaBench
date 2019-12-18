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
struct lpc18xx_gpio_pin_ic {int dummy; } ;
struct irq_fwspec {scalar_t__* param; int param_count; int /*<<< orphan*/  fwnode; } ;
struct irq_domain {TYPE_1__* parent; struct lpc18xx_gpio_pin_ic* host_data; } ;
typedef  scalar_t__ irq_hw_number_t ;
struct TYPE_2__ {int /*<<< orphan*/  fwnode; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ NR_LPC18XX_GPIO_PIN_IC_IRQS ; 
 int irq_domain_alloc_irqs_parent (struct irq_domain*,unsigned int,int,struct irq_fwspec*) ; 
 int irq_domain_set_hwirq_and_chip (struct irq_domain*,unsigned int,scalar_t__,int /*<<< orphan*/ *,struct lpc18xx_gpio_pin_ic*) ; 
 int /*<<< orphan*/  lpc18xx_gpio_pin_ic ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__,int) ; 

__attribute__((used)) static int lpc18xx_gpio_pin_ic_domain_alloc(struct irq_domain *domain,
					    unsigned int virq,
					    unsigned int nr_irqs, void *data)
{
	struct irq_fwspec parent_fwspec, *fwspec = data;
	struct lpc18xx_gpio_pin_ic *ic = domain->host_data;
	irq_hw_number_t hwirq;
	int ret;

	if (nr_irqs != 1)
		return -EINVAL;

	hwirq = fwspec->param[0];
	if (hwirq >= NR_LPC18XX_GPIO_PIN_IC_IRQS)
		return -EINVAL;

	/*
	 * All LPC18xx/LPC43xx GPIO pin hardware interrupts are translated
	 * into edge interrupts 32...39 on parent Cortex-M3/M4 NVIC
	 */
	parent_fwspec.fwnode = domain->parent->fwnode;
	parent_fwspec.param_count = 1;
	parent_fwspec.param[0] = hwirq + 32;

	ret = irq_domain_alloc_irqs_parent(domain, virq, 1, &parent_fwspec);
	if (ret < 0) {
		pr_err("failed to allocate parent irq %u: %d\n",
		       parent_fwspec.param[0], ret);
		return ret;
	}

	return irq_domain_set_hwirq_and_chip(domain, virq, hwirq,
					     &lpc18xx_gpio_pin_ic, ic);
}