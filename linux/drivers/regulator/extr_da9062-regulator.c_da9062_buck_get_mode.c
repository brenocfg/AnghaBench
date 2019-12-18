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
struct da9062_regulator {int /*<<< orphan*/  sleep; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
#define  BUCK_MODE_AUTO 131 
#define  BUCK_MODE_MANUAL 130 
#define  BUCK_MODE_SLEEP 129 
#define  BUCK_MODE_SYNC 128 
 int REGULATOR_MODE_FAST ; 
 int REGULATOR_MODE_NORMAL ; 
 int REGULATOR_MODE_STANDBY ; 
 struct da9062_regulator* rdev_get_drvdata (struct regulator_dev*) ; 
 int regmap_field_read (int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static unsigned da9062_buck_get_mode(struct regulator_dev *rdev)
{
	struct da9062_regulator *regl = rdev_get_drvdata(rdev);
	unsigned int val, mode = 0;
	int ret;

	ret = regmap_field_read(regl->mode, &val);
	if (ret < 0)
		return ret;

	switch (val) {
	default:
	case BUCK_MODE_MANUAL:
		mode = REGULATOR_MODE_FAST | REGULATOR_MODE_STANDBY;
		/* Sleep flag bit decides the mode */
		break;
	case BUCK_MODE_SLEEP:
		return REGULATOR_MODE_STANDBY;
	case BUCK_MODE_SYNC:
		return REGULATOR_MODE_FAST;
	case BUCK_MODE_AUTO:
		return REGULATOR_MODE_NORMAL;
	}

	ret = regmap_field_read(regl->sleep, &val);
	if (ret < 0)
		return 0;

	if (val)
		mode &= REGULATOR_MODE_STANDBY;
	else
		mode &= REGULATOR_MODE_NORMAL | REGULATOR_MODE_FAST;

	return mode;
}