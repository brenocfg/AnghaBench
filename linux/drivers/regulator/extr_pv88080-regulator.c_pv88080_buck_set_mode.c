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
struct pv88080_regulator {int /*<<< orphan*/  mode_reg; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PV88080_BUCK1_MODE_MASK ; 
 int PV88080_BUCK_MODE_AUTO ; 
 int PV88080_BUCK_MODE_SLEEP ; 
 int PV88080_BUCK_MODE_SYNC ; 
#define  REGULATOR_MODE_FAST 130 
#define  REGULATOR_MODE_NORMAL 129 
#define  REGULATOR_MODE_STANDBY 128 
 struct pv88080_regulator* rdev_get_drvdata (struct regulator_dev*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pv88080_buck_set_mode(struct regulator_dev *rdev,
					unsigned int mode)
{
	struct pv88080_regulator *info = rdev_get_drvdata(rdev);
	int val = 0;

	switch (mode) {
	case REGULATOR_MODE_FAST:
		val = PV88080_BUCK_MODE_SYNC;
		break;
	case REGULATOR_MODE_NORMAL:
		val = PV88080_BUCK_MODE_AUTO;
		break;
	case REGULATOR_MODE_STANDBY:
		val = PV88080_BUCK_MODE_SLEEP;
		break;
	default:
		return -EINVAL;
	}

	return regmap_update_bits(rdev->regmap, info->mode_reg,
					PV88080_BUCK1_MODE_MASK, val);
}