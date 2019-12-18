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
struct rk_iommu {int /*<<< orphan*/  group; } ;
struct iommu_group {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct iommu_group* iommu_group_ref_get (int /*<<< orphan*/ ) ; 
 struct rk_iommu* rk_iommu_from_dev (struct device*) ; 

__attribute__((used)) static struct iommu_group *rk_iommu_device_group(struct device *dev)
{
	struct rk_iommu *iommu;

	iommu = rk_iommu_from_dev(dev);

	return iommu_group_ref_get(iommu->group);
}