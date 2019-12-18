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
struct meson_pinctrl {int /*<<< orphan*/  reg_pull; int /*<<< orphan*/  reg_pullen; } ;
struct meson_bank {int dummy; } ;

/* Variables and functions */
 unsigned int BIT (unsigned int) ; 
 int PIN_CONFIG_BIAS_DISABLE ; 
 int PIN_CONFIG_BIAS_PULL_DOWN ; 
 int PIN_CONFIG_BIAS_PULL_UP ; 
 int /*<<< orphan*/  REG_PULL ; 
 int /*<<< orphan*/  REG_PULLEN ; 
 int /*<<< orphan*/  meson_calc_reg_and_bit (struct meson_bank*,unsigned int,int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 
 int meson_get_bank (struct meson_pinctrl*,unsigned int,struct meson_bank**) ; 
 int regmap_read (int /*<<< orphan*/ ,unsigned int,unsigned int*) ; 

__attribute__((used)) static int meson_pinconf_get_pull(struct meson_pinctrl *pc, unsigned int pin)
{
	struct meson_bank *bank;
	unsigned int reg, bit, val;
	int ret, conf;

	ret = meson_get_bank(pc, pin, &bank);
	if (ret)
		return ret;

	meson_calc_reg_and_bit(bank, pin, REG_PULLEN, &reg, &bit);

	ret = regmap_read(pc->reg_pullen, reg, &val);
	if (ret)
		return ret;

	if (!(val & BIT(bit))) {
		conf = PIN_CONFIG_BIAS_DISABLE;
	} else {
		meson_calc_reg_and_bit(bank, pin, REG_PULL, &reg, &bit);

		ret = regmap_read(pc->reg_pull, reg, &val);
		if (ret)
			return ret;

		if (val & BIT(bit))
			conf = PIN_CONFIG_BIAS_PULL_UP;
		else
			conf = PIN_CONFIG_BIAS_PULL_DOWN;
	}

	return conf;
}