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
struct gpio_chip {int /*<<< orphan*/  parent; } ;
struct gpio_bank {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,unsigned int,unsigned int,int) ; 
 struct gpio_bank* gpiochip_get_data (struct gpio_chip*) ; 
 int omap2_set_gpio_debounce (struct gpio_bank*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int omap_gpio_debounce(struct gpio_chip *chip, unsigned offset,
			      unsigned debounce)
{
	struct gpio_bank *bank;
	unsigned long flags;
	int ret;

	bank = gpiochip_get_data(chip);

	raw_spin_lock_irqsave(&bank->lock, flags);
	ret = omap2_set_gpio_debounce(bank, offset, debounce);
	raw_spin_unlock_irqrestore(&bank->lock, flags);

	if (ret)
		dev_info(chip->parent,
			 "Could not set line %u debounce to %u microseconds (%d)",
			 offset, debounce, ret);

	return ret;
}