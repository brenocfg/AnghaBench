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
struct meson_pinctrl {int /*<<< orphan*/  reg_gpio; } ;
struct meson_bank {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 int /*<<< orphan*/  meson_calc_reg_and_bit (struct meson_bank*,unsigned int,unsigned int,unsigned int*,unsigned int*) ; 
 int meson_get_bank (struct meson_pinctrl*,unsigned int,struct meson_bank**) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int meson_pinconf_set_gpio_bit(struct meson_pinctrl *pc,
				      unsigned int pin,
				      unsigned int reg_type,
				      bool arg)
{
	struct meson_bank *bank;
	unsigned int reg, bit;
	int ret;

	ret = meson_get_bank(pc, pin, &bank);
	if (ret)
		return ret;

	meson_calc_reg_and_bit(bank, pin, reg_type, &reg, &bit);
	return regmap_update_bits(pc->reg_gpio, reg, BIT(bit),
				  arg ? BIT(bit) : 0);
}