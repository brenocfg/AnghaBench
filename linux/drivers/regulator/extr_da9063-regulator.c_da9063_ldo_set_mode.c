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
struct da9063_regulator {int /*<<< orphan*/  sleep; } ;

/* Variables and functions */
 int EINVAL ; 
#define  REGULATOR_MODE_NORMAL 129 
#define  REGULATOR_MODE_STANDBY 128 
 struct da9063_regulator* rdev_get_drvdata (struct regulator_dev*) ; 
 int regmap_field_write (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int da9063_ldo_set_mode(struct regulator_dev *rdev, unsigned mode)
{
	struct da9063_regulator *regl = rdev_get_drvdata(rdev);
	unsigned val;

	switch (mode) {
	case REGULATOR_MODE_NORMAL:
		val = 0;
		break;
	case REGULATOR_MODE_STANDBY:
		val = 1;
		break;
	default:
		return -EINVAL;
	}

	return regmap_field_write(regl->sleep, val);
}