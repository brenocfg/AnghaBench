#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ suspend_state_t ;
struct regulator_dev {int /*<<< orphan*/  dev; TYPE_3__* supply; TYPE_2__* desc; } ;
struct TYPE_6__ {int /*<<< orphan*/  rdev; } ;
struct TYPE_5__ {scalar_t__ min_dropout_uV; TYPE_1__* ops; } ;
struct TYPE_4__ {scalar_t__ get_voltage_sel; scalar_t__ get_voltage; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 scalar_t__ PM_SUSPEND_ON ; 
 int /*<<< orphan*/  REGULATOR_CHANGE_VOLTAGE ; 
 int _regulator_do_set_suspend_voltage (struct regulator_dev*,int,int,scalar_t__) ; 
 int _regulator_do_set_voltage (struct regulator_dev*,int,int) ; 
 int _regulator_list_voltage (struct regulator_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int regulator_get_voltage_rdev (int /*<<< orphan*/ ) ; 
 int regulator_map_voltage (struct regulator_dev*,int,int) ; 
 scalar_t__ regulator_ops_is_valid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_set_voltage_unlocked (TYPE_3__*,int,int /*<<< orphan*/ ,scalar_t__) ; 

int regulator_set_voltage_rdev(struct regulator_dev *rdev, int min_uV,
			       int max_uV, suspend_state_t state)
{
	int best_supply_uV = 0;
	int supply_change_uV = 0;
	int ret;

	if (rdev->supply &&
	    regulator_ops_is_valid(rdev->supply->rdev,
				   REGULATOR_CHANGE_VOLTAGE) &&
	    (rdev->desc->min_dropout_uV || !(rdev->desc->ops->get_voltage ||
					   rdev->desc->ops->get_voltage_sel))) {
		int current_supply_uV;
		int selector;

		selector = regulator_map_voltage(rdev, min_uV, max_uV);
		if (selector < 0) {
			ret = selector;
			goto out;
		}

		best_supply_uV = _regulator_list_voltage(rdev, selector, 0);
		if (best_supply_uV < 0) {
			ret = best_supply_uV;
			goto out;
		}

		best_supply_uV += rdev->desc->min_dropout_uV;

		current_supply_uV = regulator_get_voltage_rdev(rdev->supply->rdev);
		if (current_supply_uV < 0) {
			ret = current_supply_uV;
			goto out;
		}

		supply_change_uV = best_supply_uV - current_supply_uV;
	}

	if (supply_change_uV > 0) {
		ret = regulator_set_voltage_unlocked(rdev->supply,
				best_supply_uV, INT_MAX, state);
		if (ret) {
			dev_err(&rdev->dev, "Failed to increase supply voltage: %d\n",
					ret);
			goto out;
		}
	}

	if (state == PM_SUSPEND_ON)
		ret = _regulator_do_set_voltage(rdev, min_uV, max_uV);
	else
		ret = _regulator_do_set_suspend_voltage(rdev, min_uV,
							max_uV, state);
	if (ret < 0)
		goto out;

	if (supply_change_uV < 0) {
		ret = regulator_set_voltage_unlocked(rdev->supply,
				best_supply_uV, INT_MAX, state);
		if (ret)
			dev_warn(&rdev->dev, "Failed to decrease supply voltage: %d\n",
					ret);
		/* No need to fail here */
		ret = 0;
	}

out:
	return ret;
}