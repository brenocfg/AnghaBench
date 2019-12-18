#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct regulator_ops {int (* set_input_current_limit ) (struct regulator_dev*,scalar_t__) ;int (* set_mode ) (struct regulator_dev*,scalar_t__) ;int (* set_ramp_delay ) (struct regulator_dev*,scalar_t__) ;int (* set_pull_down ) (struct regulator_dev*) ;int (* set_soft_start ) (struct regulator_dev*) ;int (* set_over_current_protection ) (struct regulator_dev*) ;int (* set_active_discharge ) (struct regulator_dev*,int) ;} ;
struct regulator_dev {int /*<<< orphan*/  use_count; int /*<<< orphan*/ * supply; TYPE_2__* constraints; TYPE_1__* desc; } ;
struct regulation_constraints {int dummy; } ;
struct TYPE_7__ {scalar_t__ active_discharge; scalar_t__ boot_on; scalar_t__ always_on; scalar_t__ over_current_protection; scalar_t__ soft_start; scalar_t__ pull_down; scalar_t__ ramp_delay; scalar_t__ ramp_disable; scalar_t__ system_load; scalar_t__ initial_mode; scalar_t__ initial_state; scalar_t__ ilim_uA; } ;
struct TYPE_6__ {struct regulator_ops* ops; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ REGULATOR_ACTIVE_DISCHARGE_ENABLE ; 
 int _regulator_do_enable (struct regulator_dev*) ; 
 int /*<<< orphan*/  _regulator_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drms_uA_update (struct regulator_dev*) ; 
 TYPE_2__* kmemdup (struct regulation_constraints const*,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int machine_constraints_current (struct regulator_dev*,TYPE_2__*) ; 
 int machine_constraints_voltage (struct regulator_dev*,TYPE_2__*) ; 
 int /*<<< orphan*/  print_constraints (struct regulator_dev*) ; 
 int /*<<< orphan*/  rdev_err (struct regulator_dev*,char*,...) ; 
 int regulator_enable (int /*<<< orphan*/ *) ; 
 int stub1 (struct regulator_dev*,scalar_t__) ; 
 int stub2 (struct regulator_dev*,scalar_t__) ; 
 int stub3 (struct regulator_dev*,scalar_t__) ; 
 int stub4 (struct regulator_dev*) ; 
 int stub5 (struct regulator_dev*) ; 
 int stub6 (struct regulator_dev*) ; 
 int stub7 (struct regulator_dev*,int) ; 
 int suspend_set_state (struct regulator_dev*,scalar_t__) ; 

__attribute__((used)) static int set_machine_constraints(struct regulator_dev *rdev,
	const struct regulation_constraints *constraints)
{
	int ret = 0;
	const struct regulator_ops *ops = rdev->desc->ops;

	if (constraints)
		rdev->constraints = kmemdup(constraints, sizeof(*constraints),
					    GFP_KERNEL);
	else
		rdev->constraints = kzalloc(sizeof(*constraints),
					    GFP_KERNEL);
	if (!rdev->constraints)
		return -ENOMEM;

	ret = machine_constraints_voltage(rdev, rdev->constraints);
	if (ret != 0)
		return ret;

	ret = machine_constraints_current(rdev, rdev->constraints);
	if (ret != 0)
		return ret;

	if (rdev->constraints->ilim_uA && ops->set_input_current_limit) {
		ret = ops->set_input_current_limit(rdev,
						   rdev->constraints->ilim_uA);
		if (ret < 0) {
			rdev_err(rdev, "failed to set input limit\n");
			return ret;
		}
	}

	/* do we need to setup our suspend state */
	if (rdev->constraints->initial_state) {
		ret = suspend_set_state(rdev, rdev->constraints->initial_state);
		if (ret < 0) {
			rdev_err(rdev, "failed to set suspend state\n");
			return ret;
		}
	}

	if (rdev->constraints->initial_mode) {
		if (!ops->set_mode) {
			rdev_err(rdev, "no set_mode operation\n");
			return -EINVAL;
		}

		ret = ops->set_mode(rdev, rdev->constraints->initial_mode);
		if (ret < 0) {
			rdev_err(rdev, "failed to set initial mode: %d\n", ret);
			return ret;
		}
	} else if (rdev->constraints->system_load) {
		/*
		 * We'll only apply the initial system load if an
		 * initial mode wasn't specified.
		 */
		drms_uA_update(rdev);
	}

	if ((rdev->constraints->ramp_delay || rdev->constraints->ramp_disable)
		&& ops->set_ramp_delay) {
		ret = ops->set_ramp_delay(rdev, rdev->constraints->ramp_delay);
		if (ret < 0) {
			rdev_err(rdev, "failed to set ramp_delay\n");
			return ret;
		}
	}

	if (rdev->constraints->pull_down && ops->set_pull_down) {
		ret = ops->set_pull_down(rdev);
		if (ret < 0) {
			rdev_err(rdev, "failed to set pull down\n");
			return ret;
		}
	}

	if (rdev->constraints->soft_start && ops->set_soft_start) {
		ret = ops->set_soft_start(rdev);
		if (ret < 0) {
			rdev_err(rdev, "failed to set soft start\n");
			return ret;
		}
	}

	if (rdev->constraints->over_current_protection
		&& ops->set_over_current_protection) {
		ret = ops->set_over_current_protection(rdev);
		if (ret < 0) {
			rdev_err(rdev, "failed to set over current protection\n");
			return ret;
		}
	}

	if (rdev->constraints->active_discharge && ops->set_active_discharge) {
		bool ad_state = (rdev->constraints->active_discharge ==
			      REGULATOR_ACTIVE_DISCHARGE_ENABLE) ? true : false;

		ret = ops->set_active_discharge(rdev, ad_state);
		if (ret < 0) {
			rdev_err(rdev, "failed to set active discharge\n");
			return ret;
		}
	}

	/* If the constraints say the regulator should be on at this point
	 * and we have control then make sure it is enabled.
	 */
	if (rdev->constraints->always_on || rdev->constraints->boot_on) {
		if (rdev->supply) {
			ret = regulator_enable(rdev->supply);
			if (ret < 0) {
				_regulator_put(rdev->supply);
				rdev->supply = NULL;
				return ret;
			}
		}

		ret = _regulator_do_enable(rdev);
		if (ret < 0 && ret != -EINVAL) {
			rdev_err(rdev, "failed to enable\n");
			return ret;
		}
		rdev->use_count++;
	}

	print_constraints(rdev);
	return 0;
}