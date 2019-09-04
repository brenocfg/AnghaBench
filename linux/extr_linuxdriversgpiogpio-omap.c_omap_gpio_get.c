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
struct gpio_bank {int dummy; } ;

/* Variables and functions */
 struct gpio_bank* gpiochip_get_data (struct gpio_chip*) ; 
 int omap_get_gpio_datain (struct gpio_bank*,unsigned int) ; 
 int omap_get_gpio_dataout (struct gpio_bank*,unsigned int) ; 
 scalar_t__ omap_gpio_is_input (struct gpio_bank*,unsigned int) ; 

__attribute__((used)) static int omap_gpio_get(struct gpio_chip *chip, unsigned offset)
{
	struct gpio_bank *bank;

	bank = gpiochip_get_data(chip);

	if (omap_gpio_is_input(bank, offset))
		return omap_get_gpio_datain(bank, offset);
	else
		return omap_get_gpio_dataout(bank, offset);
}