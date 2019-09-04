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
 int __tm6000_open (struct file*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 
 struct video_device* video_devdata (struct file*) ; 

__attribute__((used)) static int tm6000_open(struct file *file)
{
	struct video_device *vdev = video_devdata(file);
	int res;

	mutex_lock(vdev->lock);
	res = __tm6000_open(file);
	mutex_unlock(vdev->lock);
	return res;
}