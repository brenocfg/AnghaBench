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
struct gpio_chip {scalar_t__ base; } ;
struct atlas7_gpio_chip {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __atlas7_gpio_irq_mask (struct atlas7_gpio_chip*,unsigned int) ; 
 int /*<<< orphan*/  __atlas7_gpio_set_input (struct atlas7_gpio_chip*,unsigned int) ; 
 struct atlas7_gpio_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  pinctrl_gpio_free (scalar_t__) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void atlas7_gpio_free(struct gpio_chip *chip,
				unsigned int gpio)
{
	struct atlas7_gpio_chip *a7gc = gpiochip_get_data(chip);
	unsigned long flags;

	raw_spin_lock_irqsave(&a7gc->lock, flags);

	__atlas7_gpio_irq_mask(a7gc, gpio);
	__atlas7_gpio_set_input(a7gc, gpio);

	raw_spin_unlock_irqrestore(&a7gc->lock, flags);

	pinctrl_gpio_free(chip->base + gpio);
}