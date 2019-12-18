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
 int /*<<< orphan*/  REG_ALT (int,struct ocelot_pinctrl*,unsigned int) ; 
 struct ocelot_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocelot_gpio_request_enable(struct pinctrl_dev *pctldev,
				      struct pinctrl_gpio_range *range,
				      unsigned int offset)
{
	struct ocelot_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);
	unsigned int p = offset % 32;

	regmap_update_bits(info->map, REG_ALT(0, info, offset),
			   BIT(p), 0);
	regmap_update_bits(info->map, REG_ALT(1, info, offset),
			   BIT(p), 0);

	return 0;
}