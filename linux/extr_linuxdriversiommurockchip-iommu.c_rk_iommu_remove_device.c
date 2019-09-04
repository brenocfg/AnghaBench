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
struct rk_iommudata {int /*<<< orphan*/  link; } ;
struct rk_iommu {int /*<<< orphan*/  iommu; } ;
struct TYPE_2__ {struct rk_iommudata* iommu; } ;
struct device {TYPE_1__ archdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_link_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_device_unlink (int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  iommu_group_remove_device (struct device*) ; 
 struct rk_iommu* rk_iommu_from_dev (struct device*) ; 

__attribute__((used)) static void rk_iommu_remove_device(struct device *dev)
{
	struct rk_iommu *iommu;
	struct rk_iommudata *data = dev->archdata.iommu;

	iommu = rk_iommu_from_dev(dev);

	device_link_del(data->link);
	iommu_device_unlink(&iommu->iommu, dev);
	iommu_group_remove_device(dev);
}