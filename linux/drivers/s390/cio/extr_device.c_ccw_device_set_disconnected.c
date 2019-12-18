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
struct ccw_device {scalar_t__ online; TYPE_2__* private; } ;
struct TYPE_3__ {scalar_t__ fake_irb; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; TYPE_1__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_STATE_DISCONNECTED ; 
 int /*<<< orphan*/  ccw_device_schedule_recovery () ; 
 int /*<<< orphan*/  ccw_device_set_timeout (struct ccw_device*,int /*<<< orphan*/ ) ; 

void ccw_device_set_disconnected(struct ccw_device *cdev)
{
	if (!cdev)
		return;
	ccw_device_set_timeout(cdev, 0);
	cdev->private->flags.fake_irb = 0;
	cdev->private->state = DEV_STATE_DISCONNECTED;
	if (cdev->online)
		ccw_device_schedule_recovery();
}