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
typedef  int u32 ;
struct scatterlist {int dma_address; } ;
struct iommu_map_table {int table_map_base; } ;
struct iommu {int /*<<< orphan*/ * page_table; struct iommu_map_table tbl; scalar_t__ iommu_ctxflush; } ;
typedef  int /*<<< orphan*/  iopte_t ;

/* Variables and functions */
 unsigned long IOPTE_CONTEXT ; 
 int IO_PAGE_MASK ; 
 int IO_PAGE_SHIFT ; 
 unsigned long iopte_val (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long fetch_sg_ctx(struct iommu *iommu, struct scatterlist *sg)
{
	unsigned long ctx = 0;

	if (iommu->iommu_ctxflush) {
		iopte_t *base;
		u32 bus_addr;
		struct iommu_map_table *tbl = &iommu->tbl;

		bus_addr = sg->dma_address & IO_PAGE_MASK;
		base = iommu->page_table +
			((bus_addr - tbl->table_map_base) >> IO_PAGE_SHIFT);

		ctx = (iopte_val(*base) & IOPTE_CONTEXT) >> 47UL;
	}
	return ctx;
}