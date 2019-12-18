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
struct regulator_dev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  v_mask; int /*<<< orphan*/  reg_b; } ;
struct TYPE_4__ {int /*<<< orphan*/  sel_mask; int /*<<< orphan*/  reg; } ;
struct da9055_regulator_info {TYPE_1__ volt; TYPE_2__ conf; } ;
struct da9055_regulator {scalar_t__ reg_rselect; int /*<<< orphan*/  da9055; struct da9055_regulator_info* info; } ;

/* Variables and functions */
 int DA9055_SEL_REG_B ; 
 scalar_t__ NO_GPIO ; 
 int da9055_reg_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct da9055_regulator* rdev_get_drvdata (struct regulator_dev*) ; 
 int regulator_map_voltage_linear (struct regulator_dev*,int,int) ; 

__attribute__((used)) static int da9055_regulator_set_suspend_voltage(struct regulator_dev *rdev,
						int uV)
{
	struct da9055_regulator *regulator = rdev_get_drvdata(rdev);
	struct da9055_regulator_info *info = regulator->info;
	int ret;

	/* Select register set B for suspend voltage ramping. */
	if (regulator->reg_rselect == NO_GPIO) {
		ret = da9055_reg_update(regulator->da9055, info->conf.reg,
					info->conf.sel_mask, DA9055_SEL_REG_B);
		if (ret < 0)
			return ret;
	}

	ret = regulator_map_voltage_linear(rdev, uV, uV);
	if (ret < 0)
		return ret;

	return da9055_reg_update(regulator->da9055, info->volt.reg_b,
				 info->volt.v_mask, ret);
}