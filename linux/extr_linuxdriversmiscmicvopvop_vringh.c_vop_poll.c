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
struct vop_vdev {int /*<<< orphan*/  vdev_mutex; scalar_t__ poll_wake; int /*<<< orphan*/  waitq; } ;
struct file {struct vop_vdev* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ vop_vdev_inited (struct vop_vdev*) ; 

__attribute__((used)) static __poll_t vop_poll(struct file *f, poll_table *wait)
{
	struct vop_vdev *vdev = f->private_data;
	__poll_t mask = 0;

	mutex_lock(&vdev->vdev_mutex);
	if (vop_vdev_inited(vdev)) {
		mask = EPOLLERR;
		goto done;
	}
	poll_wait(f, &vdev->waitq, wait);
	if (vop_vdev_inited(vdev)) {
		mask = EPOLLERR;
	} else if (vdev->poll_wake) {
		vdev->poll_wake = 0;
		mask = EPOLLIN | EPOLLOUT;
	}
done:
	mutex_unlock(&vdev->vdev_mutex);
	return mask;
}