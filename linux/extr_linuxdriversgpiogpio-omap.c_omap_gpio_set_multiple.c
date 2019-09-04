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
struct gpio_bank {int /*<<< orphan*/  lock; int /*<<< orphan*/  (* set_dataout_multiple ) (struct gpio_bank*,unsigned long*,unsigned long*) ;} ;

/* Variables and functions */
 struct gpio_bank* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct gpio_bank*,unsigned long*,unsigned long*) ; 

__attribute__((used)) static void omap_gpio_set_multiple(struct gpio_chip *chip, unsigned long *mask,
				   unsigned long *bits)
{
	struct gpio_bank *bank = gpiochip_get_data(chip);
	unsigned long flags;

	raw_spin_lock_irqsave(&bank->lock, flags);
	bank->set_dataout_multiple(bank, mask, bits);
	raw_spin_unlock_irqrestore(&bank->lock, flags);
}