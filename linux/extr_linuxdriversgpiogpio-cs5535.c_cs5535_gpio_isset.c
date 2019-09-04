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
struct cs5535_gpio_chip {int /*<<< orphan*/  lock; scalar_t__ base; } ;

/* Variables and functions */
 struct cs5535_gpio_chip cs5535_gpio_chip ; 
 long inl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int cs5535_gpio_isset(unsigned offset, unsigned int reg)
{
	struct cs5535_gpio_chip *chip = &cs5535_gpio_chip;
	unsigned long flags;
	long val;

	spin_lock_irqsave(&chip->lock, flags);
	if (offset < 16)
		/* low bank register */
		val = inl(chip->base + reg);
	else {
		/* high bank register */
		val = inl(chip->base + 0x80 + reg);
		offset -= 16;
	}
	spin_unlock_irqrestore(&chip->lock, flags);

	return (val & (1 << offset)) ? 1 : 0;
}