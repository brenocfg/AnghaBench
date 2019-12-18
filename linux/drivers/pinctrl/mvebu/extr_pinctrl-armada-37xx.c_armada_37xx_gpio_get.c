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
struct armada_37xx_pinctrl {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned int BIT (unsigned int) ; 
 unsigned int INPUT_VAL ; 
 int /*<<< orphan*/  armada_37xx_update_reg (unsigned int*,unsigned int*) ; 
 struct armada_37xx_pinctrl* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,unsigned int,unsigned int*) ; 

__attribute__((used)) static int armada_37xx_gpio_get(struct gpio_chip *chip, unsigned int offset)
{
	struct armada_37xx_pinctrl *info = gpiochip_get_data(chip);
	unsigned int reg = INPUT_VAL;
	unsigned int val, mask;

	armada_37xx_update_reg(&reg, &offset);
	mask = BIT(offset);

	regmap_read(info->regmap, reg, &val);

	return (val & mask) != 0;
}