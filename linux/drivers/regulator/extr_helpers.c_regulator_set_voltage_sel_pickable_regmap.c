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
struct TYPE_4__ {int n_linear_ranges; int vsel_mask; unsigned int* linear_range_selectors; scalar_t__ vsel_reg; scalar_t__ vsel_range_reg; int vsel_range_mask; int apply_bit; scalar_t__ apply_reg; TYPE_1__* linear_ranges; } ;
struct TYPE_3__ {int max_sel; int min_sel; } ;

/* Variables and functions */
 int EINVAL ; 
 int ffs (int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int,unsigned int) ; 

int regulator_set_voltage_sel_pickable_regmap(struct regulator_dev *rdev,
					      unsigned int sel)
{
	unsigned int range;
	int ret, i;
	unsigned int voltages_in_range = 0;

	for (i = 0; i < rdev->desc->n_linear_ranges; i++) {
		voltages_in_range = (rdev->desc->linear_ranges[i].max_sel -
				     rdev->desc->linear_ranges[i].min_sel) + 1;
		if (sel < voltages_in_range)
			break;
		sel -= voltages_in_range;
	}

	if (i == rdev->desc->n_linear_ranges)
		return -EINVAL;

	sel <<= ffs(rdev->desc->vsel_mask) - 1;
	sel += rdev->desc->linear_ranges[i].min_sel;

	range = rdev->desc->linear_range_selectors[i];

	if (rdev->desc->vsel_reg == rdev->desc->vsel_range_reg) {
		ret = regmap_update_bits(rdev->regmap,
					 rdev->desc->vsel_reg,
					 rdev->desc->vsel_range_mask |
					 rdev->desc->vsel_mask, sel | range);
	} else {
		ret = regmap_update_bits(rdev->regmap,
					 rdev->desc->vsel_range_reg,
					 rdev->desc->vsel_range_mask, range);
		if (ret)
			return ret;

		ret = regmap_update_bits(rdev->regmap, rdev->desc->vsel_reg,
				  rdev->desc->vsel_mask, sel);
	}

	if (ret)
		return ret;

	if (rdev->desc->apply_bit)
		ret = regmap_update_bits(rdev->regmap, rdev->desc->apply_reg,
					 rdev->desc->apply_bit,
					 rdev->desc->apply_bit);
	return ret;
}