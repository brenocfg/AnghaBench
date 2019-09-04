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
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  R5K_Page_Invalidate_S ; 
 int SC_PAGE ; 
 int /*<<< orphan*/  blast_r5000_scache () ; 
 int /*<<< orphan*/  cache_op (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long scache_size ; 

__attribute__((used)) static void r5k_dma_cache_inv_sc(unsigned long addr, unsigned long size)
{
	unsigned long end, a;

	/* Catch bad driver code */
	BUG_ON(size == 0);

	if (size >= scache_size) {
		blast_r5000_scache();
		return;
	}

	/* On the R5000 secondary cache we cannot
	 * invalidate less than a page at a time.
	 * The secondary cache is physically indexed, write-through.
	 */
	a = addr & ~(SC_PAGE - 1);
	end = (addr + size - 1) & ~(SC_PAGE - 1);
	while (a <= end) {
		cache_op(R5K_Page_Invalidate_S, a);
		a += SC_PAGE;
	}
}