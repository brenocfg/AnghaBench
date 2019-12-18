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
typedef  int u8 ;
struct regulator_dev {int dummy; } ;
struct ab8500_regulator_info {int mode_mask; int mode_val_normal; int mode_val_idle; int update_val; int update_val_normal; int update_val_idle; int /*<<< orphan*/  mode_reg; int /*<<< orphan*/  mode_bank; int /*<<< orphan*/  dev; TYPE_1__* shared_mode; } ;
struct TYPE_2__ {scalar_t__ lp_mode_req; } ;

/* Variables and functions */
 unsigned int EINVAL ; 
 unsigned int REGULATOR_MODE_IDLE ; 
 unsigned int REGULATOR_MODE_NORMAL ; 
 int abx500_get_register_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rdev_get_dev (struct regulator_dev*) ; 
 struct ab8500_regulator_info* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static unsigned int ab8500_regulator_get_mode(struct regulator_dev *rdev)
{
	struct ab8500_regulator_info *info = rdev_get_drvdata(rdev);
	int ret;
	u8 val;
	u8 val_normal;
	u8 val_idle;

	if (info == NULL) {
		dev_err(rdev_get_dev(rdev), "regulator info null pointer\n");
		return -EINVAL;
	}

	/* Need special handling for shared mode */
	if (info->shared_mode) {
		if (info->shared_mode->lp_mode_req)
			return REGULATOR_MODE_IDLE;
		else
			return REGULATOR_MODE_NORMAL;
	}

	if (info->mode_mask) {
		/* Dedicated register for handling mode */
		ret = abx500_get_register_interruptible(info->dev,
		info->mode_bank, info->mode_reg, &val);
		val = val & info->mode_mask;

		val_normal = info->mode_val_normal;
		val_idle = info->mode_val_idle;
	} else {
		/* Mode register same as enable register */
		val = info->update_val;
		val_normal = info->update_val_normal;
		val_idle = info->update_val_idle;
	}

	if (val == val_normal)
		ret = REGULATOR_MODE_NORMAL;
	else if (val == val_idle)
		ret = REGULATOR_MODE_IDLE;
	else
		ret = -EINVAL;

	return ret;
}