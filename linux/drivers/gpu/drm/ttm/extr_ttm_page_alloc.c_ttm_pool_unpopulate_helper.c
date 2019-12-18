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
struct ttm_tt {int /*<<< orphan*/  state; int /*<<< orphan*/  caching_state; int /*<<< orphan*/  page_flags; int /*<<< orphan*/  num_pages; int /*<<< orphan*/ * pages; TYPE_2__* bdev; } ;
struct ttm_mem_global {int dummy; } ;
struct TYPE_4__ {TYPE_1__* glob; } ;
struct TYPE_3__ {struct ttm_mem_global* mem_glob; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  tt_unpopulated ; 
 int /*<<< orphan*/  ttm_mem_global_free_page (struct ttm_mem_global*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_put_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ttm_pool_unpopulate_helper(struct ttm_tt *ttm, unsigned mem_count_update)
{
	struct ttm_mem_global *mem_glob = ttm->bdev->glob->mem_glob;
	unsigned i;

	if (mem_count_update == 0)
		goto put_pages;

	for (i = 0; i < mem_count_update; ++i) {
		if (!ttm->pages[i])
			continue;

		ttm_mem_global_free_page(mem_glob, ttm->pages[i], PAGE_SIZE);
	}

put_pages:
	ttm_put_pages(ttm->pages, ttm->num_pages, ttm->page_flags,
		      ttm->caching_state);
	ttm->state = tt_unpopulated;
}