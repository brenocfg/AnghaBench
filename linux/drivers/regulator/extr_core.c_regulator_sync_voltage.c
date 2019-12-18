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
struct regulator_voltage {int min_uV; int max_uV; } ;
struct regulator_dev {TYPE_2__* desc; } ;
struct regulator {struct regulator_voltage* voltage; struct regulator_dev* rdev; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  set_voltage_sel; int /*<<< orphan*/  set_voltage; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t PM_SUSPEND_ON ; 
 int _regulator_do_set_voltage (struct regulator_dev*,int,int) ; 
 int regulator_check_consumers (struct regulator_dev*,int*,int*,int /*<<< orphan*/ ) ; 
 int regulator_check_voltage (struct regulator_dev*,int*,int*) ; 
 int /*<<< orphan*/  regulator_lock (struct regulator_dev*) ; 
 int /*<<< orphan*/  regulator_unlock (struct regulator_dev*) ; 

int regulator_sync_voltage(struct regulator *regulator)
{
	struct regulator_dev *rdev = regulator->rdev;
	struct regulator_voltage *voltage = &regulator->voltage[PM_SUSPEND_ON];
	int ret, min_uV, max_uV;

	regulator_lock(rdev);

	if (!rdev->desc->ops->set_voltage &&
	    !rdev->desc->ops->set_voltage_sel) {
		ret = -EINVAL;
		goto out;
	}

	/* This is only going to work if we've had a voltage configured. */
	if (!voltage->min_uV && !voltage->max_uV) {
		ret = -EINVAL;
		goto out;
	}

	min_uV = voltage->min_uV;
	max_uV = voltage->max_uV;

	/* This should be a paranoia check... */
	ret = regulator_check_voltage(rdev, &min_uV, &max_uV);
	if (ret < 0)
		goto out;

	ret = regulator_check_consumers(rdev, &min_uV, &max_uV, 0);
	if (ret < 0)
		goto out;

	ret = _regulator_do_set_voltage(rdev, min_uV, max_uV);

out:
	regulator_unlock(rdev);
	return ret;
}