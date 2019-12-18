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
struct TYPE_6__ {int n_coupled; } ;
struct TYPE_4__ {int /*<<< orphan*/  base; } ;
struct regulator_dev {int use_count; struct regulator* supply; TYPE_3__ coupling_desc; TYPE_2__* constraints; TYPE_1__ mutex; } ;
struct regulator {struct regulator_dev* rdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  always_on; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int NOTIFY_STOP_MASK ; 
 int /*<<< orphan*/  PM_SUSPEND_ON ; 
 int /*<<< orphan*/  REGULATOR_CHANGE_STATUS ; 
 int /*<<< orphan*/  REGULATOR_EVENT_ABORT_DISABLE ; 
 int /*<<< orphan*/  REGULATOR_EVENT_DISABLE ; 
 int /*<<< orphan*/  REGULATOR_EVENT_PRE_DISABLE ; 
 scalar_t__ WARN (int,char*,int /*<<< orphan*/ ) ; 
 int _notifier_call_chain (struct regulator_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int _regulator_do_disable (struct regulator_dev*) ; 
 int _regulator_handle_consumer_disable (struct regulator*) ; 
 int /*<<< orphan*/  lockdep_assert_held_once (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdev_err (struct regulator_dev*,char*) ; 
 int /*<<< orphan*/  rdev_get_name (struct regulator_dev*) ; 
 int regulator_balance_voltage (struct regulator_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ regulator_ops_is_valid (struct regulator_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _regulator_disable(struct regulator *regulator)
{
	struct regulator_dev *rdev = regulator->rdev;
	int ret = 0;

	lockdep_assert_held_once(&rdev->mutex.base);

	if (WARN(rdev->use_count <= 0,
		 "unbalanced disables for %s\n", rdev_get_name(rdev)))
		return -EIO;

	/* are we the last user and permitted to disable ? */
	if (rdev->use_count == 1 &&
	    (rdev->constraints && !rdev->constraints->always_on)) {

		/* we are last user */
		if (regulator_ops_is_valid(rdev, REGULATOR_CHANGE_STATUS)) {
			ret = _notifier_call_chain(rdev,
						   REGULATOR_EVENT_PRE_DISABLE,
						   NULL);
			if (ret & NOTIFY_STOP_MASK)
				return -EINVAL;

			ret = _regulator_do_disable(rdev);
			if (ret < 0) {
				rdev_err(rdev, "failed to disable\n");
				_notifier_call_chain(rdev,
						REGULATOR_EVENT_ABORT_DISABLE,
						NULL);
				return ret;
			}
			_notifier_call_chain(rdev, REGULATOR_EVENT_DISABLE,
					NULL);
		}

		rdev->use_count = 0;
	} else if (rdev->use_count > 1) {
		rdev->use_count--;
	}

	if (ret == 0)
		ret = _regulator_handle_consumer_disable(regulator);

	if (ret == 0 && rdev->coupling_desc.n_coupled > 1)
		ret = regulator_balance_voltage(rdev, PM_SUSPEND_ON);

	if (ret == 0 && rdev->use_count == 0 && rdev->supply)
		ret = _regulator_disable(rdev->supply);

	return ret;
}