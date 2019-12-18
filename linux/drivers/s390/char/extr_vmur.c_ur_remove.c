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
struct ccw_device {int /*<<< orphan*/  dev; scalar_t__ online; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_ccwdev_lock (struct ccw_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  ur_remove_attributes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ur_set_offline_force (struct ccw_device*,int) ; 
 int /*<<< orphan*/  urdev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmur_mutex ; 

__attribute__((used)) static void ur_remove(struct ccw_device *cdev)
{
	unsigned long flags;

	TRACE("ur_remove\n");

	mutex_lock(&vmur_mutex);

	if (cdev->online)
		ur_set_offline_force(cdev, 1);
	ur_remove_attributes(&cdev->dev);

	spin_lock_irqsave(get_ccwdev_lock(cdev), flags);
	urdev_put(dev_get_drvdata(&cdev->dev));
	dev_set_drvdata(&cdev->dev, NULL);
	spin_unlock_irqrestore(get_ccwdev_lock(cdev), flags);

	mutex_unlock(&vmur_mutex);
}