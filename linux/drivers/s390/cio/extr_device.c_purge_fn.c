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
struct device {int dummy; } ;
struct ccw_device {int /*<<< orphan*/  ccwlock; TYPE_1__* private; } ;
struct ccw_dev_id {int /*<<< orphan*/  devno; int /*<<< orphan*/  ssid; } ;
struct TYPE_2__ {scalar_t__ state; int /*<<< orphan*/  onoff; struct ccw_dev_id dev_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDEV_TODO_UNREG ; 
 int /*<<< orphan*/  CIO_MSG_EVENT (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ DEV_STATE_OFFLINE ; 
 int EINTR ; 
 scalar_t__ atomic_cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccw_device_sched_todo (struct ccw_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ is_blacklisted (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 struct ccw_device* to_ccwdev (struct device*) ; 

__attribute__((used)) static int purge_fn(struct device *dev, void *data)
{
	struct ccw_device *cdev = to_ccwdev(dev);
	struct ccw_dev_id *id = &cdev->private->dev_id;

	spin_lock_irq(cdev->ccwlock);
	if (is_blacklisted(id->ssid, id->devno) &&
	    (cdev->private->state == DEV_STATE_OFFLINE) &&
	    (atomic_cmpxchg(&cdev->private->onoff, 0, 1) == 0)) {
		CIO_MSG_EVENT(3, "ccw: purging 0.%x.%04x\n", id->ssid,
			      id->devno);
		ccw_device_sched_todo(cdev, CDEV_TODO_UNREG);
		atomic_set(&cdev->private->onoff, 0);
	}
	spin_unlock_irq(cdev->ccwlock);
	/* Abort loop in case of pending signal. */
	if (signal_pending(current))
		return -EINTR;

	return 0;
}