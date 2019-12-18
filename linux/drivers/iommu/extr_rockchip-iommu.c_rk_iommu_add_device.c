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
struct rk_iommu {int /*<<< orphan*/  dev; int /*<<< orphan*/  iommu; } ;
struct iommu_group {int dummy; } ;
struct TYPE_2__ {struct rk_iommudata* iommu; } ;
struct device {TYPE_1__ archdata; } ;

/* Variables and functions */
 int DL_FLAG_PM_RUNTIME ; 
 int DL_FLAG_STATELESS ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (struct iommu_group*) ; 
 int PTR_ERR (struct iommu_group*) ; 
 int /*<<< orphan*/  device_link_add (struct device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iommu_device_link (int /*<<< orphan*/ *,struct device*) ; 
 struct iommu_group* iommu_group_get_for_dev (struct device*) ; 
 int /*<<< orphan*/  iommu_group_put (struct iommu_group*) ; 
 struct rk_iommu* rk_iommu_from_dev (struct device*) ; 

__attribute__((used)) static int rk_iommu_add_device(struct device *dev)
{
	struct iommu_group *group;
	struct rk_iommu *iommu;
	struct rk_iommudata *data;

	data = dev->archdata.iommu;
	if (!data)
		return -ENODEV;

	iommu = rk_iommu_from_dev(dev);

	group = iommu_group_get_for_dev(dev);
	if (IS_ERR(group))
		return PTR_ERR(group);
	iommu_group_put(group);

	iommu_device_link(&iommu->iommu, dev);
	data->link = device_link_add(dev, iommu->dev,
				     DL_FLAG_STATELESS | DL_FLAG_PM_RUNTIME);

	return 0;
}