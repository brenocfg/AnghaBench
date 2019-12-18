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
struct video_device {int /*<<< orphan*/  lock; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int ivtv_open (struct file*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 
 struct video_device* video_devdata (struct file*) ; 

int ivtv_v4l2_open(struct file *filp)
{
	struct video_device *vdev = video_devdata(filp);
	int res;

	if (mutex_lock_interruptible(vdev->lock))
		return -ERESTARTSYS;
	res = ivtv_open(filp);
	mutex_unlock(vdev->lock);
	return res;
}