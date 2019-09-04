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
struct mtk_iommu_data {int /*<<< orphan*/  iommu; } ;
struct device {TYPE_1__* iommu_fwspec; } ;
struct TYPE_2__ {struct mtk_iommu_data* iommu_priv; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  iommu_device_unlink (int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  iommu_fwspec_free (struct device*) ; 
 int /*<<< orphan*/  iommu_group_remove_device (struct device*) ; 
 int /*<<< orphan*/  mtk_iommu_ops ; 

__attribute__((used)) static void mtk_iommu_remove_device(struct device *dev)
{
	struct mtk_iommu_data *data;

	if (!dev->iommu_fwspec || dev->iommu_fwspec->ops != &mtk_iommu_ops)
		return;

	data = dev->iommu_fwspec->iommu_priv;
	iommu_device_unlink(&data->iommu, dev);

	iommu_group_remove_device(dev);
	iommu_fwspec_free(dev);
}