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
struct iommu_table {unsigned long it_size; int /*<<< orphan*/  it_lock; int /*<<< orphan*/  it_map; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  bitmap_set (int /*<<< orphan*/ ,unsigned long,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void iommu_range_reserve(struct iommu_table *tbl,
	unsigned long start_addr, unsigned int npages)
{
	unsigned long index;
	unsigned long end;
	unsigned long flags;

	index = start_addr >> PAGE_SHIFT;

	/* bail out if we're asked to reserve a region we don't cover */
	if (index >= tbl->it_size)
		return;

	end = index + npages;
	if (end > tbl->it_size) /* don't go off the table */
		end = tbl->it_size;

	spin_lock_irqsave(&tbl->it_lock, flags);

	bitmap_set(tbl->it_map, index, npages);

	spin_unlock_irqrestore(&tbl->it_lock, flags);
}