#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gpio_chip {int dummy; } ;
struct gpio_bank {TYPE_1__* regs; scalar_t__ base; } ;
struct TYPE_2__ {scalar_t__ direction; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 struct gpio_bank* gpiochip_get_data (struct gpio_chip*) ; 
 int readl_relaxed (scalar_t__) ; 

__attribute__((used)) static int omap_gpio_get_direction(struct gpio_chip *chip, unsigned offset)
{
	struct gpio_bank *bank = gpiochip_get_data(chip);

	return !!(readl_relaxed(bank->base + bank->regs->direction) &
		  BIT(offset));
}