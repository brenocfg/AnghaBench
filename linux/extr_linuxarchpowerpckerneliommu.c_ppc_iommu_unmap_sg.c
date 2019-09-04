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
struct scatterlist {int /*<<< orphan*/  dma_length; int /*<<< orphan*/  dma_address; } ;
struct iommu_table {TYPE_1__* it_ops; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* flush ) (struct iommu_table*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DMA_NONE ; 
 int /*<<< orphan*/  IOMMU_PAGE_SIZE (struct iommu_table*) ; 
 int /*<<< orphan*/  __iommu_free (struct iommu_table*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int iommu_num_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 int /*<<< orphan*/  stub1 (struct iommu_table*) ; 

void ppc_iommu_unmap_sg(struct iommu_table *tbl, struct scatterlist *sglist,
			int nelems, enum dma_data_direction direction,
			unsigned long attrs)
{
	struct scatterlist *sg;

	BUG_ON(direction == DMA_NONE);

	if (!tbl)
		return;

	sg = sglist;
	while (nelems--) {
		unsigned int npages;
		dma_addr_t dma_handle = sg->dma_address;

		if (sg->dma_length == 0)
			break;
		npages = iommu_num_pages(dma_handle, sg->dma_length,
					 IOMMU_PAGE_SIZE(tbl));
		__iommu_free(tbl, dma_handle, npages);
		sg = sg_next(sg);
	}

	/* Flush/invalidate TLBs if necessary. As for iommu_free(), we
	 * do not do an mb() here, the affected platforms do not need it
	 * when freeing.
	 */
	if (tbl->it_ops->flush)
		tbl->it_ops->flush(tbl);
}