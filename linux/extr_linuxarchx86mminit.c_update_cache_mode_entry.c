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
typedef  enum page_cache_mode { ____Placeholder_page_cache_mode } page_cache_mode ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int _PAGE_CACHE_MODE_WB ; 
 int /*<<< orphan*/ * __cachemode2pte_tbl ; 
 int /*<<< orphan*/  __cm_idx2pte (unsigned int) ; 
 int* __pte2cachemode_tbl ; 

void update_cache_mode_entry(unsigned entry, enum page_cache_mode cache)
{
	/* entry 0 MUST be WB (hardwired to speed up translations) */
	BUG_ON(!entry && cache != _PAGE_CACHE_MODE_WB);

	__cachemode2pte_tbl[cache] = __cm_idx2pte(entry);
	__pte2cachemode_tbl[entry] = cache;
}