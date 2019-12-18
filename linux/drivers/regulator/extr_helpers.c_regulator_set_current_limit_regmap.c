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
struct regulator_dev {TYPE_1__* desc; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {unsigned int n_current_limits; unsigned int* curr_table; int /*<<< orphan*/  csel_mask; int /*<<< orphan*/  csel_reg; } ;

/* Variables and functions */
 int EINVAL ; 
 int ffs (int /*<<< orphan*/ ) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int regulator_set_current_limit_regmap(struct regulator_dev *rdev,
				       int min_uA, int max_uA)
{
	unsigned int n_currents = rdev->desc->n_current_limits;
	int i, sel = -1;

	if (n_currents == 0)
		return -EINVAL;

	if (rdev->desc->curr_table) {
		const unsigned int *curr_table = rdev->desc->curr_table;
		bool ascend = curr_table[n_currents - 1] > curr_table[0];

		/* search for closest to maximum */
		if (ascend) {
			for (i = n_currents - 1; i >= 0; i--) {
				if (min_uA <= curr_table[i] &&
				    curr_table[i] <= max_uA) {
					sel = i;
					break;
				}
			}
		} else {
			for (i = 0; i < n_currents; i++) {
				if (min_uA <= curr_table[i] &&
				    curr_table[i] <= max_uA) {
					sel = i;
					break;
				}
			}
		}
	}

	if (sel < 0)
		return -EINVAL;

	sel <<= ffs(rdev->desc->csel_mask) - 1;

	return regmap_update_bits(rdev->regmap, rdev->desc->csel_reg,
				  rdev->desc->csel_mask, sel);
}