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
struct iommu_group {int dummy; } ;
struct device {int /*<<< orphan*/  iommu_fwspec; } ;
struct TYPE_2__ {int /*<<< orphan*/  iommu; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct iommu_group*) ; 
 int PTR_ERR (struct iommu_group*) ; 
 TYPE_1__* gart_handle ; 
 int /*<<< orphan*/  iommu_device_link (int /*<<< orphan*/ *,struct device*) ; 
 struct iommu_group* iommu_group_get_for_dev (struct device*) ; 
 int /*<<< orphan*/  iommu_group_put (struct iommu_group*) ; 

__attribute__((used)) static int gart_iommu_add_device(struct device *dev)
{
	struct iommu_group *group;

	if (!dev->iommu_fwspec)
		return -ENODEV;

	group = iommu_group_get_for_dev(dev);
	if (IS_ERR(group))
		return PTR_ERR(group);

	iommu_group_put(group);

	iommu_device_link(&gart_handle->iommu, dev);

	return 0;
}