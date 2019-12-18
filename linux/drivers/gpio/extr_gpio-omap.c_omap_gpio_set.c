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
struct gpio_bank {int /*<<< orphan*/  lock; int /*<<< orphan*/  (* set_dataout ) (struct gpio_bank*,unsigned int,int) ;} ;

/* Variables and functions */
 struct gpio_bank* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct gpio_bank*,unsigned int,int) ; 

__attribute__((used)) static void omap_gpio_set(struct gpio_chip *chip, unsigned offset, int value)
{
	struct gpio_bank *bank;
	unsigned long flags;

	bank = gpiochip_get_data(chip);
	raw_spin_lock_irqsave(&bank->lock, flags);
	bank->set_dataout(bank, offset, value);
	raw_spin_unlock_irqrestore(&bank->lock, flags);
}