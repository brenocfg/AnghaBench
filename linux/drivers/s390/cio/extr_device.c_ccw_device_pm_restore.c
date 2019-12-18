#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct subchannel {int /*<<< orphan*/  lock; int /*<<< orphan*/  schid; } ;
struct device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct ccw_device {TYPE_5__* drv; scalar_t__ online; TYPE_4__* private; TYPE_1__ dev; } ;
struct TYPE_10__ {int (* restore ) (struct ccw_device*) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  devno; int /*<<< orphan*/  ssid; } ;
struct TYPE_7__ {int /*<<< orphan*/  donotify; } ;
struct TYPE_9__ {int state; TYPE_3__ dev_id; scalar_t__ cmb; int /*<<< orphan*/  wait_q; TYPE_2__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDEV_TODO_REBIND ; 
 int /*<<< orphan*/  CDEV_TODO_UNREG ; 
 int /*<<< orphan*/  CIO_MSG_EVENT (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CIO_OPER ; 
#define  DEV_STATE_BOXED 130 
#define  DEV_STATE_OFFLINE 129 
#define  DEV_STATE_ONLINE 128 
 int ENODEV ; 
 scalar_t__ NOTIFY_BAD ; 
 int /*<<< orphan*/  __ccw_device_pm_restore (struct ccw_device*) ; 
 scalar_t__ ccw_device_notify (struct ccw_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ ccw_device_online (struct ccw_device*) ; 
 int /*<<< orphan*/  ccw_device_sched_todo (struct ccw_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccw_device_test_sense_data (struct ccw_device*) ; 
 int /*<<< orphan*/  ccw_device_update_sense_data (struct ccw_device*) ; 
 int ccw_set_cmf (struct ccw_device*,int) ; 
 scalar_t__ cio_is_console (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_fsm_final_state (struct ccw_device*) ; 
 int resume_handle_boxed (struct ccw_device*) ; 
 int resume_handle_disc (struct ccw_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int stub1 (struct ccw_device*) ; 
 struct ccw_device* to_ccwdev (struct device*) ; 
 struct subchannel* to_subchannel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ccw_device_pm_restore(struct device *dev)
{
	struct ccw_device *cdev = to_ccwdev(dev);
	struct subchannel *sch;
	int ret = 0;

	__ccw_device_pm_restore(cdev);
	sch = to_subchannel(cdev->dev.parent);
	spin_lock_irq(sch->lock);
	if (cio_is_console(sch->schid))
		goto out_restore;

	/* check recognition results */
	switch (cdev->private->state) {
	case DEV_STATE_OFFLINE:
	case DEV_STATE_ONLINE:
		cdev->private->flags.donotify = 0;
		break;
	case DEV_STATE_BOXED:
		ret = resume_handle_boxed(cdev);
		if (ret)
			goto out_unlock;
		goto out_restore;
	default:
		ret = resume_handle_disc(cdev);
		if (ret)
			goto out_unlock;
		goto out_restore;
	}
	/* check if the device type has changed */
	if (!ccw_device_test_sense_data(cdev)) {
		ccw_device_update_sense_data(cdev);
		ccw_device_sched_todo(cdev, CDEV_TODO_REBIND);
		ret = -ENODEV;
		goto out_unlock;
	}
	if (!cdev->online)
		goto out_unlock;

	if (ccw_device_online(cdev)) {
		ret = resume_handle_disc(cdev);
		if (ret)
			goto out_unlock;
		goto out_restore;
	}
	spin_unlock_irq(sch->lock);
	wait_event(cdev->private->wait_q, dev_fsm_final_state(cdev));
	spin_lock_irq(sch->lock);

	if (ccw_device_notify(cdev, CIO_OPER) == NOTIFY_BAD) {
		ccw_device_sched_todo(cdev, CDEV_TODO_UNREG);
		ret = -ENODEV;
		goto out_unlock;
	}

	/* reenable cmf, if needed */
	if (cdev->private->cmb) {
		spin_unlock_irq(sch->lock);
		ret = ccw_set_cmf(cdev, 1);
		spin_lock_irq(sch->lock);
		if (ret) {
			CIO_MSG_EVENT(2, "resume: cdev 0.%x.%04x: cmf failed "
				      "(rc=%d)\n", cdev->private->dev_id.ssid,
				      cdev->private->dev_id.devno, ret);
			ret = 0;
		}
	}

out_restore:
	spin_unlock_irq(sch->lock);
	if (cdev->online && cdev->drv && cdev->drv->restore)
		ret = cdev->drv->restore(cdev);
	return ret;

out_unlock:
	spin_unlock_irq(sch->lock);
	return ret;
}