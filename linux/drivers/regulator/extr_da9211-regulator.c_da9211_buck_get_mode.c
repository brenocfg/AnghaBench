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
struct da9211 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
#define  DA9211_BUCK_MODE_AUTO 130 
#define  DA9211_BUCK_MODE_SLEEP 129 
#define  DA9211_BUCK_MODE_SYNC 128 
 scalar_t__ DA9211_REG_BUCKA_CONF ; 
 int REGULATOR_MODE_FAST ; 
 int REGULATOR_MODE_NORMAL ; 
 int REGULATOR_MODE_STANDBY ; 
 struct da9211* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,scalar_t__,unsigned int*) ; 

__attribute__((used)) static unsigned int da9211_buck_get_mode(struct regulator_dev *rdev)
{
	int id = rdev_get_id(rdev);
	struct da9211 *chip = rdev_get_drvdata(rdev);
	unsigned int data;
	int ret, mode = 0;

	ret = regmap_read(chip->regmap, DA9211_REG_BUCKA_CONF+id, &data);
	if (ret < 0)
		return ret;

	switch (data & 0x03) {
	case DA9211_BUCK_MODE_SYNC:
		mode = REGULATOR_MODE_FAST;
		break;
	case DA9211_BUCK_MODE_AUTO:
		mode = REGULATOR_MODE_NORMAL;
		break;
	case DA9211_BUCK_MODE_SLEEP:
		mode = REGULATOR_MODE_STANDBY;
		break;
	}

	return mode;
}