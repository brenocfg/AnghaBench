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
struct ccw_device {TYPE_1__* private; int /*<<< orphan*/  (* handler ) (struct ccw_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {int iretry; int /*<<< orphan*/  intparm; int /*<<< orphan*/  state; int /*<<< orphan*/  async_kill_io_rc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_STATE_TIMEOUT_KILL ; 
 int EBUSY ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ERR_PTR (int /*<<< orphan*/ ) ; 
 int HZ ; 
 int ccw_device_cancel_halt_clear (struct ccw_device*) ; 
 int /*<<< orphan*/  ccw_device_online_verify (struct ccw_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccw_device_set_timeout (struct ccw_device*,int) ; 
 int /*<<< orphan*/  stub1 (struct ccw_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ccw_device_kill_io(struct ccw_device *cdev)
{
	int ret;

	ccw_device_set_timeout(cdev, 0);
	cdev->private->iretry = 255;
	cdev->private->async_kill_io_rc = -EIO;
	ret = ccw_device_cancel_halt_clear(cdev);
	if (ret == -EBUSY) {
		ccw_device_set_timeout(cdev, 3*HZ);
		cdev->private->state = DEV_STATE_TIMEOUT_KILL;
		return;
	}
	/* Start delayed path verification. */
	ccw_device_online_verify(cdev, 0);
	if (cdev->handler)
		cdev->handler(cdev, cdev->private->intparm,
			      ERR_PTR(-EIO));
}