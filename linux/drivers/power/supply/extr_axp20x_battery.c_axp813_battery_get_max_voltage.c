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
struct axp20x_batt_ps {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXP20X_CHRG_CTRL1 ; 
#define  AXP20X_CHRG_CTRL1_TGT_4_15V 131 
#define  AXP20X_CHRG_CTRL1_TGT_4_1V 130 
#define  AXP20X_CHRG_CTRL1_TGT_4_2V 129 
 int AXP20X_CHRG_CTRL1_TGT_VOLT ; 
#define  AXP813_CHRG_CTRL1_TGT_4_35V 128 
 int EINVAL ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int axp813_battery_get_max_voltage(struct axp20x_batt_ps *axp20x_batt,
					  int *val)
{
	int ret, reg;

	ret = regmap_read(axp20x_batt->regmap, AXP20X_CHRG_CTRL1, &reg);
	if (ret)
		return ret;

	switch (reg & AXP20X_CHRG_CTRL1_TGT_VOLT) {
	case AXP20X_CHRG_CTRL1_TGT_4_1V:
		*val = 4100000;
		break;
	case AXP20X_CHRG_CTRL1_TGT_4_15V:
		*val = 4150000;
		break;
	case AXP20X_CHRG_CTRL1_TGT_4_2V:
		*val = 4200000;
		break;
	case AXP813_CHRG_CTRL1_TGT_4_35V:
		*val = 4350000;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}