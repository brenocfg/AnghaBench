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
 int /*<<< orphan*/  GPEDS0 ; 
 unsigned int GPIO_REG_OFFSET (unsigned int) ; 
 unsigned int GPIO_REG_SHIFT (unsigned int) ; 
 int /*<<< orphan*/  bcm2835_gpio_irq_config (struct bcm2835_pinctrl*,unsigned int,int) ; 
 int /*<<< orphan*/  bcm2835_gpio_set_bit (struct bcm2835_pinctrl*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  clear_bit (unsigned int,int /*<<< orphan*/ *) ; 
 struct bcm2835_pinctrl* gpiochip_get_data (struct gpio_chip*) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 unsigned int irqd_to_hwirq (struct irq_data*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void bcm2835_gpio_irq_disable(struct irq_data *data)
{
	struct gpio_chip *chip = irq_data_get_irq_chip_data(data);
	struct bcm2835_pinctrl *pc = gpiochip_get_data(chip);
	unsigned gpio = irqd_to_hwirq(data);
	unsigned offset = GPIO_REG_SHIFT(gpio);
	unsigned bank = GPIO_REG_OFFSET(gpio);
	unsigned long flags;

	raw_spin_lock_irqsave(&pc->irq_lock[bank], flags);
	bcm2835_gpio_irq_config(pc, gpio, false);
	/* Clear events that were latched prior to clearing event sources */
	bcm2835_gpio_set_bit(pc, GPEDS0, gpio);
	clear_bit(offset, &pc->enabled_irq_map[bank]);
	raw_spin_unlock_irqrestore(&pc->irq_lock[bank], flags);
}