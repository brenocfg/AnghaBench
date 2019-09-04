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
struct iommu_table {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DMA_NONE ; 
 int /*<<< orphan*/  IOMMU_PAGE_SIZE (struct iommu_table*) ; 
 int /*<<< orphan*/  iommu_free (struct iommu_table*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int iommu_num_pages (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

void iommu_unmap_page(struct iommu_table *tbl, dma_addr_t dma_handle,
		      size_t size, enum dma_data_direction direction,
		      unsigned long attrs)
{
	unsigned int npages;

	BUG_ON(direction == DMA_NONE);

	if (tbl) {
		npages = iommu_num_pages(dma_handle, size,
					 IOMMU_PAGE_SIZE(tbl));
		iommu_free(tbl, dma_handle, npages);
	}
}