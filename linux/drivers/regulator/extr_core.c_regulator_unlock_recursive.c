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
struct TYPE_4__ {unsigned int n_coupled; struct regulator_dev** coupled_rdevs; } ;
struct regulator_dev {TYPE_2__ coupling_desc; TYPE_1__* supply; } ;
struct TYPE_3__ {struct regulator_dev* rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  regulator_supply_is_couple (struct regulator_dev*) ; 
 int /*<<< orphan*/  regulator_unlock (struct regulator_dev*) ; 

__attribute__((used)) static void regulator_unlock_recursive(struct regulator_dev *rdev,
				       unsigned int n_coupled)
{
	struct regulator_dev *c_rdev;
	int i;

	for (i = n_coupled; i > 0; i--) {
		c_rdev = rdev->coupling_desc.coupled_rdevs[i - 1];

		if (!c_rdev)
			continue;

		if (c_rdev->supply && !regulator_supply_is_couple(c_rdev))
			regulator_unlock_recursive(
					c_rdev->supply->rdev,
					c_rdev->coupling_desc.n_coupled);

		regulator_unlock(c_rdev);
	}
}