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
struct da903x_regulator_info {int max_uV; } ;
struct TYPE_2__ {int min_uV; int uV_step; } ;

/* Variables and functions */
 int EINVAL ; 
 struct da903x_regulator_info* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int da9030_list_ldo14_voltage(struct regulator_dev *rdev,
				     unsigned selector)
{
	struct da903x_regulator_info *info = rdev_get_drvdata(rdev);
	int volt;

	if (selector & 0x4)
		volt = rdev->desc->min_uV +
		       rdev->desc->uV_step * (3 - (selector & ~0x4));
	else
		volt = (info->max_uV + rdev->desc->min_uV) / 2 +
		       rdev->desc->uV_step * (selector & ~0x4);

	if (volt > info->max_uV)
		return -EINVAL;

	return volt;
}