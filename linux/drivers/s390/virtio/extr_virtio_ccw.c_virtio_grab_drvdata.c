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
struct virtio_ccw_device {int going_away; } ;
struct ccw_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct virtio_ccw_device* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_ccwdev_lock (struct ccw_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static struct virtio_ccw_device *virtio_grab_drvdata(struct ccw_device *cdev)
{
	unsigned long flags;
	struct virtio_ccw_device *vcdev;

	spin_lock_irqsave(get_ccwdev_lock(cdev), flags);
	vcdev = dev_get_drvdata(&cdev->dev);
	if (!vcdev || vcdev->going_away) {
		spin_unlock_irqrestore(get_ccwdev_lock(cdev), flags);
		return NULL;
	}
	vcdev->going_away = true;
	spin_unlock_irqrestore(get_ccwdev_lock(cdev), flags);
	return vcdev;
}