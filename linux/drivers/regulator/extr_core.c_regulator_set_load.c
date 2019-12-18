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
struct regulator_dev {int dummy; } ;
struct regulator {int uA_load; scalar_t__ enable_count; struct regulator_dev* rdev; } ;

/* Variables and functions */
 int drms_uA_update (struct regulator_dev*) ; 
 int /*<<< orphan*/  regulator_lock (struct regulator_dev*) ; 
 int /*<<< orphan*/  regulator_unlock (struct regulator_dev*) ; 

int regulator_set_load(struct regulator *regulator, int uA_load)
{
	struct regulator_dev *rdev = regulator->rdev;
	int old_uA_load;
	int ret = 0;

	regulator_lock(rdev);
	old_uA_load = regulator->uA_load;
	regulator->uA_load = uA_load;
	if (regulator->enable_count && old_uA_load != uA_load) {
		ret = drms_uA_update(rdev);
		if (ret < 0)
			regulator->uA_load = old_uA_load;
	}
	regulator_unlock(rdev);

	return ret;
}