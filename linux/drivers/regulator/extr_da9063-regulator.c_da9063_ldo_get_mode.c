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
struct regmap_field {int dummy; } ;
struct da9063_regulator {struct regmap_field* sleep; struct regmap_field* suspend_sleep; struct regmap_field* suspend; } ;

/* Variables and functions */
 int REGULATOR_MODE_NORMAL ; 
 int REGULATOR_MODE_STANDBY ; 
 struct da9063_regulator* rdev_get_drvdata (struct regulator_dev*) ; 
 int regmap_field_read (struct regmap_field*,int*) ; 

__attribute__((used)) static unsigned da9063_ldo_get_mode(struct regulator_dev *rdev)
{
	struct da9063_regulator *regl = rdev_get_drvdata(rdev);
	struct regmap_field *field;
	int ret, val;

	/* Detect current regulator state */
	ret = regmap_field_read(regl->suspend, &val);
	if (ret < 0)
		return 0;

	/* Read regulator mode from proper register, depending on state */
	if (val)
		field = regl->suspend_sleep;
	else
		field = regl->sleep;

	ret = regmap_field_read(field, &val);
	if (ret < 0)
		return 0;

	if (val)
		return REGULATOR_MODE_STANDBY;
	else
		return REGULATOR_MODE_NORMAL;
}