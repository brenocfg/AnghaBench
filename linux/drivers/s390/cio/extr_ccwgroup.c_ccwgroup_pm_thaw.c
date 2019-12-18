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
struct ccwgroup_driver {int (* thaw ) (struct ccwgroup_device*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  driver; } ;
struct ccwgroup_device {scalar_t__ state; TYPE_1__ dev; } ;

/* Variables and functions */
 scalar_t__ CCWGROUP_ONLINE ; 
 int stub1 (struct ccwgroup_device*) ; 
 struct ccwgroup_device* to_ccwgroupdev (struct device*) ; 
 struct ccwgroup_driver* to_ccwgroupdrv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ccwgroup_pm_thaw(struct device *dev)
{
	struct ccwgroup_device *gdev = to_ccwgroupdev(dev);
	struct ccwgroup_driver *gdrv = to_ccwgroupdrv(gdev->dev.driver);

	if (!gdev->dev.driver || gdev->state != CCWGROUP_ONLINE)
		return 0;

	return gdrv->thaw ? gdrv->thaw(gdev) : 0;
}