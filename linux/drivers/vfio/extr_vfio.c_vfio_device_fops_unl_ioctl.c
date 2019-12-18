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
struct vfio_device {int /*<<< orphan*/  device_data; TYPE_1__* ops; } ;
struct file {struct vfio_device* private_data; } ;
struct TYPE_2__ {long (* ioctl ) (int /*<<< orphan*/ ,unsigned int,unsigned long) ;} ;

/* Variables and functions */
 long EINVAL ; 
 long stub1 (int /*<<< orphan*/ ,unsigned int,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static long vfio_device_fops_unl_ioctl(struct file *filep,
				       unsigned int cmd, unsigned long arg)
{
	struct vfio_device *device = filep->private_data;

	if (unlikely(!device->ops->ioctl))
		return -EINVAL;

	return device->ops->ioctl(device->device_data, cmd, arg);
}