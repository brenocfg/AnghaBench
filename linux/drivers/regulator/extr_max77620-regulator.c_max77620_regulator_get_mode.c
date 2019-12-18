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
struct max77620_regulator_info {scalar_t__ type; int /*<<< orphan*/  cfg_addr; } ;
struct max77620_regulator {int /*<<< orphan*/  dev; int /*<<< orphan*/  rmap; struct max77620_regulator_info** rinfo; } ;

/* Variables and functions */
#define  MAX77620_POWER_MODE_DISABLE 131 
#define  MAX77620_POWER_MODE_GLPM 130 
#define  MAX77620_POWER_MODE_LPM 129 
#define  MAX77620_POWER_MODE_NORMAL 128 
 scalar_t__ MAX77620_REGULATOR_TYPE_SD ; 
 unsigned int MAX77620_SD_FPWM_MASK ; 
 int REGULATOR_MODE_FAST ; 
 int REGULATOR_MODE_IDLE ; 
 int REGULATOR_MODE_NORMAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int max77620_regulator_get_power_mode (struct max77620_regulator*,int) ; 
 struct max77620_regulator* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static unsigned int max77620_regulator_get_mode(struct regulator_dev *rdev)
{
	struct max77620_regulator *pmic = rdev_get_drvdata(rdev);
	int id = rdev_get_id(rdev);
	struct max77620_regulator_info *rinfo = pmic->rinfo[id];
	int fpwm = 0;
	int ret;
	int pm_mode, reg_mode;
	unsigned int val;

	ret = max77620_regulator_get_power_mode(pmic, id);
	if (ret < 0)
		return 0;

	pm_mode = ret;

	if (rinfo->type == MAX77620_REGULATOR_TYPE_SD) {
		ret = regmap_read(pmic->rmap, rinfo->cfg_addr, &val);
		if (ret < 0) {
			dev_err(pmic->dev, "Reg 0x%02x read failed: %d\n",
				rinfo->cfg_addr, ret);
			return ret;
		}
		fpwm = !!(val & MAX77620_SD_FPWM_MASK);
	}

	switch (pm_mode) {
	case MAX77620_POWER_MODE_NORMAL:
	case MAX77620_POWER_MODE_DISABLE:
		if (fpwm)
			reg_mode = REGULATOR_MODE_FAST;
		else
			reg_mode = REGULATOR_MODE_NORMAL;
		break;
	case MAX77620_POWER_MODE_LPM:
	case MAX77620_POWER_MODE_GLPM:
		reg_mode = REGULATOR_MODE_IDLE;
		break;
	default:
		return 0;
	}

	return reg_mode;
}