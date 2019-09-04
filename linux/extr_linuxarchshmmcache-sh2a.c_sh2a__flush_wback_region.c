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

__attribute__((used)) static void sh2a__flush_wback_region(void *start, int size)
{
#ifdef CONFIG_CACHE_WRITEBACK
	unsigned long v;
	unsigned long begin, end;
	unsigned long flags;
	int nr_ways;

	begin = (unsigned long)start & ~(L1_CACHE_BYTES-1);
	end = ((unsigned long)start + size + L1_CACHE_BYTES-1)
		& ~(L1_CACHE_BYTES-1);
	nr_ways = current_cpu_data.dcache.ways;

	local_irq_save(flags);
	jump_to_uncached();

	/* If there are too many pages then flush the entire cache */
	if (((end - begin) >> PAGE_SHIFT) >= MAX_OCACHE_PAGES) {
		begin = CACHE_OC_ADDRESS_ARRAY;
		end = begin + (nr_ways * current_cpu_data.dcache.way_size);

		for (v = begin; v < end; v += L1_CACHE_BYTES) {
			unsigned long data = __raw_readl(v);
			if (data & SH_CACHE_UPDATED)
				__raw_writel(data & ~SH_CACHE_UPDATED, v);
		}
	} else {
		int way;
		for (way = 0; way < nr_ways; way++) {
			for (v = begin; v < end; v += L1_CACHE_BYTES)
				sh2a_flush_oc_line(v, way);
		}
	}

	back_to_cached();
	local_irq_restore(flags);
#endif
}