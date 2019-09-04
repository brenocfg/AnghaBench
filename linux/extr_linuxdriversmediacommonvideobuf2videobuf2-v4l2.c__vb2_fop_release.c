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
struct video_device {TYPE_1__* queue; } ;
struct mutex {int dummy; } ;
struct file {int /*<<< orphan*/ * private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/ * owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (struct mutex*) ; 
 int /*<<< orphan*/  mutex_unlock (struct mutex*) ; 
 int v4l2_fh_release (struct file*) ; 
 int /*<<< orphan*/  vb2_queue_release (TYPE_1__*) ; 
 struct video_device* video_devdata (struct file*) ; 

int _vb2_fop_release(struct file *file, struct mutex *lock)
{
	struct video_device *vdev = video_devdata(file);

	if (lock)
		mutex_lock(lock);
	if (file->private_data == vdev->queue->owner) {
		vb2_queue_release(vdev->queue);
		vdev->queue->owner = NULL;
	}
	if (lock)
		mutex_unlock(lock);
	return v4l2_fh_release(file);
}