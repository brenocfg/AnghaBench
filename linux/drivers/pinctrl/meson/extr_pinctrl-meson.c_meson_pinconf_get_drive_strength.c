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
struct meson_pinctrl {int /*<<< orphan*/  reg_ds; } ;
struct meson_bank {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
#define  MESON_PINCONF_DRV_2500UA 131 
#define  MESON_PINCONF_DRV_3000UA 130 
#define  MESON_PINCONF_DRV_4000UA 129 
#define  MESON_PINCONF_DRV_500UA 128 
 int /*<<< orphan*/  REG_DS ; 
 int /*<<< orphan*/  meson_calc_reg_and_bit (struct meson_bank*,unsigned int,int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 
 int meson_get_bank (struct meson_pinctrl*,unsigned int,struct meson_bank**) ; 
 int regmap_read (int /*<<< orphan*/ ,unsigned int,unsigned int*) ; 

__attribute__((used)) static int meson_pinconf_get_drive_strength(struct meson_pinctrl *pc,
					    unsigned int pin,
					    u16 *drive_strength_ua)
{
	struct meson_bank *bank;
	unsigned int reg, bit;
	unsigned int val;
	int ret;

	if (!pc->reg_ds)
		return -ENOTSUPP;

	ret = meson_get_bank(pc, pin, &bank);
	if (ret)
		return ret;

	meson_calc_reg_and_bit(bank, pin, REG_DS, &reg, &bit);

	ret = regmap_read(pc->reg_ds, reg, &val);
	if (ret)
		return ret;

	switch ((val >> bit) & 0x3) {
	case MESON_PINCONF_DRV_500UA:
		*drive_strength_ua = 500;
		break;
	case MESON_PINCONF_DRV_2500UA:
		*drive_strength_ua = 2500;
		break;
	case MESON_PINCONF_DRV_3000UA:
		*drive_strength_ua = 3000;
		break;
	case MESON_PINCONF_DRV_4000UA:
		*drive_strength_ua = 4000;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}