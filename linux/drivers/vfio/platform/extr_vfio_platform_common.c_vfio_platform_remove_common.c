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
struct vfio_platform_device {int /*<<< orphan*/  device; } ;
struct device {int /*<<< orphan*/  iommu_group; } ;

/* Variables and functions */
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 struct vfio_platform_device* vfio_del_group_dev (struct device*) ; 
 int /*<<< orphan*/  vfio_iommu_group_put (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  vfio_platform_put_reset (struct vfio_platform_device*) ; 

struct vfio_platform_device *vfio_platform_remove_common(struct device *dev)
{
	struct vfio_platform_device *vdev;

	vdev = vfio_del_group_dev(dev);

	if (vdev) {
		pm_runtime_disable(vdev->device);
		vfio_platform_put_reset(vdev);
		vfio_iommu_group_put(dev->iommu_group, dev);
	}

	return vdev;
}