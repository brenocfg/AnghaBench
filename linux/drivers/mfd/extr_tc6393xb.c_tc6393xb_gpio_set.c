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
struct tc6393xb {int /*<<< orphan*/  lock; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __tc6393xb_gpio_set (struct gpio_chip*,unsigned int,int) ; 
 struct tc6393xb* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void tc6393xb_gpio_set(struct gpio_chip *chip,
		unsigned offset, int value)
{
	struct tc6393xb *tc6393xb = gpiochip_get_data(chip);
	unsigned long flags;

	raw_spin_lock_irqsave(&tc6393xb->lock, flags);

	__tc6393xb_gpio_set(chip, offset, value);

	raw_spin_unlock_irqrestore(&tc6393xb->lock, flags);
}