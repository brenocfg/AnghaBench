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
struct TYPE_2__ {scalar_t__ ngpio; } ;
struct thunderx_gpio {TYPE_1__ chip; } ;
struct irq_fwspec {int param_count; scalar_t__* param; } ;
struct irq_domain {struct thunderx_gpio* host_data; } ;
typedef  scalar_t__ irq_hw_number_t ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int IRQ_TYPE_SENSE_MASK ; 
 scalar_t__ WARN_ON (int) ; 

__attribute__((used)) static int thunderx_gpio_irq_translate(struct irq_domain *d,
				       struct irq_fwspec *fwspec,
				       irq_hw_number_t *hwirq,
				       unsigned int *type)
{
	struct thunderx_gpio *txgpio = d->host_data;

	if (WARN_ON(fwspec->param_count < 2))
		return -EINVAL;
	if (fwspec->param[0] >= txgpio->chip.ngpio)
		return -EINVAL;
	*hwirq = fwspec->param[0];
	*type = fwspec->param[1] & IRQ_TYPE_SENSE_MASK;
	return 0;
}