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
struct ccwgroup_device {int /*<<< orphan*/  reg_mutex; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ccwgroup_remove_cdev_refs (struct ccwgroup_device*) ; 
 int /*<<< orphan*/  __ccwgroup_remove_symlinks (struct ccwgroup_device*) ; 
 scalar_t__ device_is_registered (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ccwgroup_ungroup(struct ccwgroup_device *gdev)
{
	mutex_lock(&gdev->reg_mutex);
	if (device_is_registered(&gdev->dev)) {
		__ccwgroup_remove_symlinks(gdev);
		device_unregister(&gdev->dev);
		__ccwgroup_remove_cdev_refs(gdev);
	}
	mutex_unlock(&gdev->reg_mutex);
}