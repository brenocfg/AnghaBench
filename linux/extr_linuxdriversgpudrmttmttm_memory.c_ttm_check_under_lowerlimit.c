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
typedef  scalar_t__ uint64_t ;
struct ttm_operation_ctx {int flags; } ;
struct ttm_mem_global {scalar_t__ lower_mem_limit; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int TTM_OPT_FLAG_FORCE_ALLOC ; 
 scalar_t__ get_nr_swap_pages () ; 
 scalar_t__ si_mem_available () ; 

bool
ttm_check_under_lowerlimit(struct ttm_mem_global *glob,
			uint64_t num_pages,
			struct ttm_operation_ctx *ctx)
{
	int64_t available;

	if (ctx->flags & TTM_OPT_FLAG_FORCE_ALLOC)
		return false;

	available = get_nr_swap_pages() + si_mem_available();
	available -= num_pages;
	if (available < glob->lower_mem_limit)
		return true;

	return false;
}