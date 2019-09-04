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
struct list_head {int dummy; } ;
struct device {TYPE_1__* iommu_fwspec; } ;
struct TYPE_2__ {int /*<<< orphan*/  iommu_fwnode; } ;

/* Variables and functions */
 int /*<<< orphan*/  iort_iommu_msi_get_resv_regions (struct device*,struct list_head*) ; 
 int /*<<< orphan*/  is_of_node (int /*<<< orphan*/ ) ; 

void iommu_dma_get_resv_regions(struct device *dev, struct list_head *list)
{

	if (!is_of_node(dev->iommu_fwspec->iommu_fwnode))
		iort_iommu_msi_get_resv_regions(dev, list);

}