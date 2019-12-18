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
struct regulator_dev {int /*<<< orphan*/  regmap; } ;
struct mt6380_regulator_info {int /*<<< orphan*/  modeset_mask; int /*<<< orphan*/  modeset_reg; } ;

/* Variables and functions */
 int EINVAL ; 
 int MT6380_REGULATOR_MODE_AUTO ; 
 int MT6380_REGULATOR_MODE_FORCE_PWM ; 
#define  REGULATOR_MODE_FAST 129 
#define  REGULATOR_MODE_NORMAL 128 
 int ffs (int /*<<< orphan*/ ) ; 
 struct mt6380_regulator_info* rdev_get_drvdata (struct regulator_dev*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mt6380_regulator_set_mode(struct regulator_dev *rdev,
				     unsigned int mode)
{
	int ret, val = 0;
	struct mt6380_regulator_info *info = rdev_get_drvdata(rdev);

	switch (mode) {
	case REGULATOR_MODE_NORMAL:
		val = MT6380_REGULATOR_MODE_AUTO;
		break;
	case REGULATOR_MODE_FAST:
		val = MT6380_REGULATOR_MODE_FORCE_PWM;
		break;
	default:
		return -EINVAL;
	}

	val <<= ffs(info->modeset_mask) - 1;

	ret = regmap_update_bits(rdev->regmap, info->modeset_reg,
				 info->modeset_mask, val);

	return ret;
}