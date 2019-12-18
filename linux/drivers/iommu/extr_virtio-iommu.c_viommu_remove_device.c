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
struct viommu_endpoint {int /*<<< orphan*/  resv_regions; TYPE_1__* viommu; } ;
struct iommu_fwspec {struct viommu_endpoint* iommu_priv; int /*<<< orphan*/ * ops; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  iommu; } ;

/* Variables and functions */
 struct iommu_fwspec* dev_iommu_fwspec_get (struct device*) ; 
 int /*<<< orphan*/  iommu_device_unlink (int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  iommu_group_remove_device (struct device*) ; 
 int /*<<< orphan*/  kfree (struct viommu_endpoint*) ; 
 int /*<<< orphan*/  viommu_ops ; 
 int /*<<< orphan*/  viommu_put_resv_regions (struct device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void viommu_remove_device(struct device *dev)
{
	struct viommu_endpoint *vdev;
	struct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);

	if (!fwspec || fwspec->ops != &viommu_ops)
		return;

	vdev = fwspec->iommu_priv;

	iommu_group_remove_device(dev);
	iommu_device_unlink(&vdev->viommu->iommu, dev);
	viommu_put_resv_regions(dev, &vdev->resv_regions);
	kfree(vdev);
}