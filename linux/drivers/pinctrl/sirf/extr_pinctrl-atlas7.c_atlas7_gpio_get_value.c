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
typedef  int u32 ;
struct gpio_chip {int dummy; } ;
struct atlas7_gpio_chip {int /*<<< orphan*/  lock; } ;
struct atlas7_gpio_bank {int gpio_offset; } ;

/* Variables and functions */
 int ATLAS7_GPIO_CTL_DATAIN_MASK ; 
 int /*<<< orphan*/  ATLAS7_GPIO_CTRL (struct atlas7_gpio_bank*,int) ; 
 struct atlas7_gpio_bank* atlas7_gpio_to_bank (struct atlas7_gpio_chip*,unsigned int) ; 
 struct atlas7_gpio_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atlas7_gpio_get_value(struct gpio_chip *chip,
					unsigned int gpio)
{
	struct atlas7_gpio_chip *a7gc = gpiochip_get_data(chip);
	struct atlas7_gpio_bank *bank;
	u32 val, pin_in_bank;
	unsigned long flags;

	bank = atlas7_gpio_to_bank(a7gc, gpio);
	pin_in_bank = gpio - bank->gpio_offset;

	raw_spin_lock_irqsave(&a7gc->lock, flags);

	val = readl(ATLAS7_GPIO_CTRL(bank, pin_in_bank));

	raw_spin_unlock_irqrestore(&a7gc->lock, flags);

	return !!(val & ATLAS7_GPIO_CTL_DATAIN_MASK);
}