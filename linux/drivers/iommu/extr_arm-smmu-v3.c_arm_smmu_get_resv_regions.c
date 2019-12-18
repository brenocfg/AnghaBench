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
struct list_head {int dummy; } ;
struct iommu_resv_region {int /*<<< orphan*/  list; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int IOMMU_MMIO ; 
 int IOMMU_NOEXEC ; 
 int /*<<< orphan*/  IOMMU_RESV_SW_MSI ; 
 int IOMMU_WRITE ; 
 int /*<<< orphan*/  MSI_IOVA_BASE ; 
 int /*<<< orphan*/  MSI_IOVA_LENGTH ; 
 struct iommu_resv_region* iommu_alloc_resv_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_dma_get_resv_regions (struct device*,struct list_head*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 

__attribute__((used)) static void arm_smmu_get_resv_regions(struct device *dev,
				      struct list_head *head)
{
	struct iommu_resv_region *region;
	int prot = IOMMU_WRITE | IOMMU_NOEXEC | IOMMU_MMIO;

	region = iommu_alloc_resv_region(MSI_IOVA_BASE, MSI_IOVA_LENGTH,
					 prot, IOMMU_RESV_SW_MSI);
	if (!region)
		return;

	list_add_tail(&region->list, head);

	iommu_dma_get_resv_regions(dev, head);
}