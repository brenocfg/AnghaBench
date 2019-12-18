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
struct da9062_regulator {int /*<<< orphan*/  sleep; } ;

/* Variables and functions */
 int REGULATOR_MODE_NORMAL ; 
 int REGULATOR_MODE_STANDBY ; 
 struct da9062_regulator* rdev_get_drvdata (struct regulator_dev*) ; 
 int regmap_field_read (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static unsigned da9062_ldo_get_mode(struct regulator_dev *rdev)
{
	struct da9062_regulator *regl = rdev_get_drvdata(rdev);
	int ret, val;

	ret = regmap_field_read(regl->sleep, &val);
	if (ret < 0)
		return 0;

	if (val)
		return REGULATOR_MODE_STANDBY;
	else
		return REGULATOR_MODE_NORMAL;
}