#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct regulator_dev {TYPE_2__* desc; int /*<<< orphan*/  regmap; } ;
struct TYPE_4__ {unsigned int vsel_mask; TYPE_1__* linear_ranges; int /*<<< orphan*/  vsel_range_reg; int /*<<< orphan*/  vsel_reg; } ;
struct TYPE_3__ {scalar_t__ min_sel; scalar_t__ max_sel; } ;

/* Variables and functions */
 int EINVAL ; 
 int ffs (unsigned int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regulator_range_selector_to_index (struct regulator_dev*,unsigned int) ; 

int regulator_get_voltage_sel_pickable_regmap(struct regulator_dev *rdev)
{
	unsigned int r_val;
	int range;
	unsigned int val;
	int ret, i;
	unsigned int voltages_in_range = 0;

	if (!rdev->desc->linear_ranges)
		return -EINVAL;

	ret = regmap_read(rdev->regmap, rdev->desc->vsel_reg, &val);
	if (ret != 0)
		return ret;

	ret = regmap_read(rdev->regmap, rdev->desc->vsel_range_reg, &r_val);
	if (ret != 0)
		return ret;

	val &= rdev->desc->vsel_mask;
	val >>= ffs(rdev->desc->vsel_mask) - 1;

	range = regulator_range_selector_to_index(rdev, r_val);
	if (range < 0)
		return -EINVAL;

	for (i = 0; i < range; i++)
		voltages_in_range += (rdev->desc->linear_ranges[i].max_sel -
				     rdev->desc->linear_ranges[i].min_sel) + 1;

	return val + voltages_in_range;
}