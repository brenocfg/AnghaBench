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
struct regulator_linear_range {int min_uV; int max_sel; int min_sel; int uV_step; } ;
struct regulator_dev {TYPE_2__* desc; } ;
struct TYPE_4__ {int n_linear_ranges; TYPE_1__* ops; struct regulator_linear_range* linear_ranges; } ;
struct TYPE_3__ {int (* list_voltage ) (struct regulator_dev*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DIV_ROUND_UP (int,int) ; 
 int EINVAL ; 
 int stub1 (struct regulator_dev*,int) ; 

int regulator_map_voltage_pickable_linear_range(struct regulator_dev *rdev,
						int min_uV, int max_uV)
{
	const struct regulator_linear_range *range;
	int ret = -EINVAL;
	int voltage, i;
	unsigned int selector = 0;

	if (!rdev->desc->n_linear_ranges) {
		BUG_ON(!rdev->desc->n_linear_ranges);
		return -EINVAL;
	}

	for (i = 0; i < rdev->desc->n_linear_ranges; i++) {
		int linear_max_uV;

		range = &rdev->desc->linear_ranges[i];
		linear_max_uV = range->min_uV +
			(range->max_sel - range->min_sel) * range->uV_step;

		if (!(min_uV <= linear_max_uV && max_uV >= range->min_uV)) {
			selector += (range->max_sel - range->min_sel + 1);
			continue;
		}

		if (min_uV <= range->min_uV)
			min_uV = range->min_uV;

		/* range->uV_step == 0 means fixed voltage range */
		if (range->uV_step == 0) {
			ret = 0;
		} else {
			ret = DIV_ROUND_UP(min_uV - range->min_uV,
					   range->uV_step);
			if (ret < 0)
				return ret;
		}

		ret += selector;

		voltage = rdev->desc->ops->list_voltage(rdev, ret);

		/*
		 * Map back into a voltage to verify we're still in bounds.
		 * We may have overlapping voltage ranges. Hence we don't
		 * exit but retry until we have checked all ranges.
		 */
		if (voltage < min_uV || voltage > max_uV)
			selector += (range->max_sel - range->min_sel + 1);
		else
			break;
	}

	if (i == rdev->desc->n_linear_ranges)
		return -EINVAL;

	return ret;
}