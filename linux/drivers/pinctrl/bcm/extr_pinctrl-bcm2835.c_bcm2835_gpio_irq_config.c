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
struct bcm2835_pinctrl {int* irq_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPFEN0 ; 
 int /*<<< orphan*/  GPHEN0 ; 
 int /*<<< orphan*/  GPLEN0 ; 
 int /*<<< orphan*/  GPREN0 ; 
#define  IRQ_TYPE_EDGE_BOTH 132 
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 int /*<<< orphan*/  __bcm2835_gpio_irq_config (struct bcm2835_pinctrl*,int /*<<< orphan*/ ,unsigned int,int) ; 

__attribute__((used)) static void bcm2835_gpio_irq_config(struct bcm2835_pinctrl *pc,
	unsigned offset, bool enable)
{
	switch (pc->irq_type[offset]) {
	case IRQ_TYPE_EDGE_RISING:
		__bcm2835_gpio_irq_config(pc, GPREN0, offset, enable);
		break;

	case IRQ_TYPE_EDGE_FALLING:
		__bcm2835_gpio_irq_config(pc, GPFEN0, offset, enable);
		break;

	case IRQ_TYPE_EDGE_BOTH:
		__bcm2835_gpio_irq_config(pc, GPREN0, offset, enable);
		__bcm2835_gpio_irq_config(pc, GPFEN0, offset, enable);
		break;

	case IRQ_TYPE_LEVEL_HIGH:
		__bcm2835_gpio_irq_config(pc, GPHEN0, offset, enable);
		break;

	case IRQ_TYPE_LEVEL_LOW:
		__bcm2835_gpio_irq_config(pc, GPLEN0, offset, enable);
		break;
	}
}