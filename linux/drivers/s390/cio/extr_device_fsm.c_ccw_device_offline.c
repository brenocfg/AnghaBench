#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  scsw; } ;
struct subchannel {TYPE_2__ schib; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct ccw_device {TYPE_4__* private; TYPE_1__ dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  pgroup; scalar_t__ donotify; } ;
struct TYPE_8__ {scalar_t__ state; TYPE_3__ flags; } ;

/* Variables and functions */
 scalar_t__ DEV_STATE_BOXED ; 
 scalar_t__ DEV_STATE_DISBAND_PGID ; 
 scalar_t__ DEV_STATE_DISCONNECTED ; 
 scalar_t__ DEV_STATE_NOT_OPER ; 
 scalar_t__ DEV_STATE_OFFLINE ; 
 scalar_t__ DEV_STATE_ONLINE ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  ccw_device_disband_start (struct ccw_device*) ; 
 int /*<<< orphan*/  ccw_device_done (struct ccw_device*,scalar_t__) ; 
 scalar_t__ ccw_device_is_orphan (struct ccw_device*) ; 
 scalar_t__ cio_update_schib (struct subchannel*) ; 
 scalar_t__ scsw_actl (int /*<<< orphan*/ *) ; 
 struct subchannel* to_subchannel (int /*<<< orphan*/ ) ; 

int
ccw_device_offline(struct ccw_device *cdev)
{
	struct subchannel *sch;

	/* Allow ccw_device_offline while disconnected. */
	if (cdev->private->state == DEV_STATE_DISCONNECTED ||
	    cdev->private->state == DEV_STATE_NOT_OPER) {
		cdev->private->flags.donotify = 0;
		ccw_device_done(cdev, DEV_STATE_NOT_OPER);
		return 0;
	}
	if (cdev->private->state == DEV_STATE_BOXED) {
		ccw_device_done(cdev, DEV_STATE_BOXED);
		return 0;
	}
	if (ccw_device_is_orphan(cdev)) {
		ccw_device_done(cdev, DEV_STATE_OFFLINE);
		return 0;
	}
	sch = to_subchannel(cdev->dev.parent);
	if (cio_update_schib(sch))
		return -ENODEV;
	if (scsw_actl(&sch->schib.scsw) != 0)
		return -EBUSY;
	if (cdev->private->state != DEV_STATE_ONLINE)
		return -EINVAL;
	/* Are we doing path grouping? */
	if (!cdev->private->flags.pgroup) {
		/* No, set state offline immediately. */
		ccw_device_done(cdev, DEV_STATE_OFFLINE);
		return 0;
	}
	/* Start Set Path Group commands. */
	cdev->private->state = DEV_STATE_DISBAND_PGID;
	ccw_device_disband_start(cdev);
	return 0;
}