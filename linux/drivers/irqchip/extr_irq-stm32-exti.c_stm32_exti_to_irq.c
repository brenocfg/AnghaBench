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
struct stm32_exti_drv_data {int irq_nr; struct stm32_desc_irq* desc_irqs; } ;
struct stm32_desc_irq {scalar_t__ exti; int irq_parent; } ;
typedef  scalar_t__ irq_hw_number_t ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int stm32_exti_to_irq(const struct stm32_exti_drv_data *drv_data,
			     irq_hw_number_t hwirq)
{
	const struct stm32_desc_irq *desc_irq;
	int i;

	if (!drv_data->desc_irqs)
		return -EINVAL;

	for (i = 0; i < drv_data->irq_nr; i++) {
		desc_irq = &drv_data->desc_irqs[i];
		if (desc_irq->exti == hwirq)
			return desc_irq->irq_parent;
	}

	return -EINVAL;
}