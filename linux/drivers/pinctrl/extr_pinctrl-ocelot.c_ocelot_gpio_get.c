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
 unsigned int BIT (unsigned int) ; 
 int /*<<< orphan*/  OCELOT_GPIO_IN ; 
 int /*<<< orphan*/  REG (int /*<<< orphan*/ ,struct ocelot_pinctrl*,unsigned int) ; 
 struct ocelot_pinctrl* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int ocelot_gpio_get(struct gpio_chip *chip, unsigned int offset)
{
	struct ocelot_pinctrl *info = gpiochip_get_data(chip);
	unsigned int val;

	regmap_read(info->map, REG(OCELOT_GPIO_IN, info, offset), &val);

	return !!(val & BIT(offset % 32));
}