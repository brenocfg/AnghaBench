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

/* Variables and functions */
 int /*<<< orphan*/  CACHE_OC_ADDRESS_ARRAY ; 
 int CCR_OCACHE_INVALIDATE ; 
 int L1_CACHE_BYTES ; 
 unsigned long MAX_OCACHE_PAGES ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  SH_CCR ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  back_to_cached () ; 
 int /*<<< orphan*/  jump_to_uncached () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  sh2a_invalidate_line (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void sh2a__flush_invalidate_region(void *start, int size)
{
	unsigned long v;
	unsigned long begin, end;
	unsigned long flags;

	begin = (unsigned long)start & ~(L1_CACHE_BYTES-1);
	end = ((unsigned long)start + size + L1_CACHE_BYTES-1)
		& ~(L1_CACHE_BYTES-1);

	local_irq_save(flags);
	jump_to_uncached();

	/* If there are too many pages then just blow the cache */
	if (((end - begin) >> PAGE_SHIFT) >= MAX_OCACHE_PAGES) {
		__raw_writel(__raw_readl(SH_CCR) | CCR_OCACHE_INVALIDATE,
			     SH_CCR);
	} else {
		for (v = begin; v < end; v += L1_CACHE_BYTES)
			sh2a_invalidate_line(CACHE_OC_ADDRESS_ARRAY, v);
	}

	back_to_cached();
	local_irq_restore(flags);
}