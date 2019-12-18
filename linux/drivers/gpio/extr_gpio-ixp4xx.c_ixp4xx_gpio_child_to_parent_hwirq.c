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
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int IRQ_TYPE_LEVEL_HIGH ; 

__attribute__((used)) static int ixp4xx_gpio_child_to_parent_hwirq(struct gpio_chip *gc,
					     unsigned int child,
					     unsigned int child_type,
					     unsigned int *parent,
					     unsigned int *parent_type)
{
	/* All these interrupts are level high in the CPU */
	*parent_type = IRQ_TYPE_LEVEL_HIGH;

	/* GPIO lines 0..12 have dedicated IRQs */
	if (child == 0) {
		*parent = 6;
		return 0;
	}
	if (child == 1) {
		*parent = 7;
		return 0;
	}
	if (child >= 2 && child <= 12) {
		*parent = child + 17;
		return 0;
	}
	return -EINVAL;
}