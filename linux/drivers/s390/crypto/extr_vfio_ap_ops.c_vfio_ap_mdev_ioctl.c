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
struct mdev_device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  VFIO_DEVICE_GET_INFO 129 
#define  VFIO_DEVICE_RESET 128 
 TYPE_1__* matrix_dev ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int vfio_ap_mdev_get_device_info (unsigned long) ; 
 int vfio_ap_mdev_reset_queues (struct mdev_device*) ; 

__attribute__((used)) static ssize_t vfio_ap_mdev_ioctl(struct mdev_device *mdev,
				    unsigned int cmd, unsigned long arg)
{
	int ret;

	mutex_lock(&matrix_dev->lock);
	switch (cmd) {
	case VFIO_DEVICE_GET_INFO:
		ret = vfio_ap_mdev_get_device_info(arg);
		break;
	case VFIO_DEVICE_RESET:
		ret = vfio_ap_mdev_reset_queues(mdev);
		break;
	default:
		ret = -EOPNOTSUPP;
		break;
	}
	mutex_unlock(&matrix_dev->lock);

	return ret;
}