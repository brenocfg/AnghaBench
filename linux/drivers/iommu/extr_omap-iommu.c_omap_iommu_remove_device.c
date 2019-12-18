#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct omap_iommu_arch_data {TYPE_1__* iommu_dev; } ;
struct TYPE_4__ {struct omap_iommu_arch_data* iommu; } ;
struct device {TYPE_2__ archdata; int /*<<< orphan*/  of_node; } ;
struct TYPE_3__ {int /*<<< orphan*/  iommu; } ;

/* Variables and functions */
 int /*<<< orphan*/  iommu_device_unlink (int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  iommu_group_remove_device (struct device*) ; 
 int /*<<< orphan*/  kfree (struct omap_iommu_arch_data*) ; 

__attribute__((used)) static void omap_iommu_remove_device(struct device *dev)
{
	struct omap_iommu_arch_data *arch_data = dev->archdata.iommu;

	if (!dev->of_node || !arch_data)
		return;

	iommu_device_unlink(&arch_data->iommu_dev->iommu, dev);
	iommu_group_remove_device(dev);

	dev->archdata.iommu = NULL;
	kfree(arch_data);

}