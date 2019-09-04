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

/* Variables and functions */
 int PAGE_SHIFT ; 
 int bitmap_find_free_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int dma_base ; 
 int /*<<< orphan*/  dma_bitmap ; 
 int /*<<< orphan*/  dma_lock ; 
 int /*<<< orphan*/  dma_pages ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline u32 __alloc_dma_pages(int order)
{
	unsigned long flags;
	u32 pos;

	spin_lock_irqsave(&dma_lock, flags);
	pos = bitmap_find_free_region(dma_bitmap, dma_pages, order);
	spin_unlock_irqrestore(&dma_lock, flags);

	return dma_base + (pos << PAGE_SHIFT);
}