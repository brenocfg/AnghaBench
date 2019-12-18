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
struct urdev {int /*<<< orphan*/  io_mutex; int /*<<< orphan*/ * io_done; struct ccw_device* cdev; } ;
struct ccw_device {int dummy; } ;
struct ccw1 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int ccw_device_start (struct ccw_device*,struct ccw1*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event ; 
 int /*<<< orphan*/  get_ccwdev_lock (struct ccw_device*) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_ur_io(struct urdev *urd, struct ccw1 *cpa)
{
	int rc;
	struct ccw_device *cdev = urd->cdev;
	DECLARE_COMPLETION_ONSTACK(event);

	TRACE("do_ur_io: cpa=%p\n", cpa);

	rc = mutex_lock_interruptible(&urd->io_mutex);
	if (rc)
		return rc;

	urd->io_done = &event;

	spin_lock_irq(get_ccwdev_lock(cdev));
	rc = ccw_device_start(cdev, cpa, 1, 0, 0);
	spin_unlock_irq(get_ccwdev_lock(cdev));

	TRACE("do_ur_io: ccw_device_start returned %d\n", rc);
	if (rc)
		goto out;

	wait_for_completion(&event);
	TRACE("do_ur_io: I/O complete\n");
	rc = 0;

out:
	mutex_unlock(&urd->io_mutex);
	return rc;
}