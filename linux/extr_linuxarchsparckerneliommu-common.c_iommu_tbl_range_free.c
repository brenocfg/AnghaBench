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
typedef  unsigned long u64 ;
struct iommu_pool {int /*<<< orphan*/  lock; } ;
struct iommu_map_table {unsigned long table_shift; unsigned long table_map_base; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 unsigned long IOMMU_ERROR_CODE ; 
 int /*<<< orphan*/  bitmap_clear (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 struct iommu_pool* get_pool (struct iommu_map_table*,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void iommu_tbl_range_free(struct iommu_map_table *iommu, u64 dma_addr,
			  unsigned long npages, unsigned long entry)
{
	struct iommu_pool *pool;
	unsigned long flags;
	unsigned long shift = iommu->table_shift;

	if (entry == IOMMU_ERROR_CODE) /* use default addr->entry mapping */
		entry = (dma_addr - iommu->table_map_base) >> shift;
	pool = get_pool(iommu, entry);

	spin_lock_irqsave(&(pool->lock), flags);
	bitmap_clear(iommu->map, entry, npages);
	spin_unlock_irqrestore(&(pool->lock), flags);
}