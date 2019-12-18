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
struct irq_data {int dummy; } ;
struct gpio_chip {int dummy; } ;
struct bcm2835_pinctrl {int /*<<< orphan*/ * irq_lock; int /*<<< orphan*/ * enabled_irq_map; } ;

/* Variables and functions */
 unsigned int GPIO_REG_OFFSET (unsigned int) ; 
 unsigned int GPIO_REG_SHIFT (unsigned int) ; 
 unsigned int IRQ_TYPE_EDGE_BOTH ; 
 int __bcm2835_gpio_irq_set_type_disabled (struct bcm2835_pinctrl*,unsigned int,unsigned int) ; 
 int __bcm2835_gpio_irq_set_type_enabled (struct bcm2835_pinctrl*,unsigned int,unsigned int) ; 
 struct bcm2835_pinctrl* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  handle_level_irq ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irq_set_handler_locked (struct irq_data*,int /*<<< orphan*/ ) ; 
 unsigned int irqd_to_hwirq (struct irq_data*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcm2835_gpio_irq_set_type(struct irq_data *data, unsigned int type)
{
	struct gpio_chip *chip = irq_data_get_irq_chip_data(data);
	struct bcm2835_pinctrl *pc = gpiochip_get_data(chip);
	unsigned gpio = irqd_to_hwirq(data);
	unsigned offset = GPIO_REG_SHIFT(gpio);
	unsigned bank = GPIO_REG_OFFSET(gpio);
	unsigned long flags;
	int ret;

	raw_spin_lock_irqsave(&pc->irq_lock[bank], flags);

	if (test_bit(offset, &pc->enabled_irq_map[bank]))
		ret = __bcm2835_gpio_irq_set_type_enabled(pc, gpio, type);
	else
		ret = __bcm2835_gpio_irq_set_type_disabled(pc, gpio, type);

	if (type & IRQ_TYPE_EDGE_BOTH)
		irq_set_handler_locked(data, handle_edge_irq);
	else
		irq_set_handler_locked(data, handle_level_irq);

	raw_spin_unlock_irqrestore(&pc->irq_lock[bank], flags);

	return ret;
}