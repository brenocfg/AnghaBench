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
struct video_device {struct mutex* lock; } ;
struct mutex {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 long ENODEV ; 
 long ERESTARTSYS ; 
 scalar_t__ mutex_lock_interruptible (struct mutex*) ; 
 int /*<<< orphan*/  mutex_unlock (struct mutex*) ; 
 long subdev_do_ioctl (struct file*,unsigned int,void*) ; 
 struct video_device* video_devdata (struct file*) ; 
 scalar_t__ video_is_registered (struct video_device*) ; 

__attribute__((used)) static long subdev_do_ioctl_lock(struct file *file, unsigned int cmd, void *arg)
{
	struct video_device *vdev = video_devdata(file);
	struct mutex *lock = vdev->lock;
	long ret = -ENODEV;

	if (lock && mutex_lock_interruptible(lock))
		return -ERESTARTSYS;
	if (video_is_registered(vdev))
		ret = subdev_do_ioctl(file, cmd, arg);
	if (lock)
		mutex_unlock(lock);
	return ret;
}