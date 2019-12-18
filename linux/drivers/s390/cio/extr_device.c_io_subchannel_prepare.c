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
struct subchannel {int dummy; } ;
struct ccw_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  device_is_registered (int /*<<< orphan*/ *) ; 
 struct ccw_device* sch_get_cdev (struct subchannel*) ; 

__attribute__((used)) static int io_subchannel_prepare(struct subchannel *sch)
{
	struct ccw_device *cdev;
	/*
	 * Don't allow suspend while a ccw device registration
	 * is still outstanding.
	 */
	cdev = sch_get_cdev(sch);
	if (cdev && !device_is_registered(&cdev->dev))
		return -EAGAIN;
	return 0;
}