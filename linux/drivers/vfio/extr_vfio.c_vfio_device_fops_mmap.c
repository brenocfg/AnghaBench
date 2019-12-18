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
struct vm_area_struct {int dummy; } ;
struct vfio_device {int /*<<< orphan*/  device_data; TYPE_1__* ops; } ;
struct file {struct vfio_device* private_data; } ;
struct TYPE_2__ {int (* mmap ) (int /*<<< orphan*/ ,struct vm_area_struct*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (int /*<<< orphan*/ ,struct vm_area_struct*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int vfio_device_fops_mmap(struct file *filep, struct vm_area_struct *vma)
{
	struct vfio_device *device = filep->private_data;

	if (unlikely(!device->ops->mmap))
		return -EINVAL;

	return device->ops->mmap(device->device_data, vma);
}