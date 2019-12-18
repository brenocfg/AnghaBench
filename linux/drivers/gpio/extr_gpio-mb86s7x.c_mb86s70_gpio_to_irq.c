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
struct gpio_chip {int /*<<< orphan*/  parent; } ;
struct TYPE_2__ {unsigned int hwirq; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_1__* irq_get_irq_data (int) ; 
 int platform_get_irq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mb86s70_gpio_to_irq(struct gpio_chip *gc, unsigned int offset)
{
	int irq, index;

	for (index = 0;; index++) {
		irq = platform_get_irq(to_platform_device(gc->parent), index);
		if (irq <= 0)
			break;
		if (irq_get_irq_data(irq)->hwirq == offset)
			return irq;
	}
	return -EINVAL;
}