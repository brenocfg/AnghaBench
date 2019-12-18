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
struct gpio_bank {int /*<<< orphan*/  lock; int /*<<< orphan*/  mod_usage; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 struct gpio_bank* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  omap_enable_gpio_module (struct gpio_bank*,unsigned int) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int omap_gpio_request(struct gpio_chip *chip, unsigned offset)
{
	struct gpio_bank *bank = gpiochip_get_data(chip);
	unsigned long flags;

	pm_runtime_get_sync(chip->parent);

	raw_spin_lock_irqsave(&bank->lock, flags);
	omap_enable_gpio_module(bank, offset);
	bank->mod_usage |= BIT(offset);
	raw_spin_unlock_irqrestore(&bank->lock, flags);

	return 0;
}