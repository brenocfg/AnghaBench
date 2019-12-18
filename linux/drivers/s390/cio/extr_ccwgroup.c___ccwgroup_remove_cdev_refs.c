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
struct ccwgroup_device {int count; struct ccw_device** cdev; } ;
struct ccw_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  ccwlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __ccwgroup_remove_cdev_refs(struct ccwgroup_device *gdev)
{
	struct ccw_device *cdev;
	int i;

	for (i = 0; i < gdev->count; i++) {
		cdev = gdev->cdev[i];
		if (!cdev)
			continue;
		spin_lock_irq(cdev->ccwlock);
		dev_set_drvdata(&cdev->dev, NULL);
		spin_unlock_irq(cdev->ccwlock);
		gdev->cdev[i] = NULL;
		put_device(&cdev->dev);
	}
}