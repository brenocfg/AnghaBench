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
struct pinctrl_gpio_range {int dummy; } ;
struct pinctrl_dev {int dummy; } ;
struct ocelot_pinctrl {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 int /*<<< orphan*/  OCELOT_GPIO_OE ; 
 int /*<<< orphan*/  REG (int /*<<< orphan*/ ,struct ocelot_pinctrl*,unsigned int) ; 
 struct ocelot_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocelot_gpio_set_direction(struct pinctrl_dev *pctldev,
				     struct pinctrl_gpio_range *range,
				     unsigned int pin, bool input)
{
	struct ocelot_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);
	unsigned int p = pin % 32;

	regmap_update_bits(info->map, REG(OCELOT_GPIO_OE, info, pin), BIT(p),
			   input ? 0 : BIT(p));

	return 0;
}