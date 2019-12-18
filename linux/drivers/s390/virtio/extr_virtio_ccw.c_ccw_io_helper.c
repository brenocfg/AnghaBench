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
struct virtio_ccw_device {int curr_io; int err; int /*<<< orphan*/  io_lock; int /*<<< orphan*/  wait_q; int /*<<< orphan*/  cdev; } ;
struct ccw1 {int dummy; } ;
typedef  int __u32 ;

/* Variables and functions */
 int EBUSY ; 
 int VIRTIO_CCW_INTPARM_MASK ; 
 int ccw_device_start (int /*<<< orphan*/ ,struct ccw1*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 scalar_t__ doing_io (struct virtio_ccw_device*,int) ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ccw_io_helper(struct virtio_ccw_device *vcdev,
			 struct ccw1 *ccw, __u32 intparm)
{
	int ret;
	unsigned long flags;
	int flag = intparm & VIRTIO_CCW_INTPARM_MASK;

	mutex_lock(&vcdev->io_lock);
	do {
		spin_lock_irqsave(get_ccwdev_lock(vcdev->cdev), flags);
		ret = ccw_device_start(vcdev->cdev, ccw, intparm, 0, 0);
		if (!ret) {
			if (!vcdev->curr_io)
				vcdev->err = 0;
			vcdev->curr_io |= flag;
		}
		spin_unlock_irqrestore(get_ccwdev_lock(vcdev->cdev), flags);
		cpu_relax();
	} while (ret == -EBUSY);
	wait_event(vcdev->wait_q, doing_io(vcdev, flag) == 0);
	ret = ret ? ret : vcdev->err;
	mutex_unlock(&vcdev->io_lock);
	return ret;
}