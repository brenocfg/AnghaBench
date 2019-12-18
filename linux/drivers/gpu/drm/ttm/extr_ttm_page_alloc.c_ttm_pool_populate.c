#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ttm_tt {scalar_t__ state; unsigned int num_pages; int page_flags; int /*<<< orphan*/ * pages; int /*<<< orphan*/  caching_state; TYPE_2__* bdev; } ;
struct ttm_operation_ctx {int dummy; } ;
struct ttm_mem_global {int dummy; } ;
struct TYPE_4__ {TYPE_1__* glob; } ;
struct TYPE_3__ {struct ttm_mem_global* mem_glob; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int TTM_PAGE_FLAG_SWAPPED ; 
 scalar_t__ tt_unbound ; 
 scalar_t__ tt_unpopulated ; 
 scalar_t__ ttm_check_under_lowerlimit (struct ttm_mem_global*,unsigned int,struct ttm_operation_ctx*) ; 
 int ttm_get_pages (int /*<<< orphan*/ *,unsigned int,int,int /*<<< orphan*/ ) ; 
 int ttm_mem_global_alloc_page (struct ttm_mem_global*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ttm_operation_ctx*) ; 
 int /*<<< orphan*/  ttm_pool_unpopulate (struct ttm_tt*) ; 
 int /*<<< orphan*/  ttm_pool_unpopulate_helper (struct ttm_tt*,unsigned int) ; 
 int ttm_tt_swapin (struct ttm_tt*) ; 
 scalar_t__ unlikely (int) ; 

int ttm_pool_populate(struct ttm_tt *ttm, struct ttm_operation_ctx *ctx)
{
	struct ttm_mem_global *mem_glob = ttm->bdev->glob->mem_glob;
	unsigned i;
	int ret;

	if (ttm->state != tt_unpopulated)
		return 0;

	if (ttm_check_under_lowerlimit(mem_glob, ttm->num_pages, ctx))
		return -ENOMEM;

	ret = ttm_get_pages(ttm->pages, ttm->num_pages, ttm->page_flags,
			    ttm->caching_state);
	if (unlikely(ret != 0)) {
		ttm_pool_unpopulate_helper(ttm, 0);
		return ret;
	}

	for (i = 0; i < ttm->num_pages; ++i) {
		ret = ttm_mem_global_alloc_page(mem_glob, ttm->pages[i],
						PAGE_SIZE, ctx);
		if (unlikely(ret != 0)) {
			ttm_pool_unpopulate_helper(ttm, i);
			return -ENOMEM;
		}
	}

	if (unlikely(ttm->page_flags & TTM_PAGE_FLAG_SWAPPED)) {
		ret = ttm_tt_swapin(ttm);
		if (unlikely(ret != 0)) {
			ttm_pool_unpopulate(ttm);
			return ret;
		}
	}

	ttm->state = tt_unbound;
	return 0;
}