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
struct video_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_FL_REGISTERED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_is_registered (struct video_device*) ; 
 int /*<<< orphan*/  videodev_lock ; 

void video_unregister_device(struct video_device *vdev)
{
	/* Check if vdev was ever registered at all */
	if (!vdev || !video_is_registered(vdev))
		return;

	mutex_lock(&videodev_lock);
	/* This must be in a critical section to prevent a race with v4l2_open.
	 * Once this bit has been cleared video_get may never be called again.
	 */
	clear_bit(V4L2_FL_REGISTERED, &vdev->flags);
	mutex_unlock(&videodev_lock);
	device_unregister(&vdev->dev);
}