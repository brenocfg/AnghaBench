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
struct lp_gpio {int /*<<< orphan*/  lock; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LP_CONFIG1 ; 
 int OUT_LVL_BIT ; 
 struct lp_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int inl (unsigned long) ; 
 unsigned long lp_gpio_reg (struct gpio_chip*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (int,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void lp_gpio_set(struct gpio_chip *chip, unsigned offset, int value)
{
	struct lp_gpio *lg = gpiochip_get_data(chip);
	unsigned long reg = lp_gpio_reg(chip, offset, LP_CONFIG1);
	unsigned long flags;

	spin_lock_irqsave(&lg->lock, flags);

	if (value)
		outl(inl(reg) | OUT_LVL_BIT, reg);
	else
		outl(inl(reg) & ~OUT_LVL_BIT, reg);

	spin_unlock_irqrestore(&lg->lock, flags);
}