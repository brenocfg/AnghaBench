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
struct sirfsoc_gpio_chip {int dummy; } ;
struct sirfsoc_gpio_bank {int /*<<< orphan*/  lock; int /*<<< orphan*/  id; } ;
struct gpio_chip {unsigned int base; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  SIRFSOC_GPIO_CTRL (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  __sirfsoc_gpio_irq_mask (struct sirfsoc_gpio_chip*,struct sirfsoc_gpio_bank*,unsigned int) ; 
 struct sirfsoc_gpio_chip* gpiochip_get_data (struct gpio_chip*) ; 
 scalar_t__ pinctrl_gpio_request (unsigned int) ; 
 int /*<<< orphan*/  sirfsoc_gpio_set_input (struct sirfsoc_gpio_chip*,int /*<<< orphan*/ ) ; 
 struct sirfsoc_gpio_bank* sirfsoc_gpio_to_bank (struct sirfsoc_gpio_chip*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int sirfsoc_gpio_request(struct gpio_chip *chip, unsigned offset)
{
	struct sirfsoc_gpio_chip *sgpio = gpiochip_get_data(chip);
	struct sirfsoc_gpio_bank *bank = sirfsoc_gpio_to_bank(sgpio, offset);
	unsigned long flags;

	if (pinctrl_gpio_request(chip->base + offset))
		return -ENODEV;

	spin_lock_irqsave(&bank->lock, flags);

	/*
	 * default status:
	 * set direction as input and mask irq
	 */
	sirfsoc_gpio_set_input(sgpio, SIRFSOC_GPIO_CTRL(bank->id, offset));
	__sirfsoc_gpio_irq_mask(sgpio, bank, offset);

	spin_unlock_irqrestore(&bank->lock, flags);

	return 0;
}