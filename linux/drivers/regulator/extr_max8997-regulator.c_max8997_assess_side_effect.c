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
typedef  scalar_t__ u8 ;
struct regulator_dev {int dummy; } ;
struct max8997_data {int buck1_gpiodvs; int buck2_gpiodvs; int buck5_gpiodvs; size_t buck125_gpioindex; scalar_t__* buck5_vol; scalar_t__* buck2_vol; scalar_t__* buck1_vol; } ;

/* Variables and functions */
 int EINVAL ; 
 int INT_MAX ; 
#define  MAX8997_BUCK1 130 
#define  MAX8997_BUCK2 129 
#define  MAX8997_BUCK5 128 
 struct max8997_data* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 

__attribute__((used)) static int max8997_assess_side_effect(struct regulator_dev *rdev,
		u8 new_val, int *best)
{
	struct max8997_data *max8997 = rdev_get_drvdata(rdev);
	int rid = rdev_get_id(rdev);
	u8 *buckx_val[3];
	bool buckx_gpiodvs[3];
	int side_effect[8];
	int min_side_effect = INT_MAX;
	int i;

	*best = -1;

	switch (rid) {
	case MAX8997_BUCK1:
		rid = 0;
		break;
	case MAX8997_BUCK2:
		rid = 1;
		break;
	case MAX8997_BUCK5:
		rid = 2;
		break;
	default:
		return -EINVAL;
	}

	buckx_val[0] = max8997->buck1_vol;
	buckx_val[1] = max8997->buck2_vol;
	buckx_val[2] = max8997->buck5_vol;
	buckx_gpiodvs[0] = max8997->buck1_gpiodvs;
	buckx_gpiodvs[1] = max8997->buck2_gpiodvs;
	buckx_gpiodvs[2] = max8997->buck5_gpiodvs;

	for (i = 0; i < 8; i++) {
		int others;

		if (new_val != (buckx_val[rid])[i]) {
			side_effect[i] = -1;
			continue;
		}

		side_effect[i] = 0;
		for (others = 0; others < 3; others++) {
			int diff;

			if (others == rid)
				continue;
			if (buckx_gpiodvs[others] == false)
				continue; /* Not affected */
			diff = (buckx_val[others])[i] -
				(buckx_val[others])[max8997->buck125_gpioindex];
			if (diff > 0)
				side_effect[i] += diff;
			else if (diff < 0)
				side_effect[i] -= diff;
		}
		if (side_effect[i] == 0) {
			*best = i;
			return 0; /* NO SIDE EFFECT! Use This! */
		}
		if (side_effect[i] < min_side_effect) {
			min_side_effect = side_effect[i];
			*best = i;
		}
	}

	if (*best == -1)
		return -EINVAL;

	return side_effect[*best];
}