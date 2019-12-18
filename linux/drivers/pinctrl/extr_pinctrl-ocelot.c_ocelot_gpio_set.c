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
struct ocelot_pinctrl {int /*<<< orphan*/  map; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 int /*<<< orphan*/  OCELOT_GPIO_OUT_CLR ; 
 int /*<<< orphan*/  OCELOT_GPIO_OUT_SET ; 
 int /*<<< orphan*/  REG (int /*<<< orphan*/ ,struct ocelot_pinctrl*,unsigned int) ; 
 struct ocelot_pinctrl* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ocelot_gpio_set(struct gpio_chip *chip, unsigned int offset,
			    int value)
{
	struct ocelot_pinctrl *info = gpiochip_get_data(chip);

	if (value)
		regmap_write(info->map, REG(OCELOT_GPIO_OUT_SET, info, offset),
			     BIT(offset % 32));
	else
		regmap_write(info->map, REG(OCELOT_GPIO_OUT_CLR, info, offset),
			     BIT(offset % 32));
}