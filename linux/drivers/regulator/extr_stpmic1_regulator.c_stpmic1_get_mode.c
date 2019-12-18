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
 unsigned int REGULATOR_MODE_NORMAL ; 
 unsigned int REGULATOR_MODE_STANDBY ; 
 int STPMIC1_BUCK_MODE_LP ; 
 struct regmap* rdev_get_regmap (struct regulator_dev*) ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static unsigned int stpmic1_get_mode(struct regulator_dev *rdev)
{
	int value;
	struct regmap *regmap = rdev_get_regmap(rdev);

	regmap_read(regmap, rdev->desc->enable_reg, &value);

	if (value & STPMIC1_BUCK_MODE_LP)
		return REGULATOR_MODE_STANDBY;

	return REGULATOR_MODE_NORMAL;
}