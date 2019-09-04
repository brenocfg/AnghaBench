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
struct iommu_table {unsigned long it_page_shift; unsigned long it_offset; int /*<<< orphan*/  it_map; TYPE_1__* it_ops; } ;
struct iommu_pool {int /*<<< orphan*/  lock; } ;
typedef  unsigned long dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* clear ) (struct iommu_table*,unsigned long,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_clear (int /*<<< orphan*/ ,unsigned long,unsigned int) ; 
 struct iommu_pool* get_pool (struct iommu_table*,unsigned long) ; 
 int /*<<< orphan*/  iommu_free_check (struct iommu_table*,unsigned long,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct iommu_table*,unsigned long,unsigned int) ; 

__attribute__((used)) static void __iommu_free(struct iommu_table *tbl, dma_addr_t dma_addr,
			 unsigned int npages)
{
	unsigned long entry, free_entry;
	unsigned long flags;
	struct iommu_pool *pool;

	entry = dma_addr >> tbl->it_page_shift;
	free_entry = entry - tbl->it_offset;

	pool = get_pool(tbl, free_entry);

	if (!iommu_free_check(tbl, dma_addr, npages))
		return;

	tbl->it_ops->clear(tbl, entry, npages);

	spin_lock_irqsave(&(pool->lock), flags);
	bitmap_clear(tbl->it_map, free_entry, npages);
	spin_unlock_irqrestore(&(pool->lock), flags);
}