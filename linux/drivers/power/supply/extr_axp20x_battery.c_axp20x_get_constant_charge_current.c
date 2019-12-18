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
struct axp20x_batt_ps {TYPE_1__* data; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int ccc_scale; int ccc_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXP20X_CHRG_CTRL1 ; 
 int AXP20X_CHRG_CTRL1_TGT_CURR ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int axp20x_get_constant_charge_current(struct axp20x_batt_ps *axp,
					      int *val)
{
	int ret;

	ret = regmap_read(axp->regmap, AXP20X_CHRG_CTRL1, val);
	if (ret)
		return ret;

	*val &= AXP20X_CHRG_CTRL1_TGT_CURR;

	*val = *val * axp->data->ccc_scale + axp->data->ccc_offset;

	return 0;
}