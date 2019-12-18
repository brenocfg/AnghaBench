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
struct regulator_linear_range {unsigned int max_sel; unsigned int min_sel; int min_uV; unsigned int uV_step; } ;
struct regulator_dev {TYPE_1__* desc; } ;
struct TYPE_2__ {int n_linear_ranges; struct regulator_linear_range* linear_ranges; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 

int regulator_list_voltage_pickable_linear_range(struct regulator_dev *rdev,
						 unsigned int selector)
{
	const struct regulator_linear_range *range;
	int i;
	unsigned int all_sels = 0;

	if (!rdev->desc->n_linear_ranges) {
		BUG_ON(!rdev->desc->n_linear_ranges);
		return -EINVAL;
	}

	for (i = 0; i < rdev->desc->n_linear_ranges; i++) {
		unsigned int sels_in_range;

		range = &rdev->desc->linear_ranges[i];

		sels_in_range = range->max_sel - range->min_sel;

		if (all_sels + sels_in_range >= selector) {
			selector -= all_sels;
			return range->min_uV + (range->uV_step * selector);
		}

		all_sels += (sels_in_range + 1);
	}

	return -EINVAL;
}