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
struct tb10x_gpio {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int /*<<< orphan*/  OFFSET_TO_REG_DATA ; 
 struct tb10x_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int tb10x_reg_read (struct tb10x_gpio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tb10x_gpio_get(struct gpio_chip *chip, unsigned offset)
{
	struct tb10x_gpio *tb10x_gpio = gpiochip_get_data(chip);
	int val;

	val = tb10x_reg_read(tb10x_gpio, OFFSET_TO_REG_DATA);

	if (val & BIT(offset))
		return 1;
	else
		return 0;
}