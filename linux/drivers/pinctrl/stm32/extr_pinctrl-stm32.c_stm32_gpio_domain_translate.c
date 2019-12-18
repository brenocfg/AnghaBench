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
 unsigned long STM32_GPIO_IRQ_LINE ; 

__attribute__((used)) static int stm32_gpio_domain_translate(struct irq_domain *d,
				       struct irq_fwspec *fwspec,
				       unsigned long *hwirq,
				       unsigned int *type)
{
	if ((fwspec->param_count != 2) ||
	    (fwspec->param[0] >= STM32_GPIO_IRQ_LINE))
		return -EINVAL;

	*hwirq = fwspec->param[0];
	*type = fwspec->param[1];
	return 0;
}