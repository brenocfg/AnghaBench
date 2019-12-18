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
struct ccw_device {TYPE_1__* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDEV_TODO_UNREG ; 
 int /*<<< orphan*/  CIO_GONE ; 
 int /*<<< orphan*/  DEV_STATE_DISCONNECTED ; 
 int ENODEV ; 
 scalar_t__ NOTIFY_OK ; 
 scalar_t__ ccw_device_notify (struct ccw_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccw_device_sched_todo (struct ccw_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int resume_handle_disc(struct ccw_device *cdev)
{
	cdev->private->state = DEV_STATE_DISCONNECTED;
	if (ccw_device_notify(cdev, CIO_GONE) == NOTIFY_OK)
		return 0;
	ccw_device_sched_todo(cdev, CDEV_TODO_UNREG);
	return -ENODEV;
}