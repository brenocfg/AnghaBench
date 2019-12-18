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
struct iommu_ops {int (* dev_enable_feat ) (struct device*,int) ;} ;
struct device {TYPE_1__* bus; } ;
typedef  enum iommu_dev_features { ____Placeholder_iommu_dev_features } iommu_dev_features ;
struct TYPE_2__ {struct iommu_ops* iommu_ops; } ;

/* Variables and functions */
 int ENODEV ; 
 int stub1 (struct device*,int) ; 

int iommu_dev_enable_feature(struct device *dev, enum iommu_dev_features feat)
{
	const struct iommu_ops *ops = dev->bus->iommu_ops;

	if (ops && ops->dev_enable_feat)
		return ops->dev_enable_feat(dev, feat);

	return -ENODEV;
}