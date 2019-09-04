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
struct orion_gpio_chip {int /*<<< orphan*/  lock; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __set_level (struct orion_gpio_chip*,unsigned int,int) ; 
 struct orion_gpio_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void orion_gpio_set(struct gpio_chip *chip, unsigned pin, int value)
{
	struct orion_gpio_chip *ochip = gpiochip_get_data(chip);
	unsigned long flags;

	spin_lock_irqsave(&ochip->lock, flags);
	__set_level(ochip, pin, value);
	spin_unlock_irqrestore(&ochip->lock, flags);
}