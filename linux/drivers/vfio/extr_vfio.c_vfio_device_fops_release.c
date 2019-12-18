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
struct vfio_device {int /*<<< orphan*/  group; int /*<<< orphan*/  device_data; TYPE_1__* ops; } ;
struct inode {int dummy; } ;
struct file {struct vfio_device* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* release ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfio_device_put (struct vfio_device*) ; 
 int /*<<< orphan*/  vfio_group_try_dissolve_container (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vfio_device_fops_release(struct inode *inode, struct file *filep)
{
	struct vfio_device *device = filep->private_data;

	device->ops->release(device->device_data);

	vfio_group_try_dissolve_container(device->group);

	vfio_device_put(device);

	return 0;
}