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
struct TYPE_2__ {int /*<<< orphan*/  base; } ;
struct regulator_dev {TYPE_1__ mutex; } ;

/* Variables and functions */
 int EINVAL ; 
 int NOTIFY_STOP_MASK ; 
 int REGULATOR_EVENT_ABORT_DISABLE ; 
 int REGULATOR_EVENT_DISABLE ; 
 int REGULATOR_EVENT_FORCE_DISABLE ; 
 int REGULATOR_EVENT_PRE_DISABLE ; 
 int _notifier_call_chain (struct regulator_dev*,int,int /*<<< orphan*/ *) ; 
 int _regulator_do_disable (struct regulator_dev*) ; 
 int /*<<< orphan*/  lockdep_assert_held_once (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdev_err (struct regulator_dev*,char*) ; 

__attribute__((used)) static int _regulator_force_disable(struct regulator_dev *rdev)
{
	int ret = 0;

	lockdep_assert_held_once(&rdev->mutex.base);

	ret = _notifier_call_chain(rdev, REGULATOR_EVENT_FORCE_DISABLE |
			REGULATOR_EVENT_PRE_DISABLE, NULL);
	if (ret & NOTIFY_STOP_MASK)
		return -EINVAL;

	ret = _regulator_do_disable(rdev);
	if (ret < 0) {
		rdev_err(rdev, "failed to force disable\n");
		_notifier_call_chain(rdev, REGULATOR_EVENT_FORCE_DISABLE |
				REGULATOR_EVENT_ABORT_DISABLE, NULL);
		return ret;
	}

	_notifier_call_chain(rdev, REGULATOR_EVENT_FORCE_DISABLE |
			REGULATOR_EVENT_DISABLE, NULL);

	return 0;
}