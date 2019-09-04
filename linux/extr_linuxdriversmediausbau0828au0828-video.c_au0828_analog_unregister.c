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
struct au0828_dev {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  vbi_dev; int /*<<< orphan*/  vdev; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ AU0828_VMUX_UNDEFINED ; 
 TYPE_1__ AUVI_INPUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au0828_sysfs_lock ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

int au0828_analog_unregister(struct au0828_dev *dev)
{
	dprintk(1, "au0828_analog_unregister called\n");

	/* No analog TV */
	if (AUVI_INPUT(0).type == AU0828_VMUX_UNDEFINED)
		return 0;

	mutex_lock(&au0828_sysfs_lock);
	video_unregister_device(&dev->vdev);
	video_unregister_device(&dev->vbi_dev);
	mutex_unlock(&au0828_sysfs_lock);

	v4l2_device_disconnect(&dev->v4l2_dev);
	v4l2_device_put(&dev->v4l2_dev);

	return 1;
}