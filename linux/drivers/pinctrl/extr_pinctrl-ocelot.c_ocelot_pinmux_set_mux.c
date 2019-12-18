#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pinctrl_dev {int dummy; } ;
struct ocelot_pinctrl {int /*<<< orphan*/  map; TYPE_1__* desc; } ;
struct ocelot_pin_caps {int pin; } ;
struct TYPE_4__ {struct ocelot_pin_caps* drv_data; } ;
struct TYPE_3__ {TYPE_2__* pins; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  REG_ALT (int,struct ocelot_pinctrl*,int) ; 
 int ocelot_pin_function_idx (struct ocelot_pinctrl*,unsigned int,unsigned int) ; 
 struct ocelot_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ocelot_pinmux_set_mux(struct pinctrl_dev *pctldev,
				 unsigned int selector, unsigned int group)
{
	struct ocelot_pinctrl *info = pinctrl_dev_get_drvdata(pctldev);
	struct ocelot_pin_caps *pin = info->desc->pins[group].drv_data;
	unsigned int p = pin->pin % 32;
	int f;

	f = ocelot_pin_function_idx(info, group, selector);
	if (f < 0)
		return -EINVAL;

	/*
	 * f is encoded on two bits.
	 * bit 0 of f goes in BIT(pin) of ALT[0], bit 1 of f goes in BIT(pin) of
	 * ALT[1]
	 * This is racy because both registers can't be updated at the same time
	 * but it doesn't matter much for now.
	 */
	regmap_update_bits(info->map, REG_ALT(0, info, pin->pin),
			   BIT(p), f << p);
	regmap_update_bits(info->map, REG_ALT(1, info, pin->pin),
			   BIT(p), f << (p - 1));

	return 0;
}