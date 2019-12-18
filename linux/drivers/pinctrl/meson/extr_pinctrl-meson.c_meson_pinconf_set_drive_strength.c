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
typedef  int u16 ;
struct meson_pinctrl {int /*<<< orphan*/  reg_ds; int /*<<< orphan*/  dev; } ;
struct meson_bank {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 unsigned int MESON_PINCONF_DRV_2500UA ; 
 unsigned int MESON_PINCONF_DRV_3000UA ; 
 unsigned int MESON_PINCONF_DRV_4000UA ; 
 unsigned int MESON_PINCONF_DRV_500UA ; 
 int /*<<< orphan*/  REG_DS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn_once (int /*<<< orphan*/ ,char*,unsigned int,int) ; 
 int /*<<< orphan*/  meson_calc_reg_and_bit (struct meson_bank*,unsigned int,int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 
 int meson_get_bank (struct meson_pinctrl*,unsigned int,struct meson_bank**) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,unsigned int,int,unsigned int) ; 

__attribute__((used)) static int meson_pinconf_set_drive_strength(struct meson_pinctrl *pc,
					    unsigned int pin,
					    u16 drive_strength_ua)
{
	struct meson_bank *bank;
	unsigned int reg, bit, ds_val;
	int ret;

	if (!pc->reg_ds) {
		dev_err(pc->dev, "drive-strength not supported\n");
		return -ENOTSUPP;
	}

	ret = meson_get_bank(pc, pin, &bank);
	if (ret)
		return ret;

	meson_calc_reg_and_bit(bank, pin, REG_DS, &reg, &bit);
	bit = bit << 1;

	if (drive_strength_ua <= 500) {
		ds_val = MESON_PINCONF_DRV_500UA;
	} else if (drive_strength_ua <= 2500) {
		ds_val = MESON_PINCONF_DRV_2500UA;
	} else if (drive_strength_ua <= 3000) {
		ds_val = MESON_PINCONF_DRV_3000UA;
	} else if (drive_strength_ua <= 4000) {
		ds_val = MESON_PINCONF_DRV_4000UA;
	} else {
		dev_warn_once(pc->dev,
			      "pin %u: invalid drive-strength : %d , default to 4mA\n",
			      pin, drive_strength_ua);
		ds_val = MESON_PINCONF_DRV_4000UA;
	}

	ret = regmap_update_bits(pc->reg_ds, reg, 0x3 << bit, ds_val << bit);
	if (ret)
		return ret;

	return 0;
}