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
struct TYPE_3__ {int n_coupled; struct regulator_dev** coupled_rdevs; } ;
struct regulator_dev {TYPE_2__* supply; TYPE_1__ coupling_desc; } ;
struct TYPE_4__ {struct regulator_dev* rdev; } ;

/* Variables and functions */

__attribute__((used)) static bool regulator_supply_is_couple(struct regulator_dev *rdev)
{
	struct regulator_dev *c_rdev;
	int i;

	for (i = 1; i < rdev->coupling_desc.n_coupled; i++) {
		c_rdev = rdev->coupling_desc.coupled_rdevs[i];

		if (rdev->supply->rdev == c_rdev)
			return true;
	}

	return false;
}