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
struct ttm_page_pool {int dummy; } ;
typedef  enum ttm_caching_state { ____Placeholder_ttm_caching_state } ttm_caching_state ;
struct TYPE_2__ {struct ttm_page_pool* pools; } ;

/* Variables and functions */
 int TTM_PAGE_FLAG_DMA32 ; 
 TYPE_1__* _manager ; 
 int tt_cached ; 
 int tt_wc ; 

__attribute__((used)) static struct ttm_page_pool *ttm_get_pool(int flags, bool huge,
					  enum ttm_caching_state cstate)
{
	int pool_index;

	if (cstate == tt_cached)
		return NULL;

	if (cstate == tt_wc)
		pool_index = 0x0;
	else
		pool_index = 0x1;

	if (flags & TTM_PAGE_FLAG_DMA32) {
		if (huge)
			return NULL;
		pool_index |= 0x2;

	} else if (huge) {
		pool_index |= 0x4;
	}

	return &_manager->pools[pool_index];
}