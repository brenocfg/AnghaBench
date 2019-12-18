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
struct mdev_parent {TYPE_1__* ops; } ;
struct mdev_device {struct mdev_parent* parent; } ;
struct TYPE_2__ {long (* ioctl ) (struct mdev_device*,unsigned int,unsigned long) ;} ;

/* Variables and functions */
 long EINVAL ; 
 long stub1 (struct mdev_device*,unsigned int,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static long vfio_mdev_unlocked_ioctl(void *device_data,
				     unsigned int cmd, unsigned long arg)
{
	struct mdev_device *mdev = device_data;
	struct mdev_parent *parent = mdev->parent;

	if (unlikely(!parent->ops->ioctl))
		return -EINVAL;

	return parent->ops->ioctl(mdev, cmd, arg);
}