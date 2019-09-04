#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rtl2832_sdr_dev {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  vb_queue_lock; int /*<<< orphan*/  v4l2_lock; int /*<<< orphan*/  vdev; int /*<<< orphan*/ * udev; } ;
struct TYPE_6__ {TYPE_2__* parent; } ;
struct platform_device {TYPE_3__ dev; } ;
struct TYPE_5__ {TYPE_1__* driver; } ;
struct TYPE_4__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct rtl2832_sdr_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  v4l2_device_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rtl2832_sdr_remove(struct platform_device *pdev)
{
	struct rtl2832_sdr_dev *dev = platform_get_drvdata(pdev);

	dev_dbg(&pdev->dev, "\n");

	mutex_lock(&dev->vb_queue_lock);
	mutex_lock(&dev->v4l2_lock);
	/* No need to keep the urbs around after disconnection */
	dev->udev = NULL;
	v4l2_device_disconnect(&dev->v4l2_dev);
	video_unregister_device(&dev->vdev);
	mutex_unlock(&dev->v4l2_lock);
	mutex_unlock(&dev->vb_queue_lock);
	v4l2_device_put(&dev->v4l2_dev);
	module_put(pdev->dev.parent->driver->owner);

	return 0;
}