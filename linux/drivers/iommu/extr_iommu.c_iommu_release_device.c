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
struct iommu_ops {int /*<<< orphan*/  (* remove_device ) (struct device*) ;} ;
struct device {scalar_t__ iommu_group; TYPE_1__* bus; } ;
struct TYPE_2__ {struct iommu_ops* iommu_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  iommu_free_dev_param (struct device*) ; 
 int /*<<< orphan*/  stub1 (struct device*) ; 

void iommu_release_device(struct device *dev)
{
	const struct iommu_ops *ops = dev->bus->iommu_ops;

	if (dev->iommu_group)
		ops->remove_device(dev);

	iommu_free_dev_param(dev);
}