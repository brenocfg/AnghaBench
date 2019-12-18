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
struct regulator_dev {int dummy; } ;
struct da9055_volt_reg {int sl_shift; int /*<<< orphan*/  reg_b; } ;
struct da9055_regulator_info {struct da9055_volt_reg volt; } ;
struct da9055_regulator {int /*<<< orphan*/  da9055; struct da9055_regulator_info* info; } ;

/* Variables and functions */
 int DA9055_LDO_MODE_SLEEP ; 
 int DA9055_LDO_MODE_SYNC ; 
#define  REGULATOR_MODE_FAST 130 
#define  REGULATOR_MODE_NORMAL 129 
#define  REGULATOR_MODE_STANDBY 128 
 int da9055_reg_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct da9055_regulator* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int da9055_ldo_set_mode(struct regulator_dev *rdev, unsigned int mode)
{
	struct da9055_regulator *regulator = rdev_get_drvdata(rdev);
	struct da9055_regulator_info *info = regulator->info;
	struct da9055_volt_reg volt = info->volt;
	int val = 0;

	switch (mode) {
	case REGULATOR_MODE_NORMAL:
	case REGULATOR_MODE_FAST:
		val = DA9055_LDO_MODE_SYNC;
		break;
	case REGULATOR_MODE_STANDBY:
		val = DA9055_LDO_MODE_SLEEP;
		break;
	}

	return da9055_reg_update(regulator->da9055, volt.reg_b,
				 1 << volt.sl_shift,
				 val << volt.sl_shift);
}