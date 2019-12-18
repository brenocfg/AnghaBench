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
struct TYPE_2__ {unsigned int* linear_range_selectors; unsigned int vsel_range_mask; int n_linear_ranges; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int regulator_range_selector_to_index(struct regulator_dev *rdev,
					     unsigned int rval)
{
	int i;

	if (!rdev->desc->linear_range_selectors)
		return -EINVAL;

	rval &= rdev->desc->vsel_range_mask;

	for (i = 0; i < rdev->desc->n_linear_ranges; i++) {
		if (rdev->desc->linear_range_selectors[i] == rval)
			return i;
	}
	return -EINVAL;
}