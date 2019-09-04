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

/* Variables and functions */
 unsigned int IRQ_TYPE_EDGE_FALLING ; 
 unsigned int IRQ_TYPE_EDGE_RISING ; 
 unsigned int IRQ_TYPE_LEVEL_HIGH ; 
 unsigned int IRQ_TYPE_LEVEL_LOW ; 
 unsigned int IRQ_TYPE_SENSE_MASK ; 

__attribute__((used)) static unsigned int meson_gpio_irq_type_output(unsigned int type)
{
	unsigned int sense = type & IRQ_TYPE_SENSE_MASK;

	type &= ~IRQ_TYPE_SENSE_MASK;

	/*
	 * The polarity of the signal provided to the GIC should always
	 * be high.
	 */
	if (sense & (IRQ_TYPE_LEVEL_HIGH | IRQ_TYPE_LEVEL_LOW))
		type |= IRQ_TYPE_LEVEL_HIGH;
	else if (sense & (IRQ_TYPE_EDGE_RISING | IRQ_TYPE_EDGE_FALLING))
		type |= IRQ_TYPE_EDGE_RISING;

	return type;
}