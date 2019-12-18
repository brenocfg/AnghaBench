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
struct iommu_group {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * iommu_group_get_iommudata (struct iommu_group*) ; 
 int /*<<< orphan*/  iommu_group_put (struct iommu_group*) ; 
 int /*<<< orphan*/  iommu_group_remove_device (struct device*) ; 
 int /*<<< orphan*/  noiommu ; 

void vfio_iommu_group_put(struct iommu_group *group, struct device *dev)
{
#ifdef CONFIG_VFIO_NOIOMMU
	if (iommu_group_get_iommudata(group) == &noiommu)
		iommu_group_remove_device(dev);
#endif

	iommu_group_put(group);
}