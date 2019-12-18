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
struct vfio_group {int /*<<< orphan*/  iommu_group; int /*<<< orphan*/  container_users; } ;
struct vfio_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (struct vfio_device*) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_WARN (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_group_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfio_device_put (struct vfio_device*) ; 
 struct vfio_device* vfio_group_get_device (struct vfio_group*,struct device*) ; 

__attribute__((used)) static int vfio_group_nb_add_dev(struct vfio_group *group, struct device *dev)
{
	struct vfio_device *device;

	/* Do we already know about it?  We shouldn't */
	device = vfio_group_get_device(group, dev);
	if (WARN_ON_ONCE(device)) {
		vfio_device_put(device);
		return 0;
	}

	/* Nothing to do for idle groups */
	if (!atomic_read(&group->container_users))
		return 0;

	/* TODO Prevent device auto probing */
	dev_WARN(dev, "Device added to live group %d!\n",
		 iommu_group_id(group->iommu_group));

	return 0;
}