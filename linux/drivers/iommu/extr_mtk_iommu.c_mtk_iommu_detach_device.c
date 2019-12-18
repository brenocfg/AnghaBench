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
struct mtk_iommu_data {int dummy; } ;
struct iommu_domain {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct mtk_iommu_data* iommu_priv; } ;

/* Variables and functions */
 TYPE_1__* dev_iommu_fwspec_get (struct device*) ; 
 int /*<<< orphan*/  mtk_iommu_config (struct mtk_iommu_data*,struct device*,int) ; 

__attribute__((used)) static void mtk_iommu_detach_device(struct iommu_domain *domain,
				    struct device *dev)
{
	struct mtk_iommu_data *data = dev_iommu_fwspec_get(dev)->iommu_priv;

	if (!data)
		return;

	mtk_iommu_config(data, dev, false);
}