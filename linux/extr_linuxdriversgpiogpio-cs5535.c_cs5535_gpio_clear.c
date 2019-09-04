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
struct cs5535_gpio_chip {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cs5535_gpio_clear (struct cs5535_gpio_chip*,unsigned int,unsigned int) ; 
 struct cs5535_gpio_chip cs5535_gpio_chip ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void cs5535_gpio_clear(unsigned offset, unsigned int reg)
{
	struct cs5535_gpio_chip *chip = &cs5535_gpio_chip;
	unsigned long flags;

	spin_lock_irqsave(&chip->lock, flags);
	__cs5535_gpio_clear(chip, offset, reg);
	spin_unlock_irqrestore(&chip->lock, flags);
}