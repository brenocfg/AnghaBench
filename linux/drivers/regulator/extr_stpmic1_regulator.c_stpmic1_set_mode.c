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
struct regulator_dev {TYPE_1__* desc; } ;
struct regmap {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  enable_reg; } ;

/* Variables and functions */
 int EINVAL ; 
#define  REGULATOR_MODE_NORMAL 129 
#define  REGULATOR_MODE_STANDBY 128 
 int STPMIC1_BUCK_MODE_LP ; 
 int STPMIC1_BUCK_MODE_NORMAL ; 
 struct regmap* rdev_get_regmap (struct regulator_dev*) ; 
 int regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int stpmic1_set_mode(struct regulator_dev *rdev, unsigned int mode)
{
	int value;
	struct regmap *regmap = rdev_get_regmap(rdev);

	switch (mode) {
	case REGULATOR_MODE_NORMAL:
		value = STPMIC1_BUCK_MODE_NORMAL;
		break;
	case REGULATOR_MODE_STANDBY:
		value = STPMIC1_BUCK_MODE_LP;
		break;
	default:
		return -EINVAL;
	}

	return regmap_update_bits(regmap, rdev->desc->enable_reg,
				  STPMIC1_BUCK_MODE_LP, value);
}