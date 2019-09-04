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
 int CACHE_LINE_SIZE ; 
 int /*<<< orphan*/  dsb () ; 
 unsigned long l2_map_va (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  l2_unmap_va (unsigned long) ; 
 int /*<<< orphan*/  xsc3_l2_clean_mva (unsigned long) ; 
 int /*<<< orphan*/  xsc3_l2_inv_all () ; 
 int /*<<< orphan*/  xsc3_l2_inv_mva (unsigned long) ; 

__attribute__((used)) static void xsc3_l2_inv_range(unsigned long start, unsigned long end)
{
	unsigned long vaddr;

	if (start == 0 && end == -1ul) {
		xsc3_l2_inv_all();
		return;
	}

	vaddr = -1;  /* to force the first mapping */

	/*
	 * Clean and invalidate partial first cache line.
	 */
	if (start & (CACHE_LINE_SIZE - 1)) {
		vaddr = l2_map_va(start & ~(CACHE_LINE_SIZE - 1), vaddr);
		xsc3_l2_clean_mva(vaddr);
		xsc3_l2_inv_mva(vaddr);
		start = (start | (CACHE_LINE_SIZE - 1)) + 1;
	}

	/*
	 * Invalidate all full cache lines between 'start' and 'end'.
	 */
	while (start < (end & ~(CACHE_LINE_SIZE - 1))) {
		vaddr = l2_map_va(start, vaddr);
		xsc3_l2_inv_mva(vaddr);
		start += CACHE_LINE_SIZE;
	}

	/*
	 * Clean and invalidate partial last cache line.
	 */
	if (start < end) {
		vaddr = l2_map_va(start, vaddr);
		xsc3_l2_clean_mva(vaddr);
		xsc3_l2_inv_mva(vaddr);
	}

	l2_unmap_va(vaddr);

	dsb();
}