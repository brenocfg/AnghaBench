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
 int AXP20X_CHRG_CTRL1_TGT_4_15V ; 
 int AXP20X_CHRG_CTRL1_TGT_4_1V ; 
 int AXP20X_CHRG_CTRL1_TGT_4_2V ; 
 int /*<<< orphan*/  AXP20X_CHRG_CTRL1_TGT_VOLT ; 
 int EINVAL ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int axp20x_battery_set_max_voltage(struct axp20x_batt_ps *axp20x_batt,
					  int val)
{
	switch (val) {
	case 4100000:
		val = AXP20X_CHRG_CTRL1_TGT_4_1V;
		break;

	case 4150000:
		val = AXP20X_CHRG_CTRL1_TGT_4_15V;
		break;

	case 4200000:
		val = AXP20X_CHRG_CTRL1_TGT_4_2V;
		break;

	default:
		/*
		 * AXP20x max voltage can be set to 4.36V and AXP22X max voltage
		 * can be set to 4.22V and 4.24V, but these voltages are too
		 * high for Lithium based batteries (AXP PMICs are supposed to
		 * be used with these kinds of battery).
		 */
		return -EINVAL;
	}

	return regmap_update_bits(axp20x_batt->regmap, AXP20X_CHRG_CTRL1,
				  AXP20X_CHRG_CTRL1_TGT_VOLT, val);
}