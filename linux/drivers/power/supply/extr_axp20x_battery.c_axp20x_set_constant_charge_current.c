#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct axp20x_batt_ps {int max_ccc; int /*<<< orphan*/  regmap; TYPE_1__* data; } ;
struct TYPE_2__ {int ccc_offset; int ccc_scale; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXP20X_CHRG_CTRL1 ; 
 int AXP20X_CHRG_CTRL1_TGT_CURR ; 
 int EINVAL ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int axp20x_set_constant_charge_current(struct axp20x_batt_ps *axp_batt,
					      int charge_current)
{
	if (charge_current > axp_batt->max_ccc)
		return -EINVAL;

	charge_current = (charge_current - axp_batt->data->ccc_offset) /
		axp_batt->data->ccc_scale;

	if (charge_current > AXP20X_CHRG_CTRL1_TGT_CURR || charge_current < 0)
		return -EINVAL;

	return regmap_update_bits(axp_batt->regmap, AXP20X_CHRG_CTRL1,
				  AXP20X_CHRG_CTRL1_TGT_CURR, charge_current);
}