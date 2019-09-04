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
typedef  int /*<<< orphan*/  uint32_t ;
struct ttm_tt {int /*<<< orphan*/  sg; int /*<<< orphan*/ * swap_storage; int /*<<< orphan*/  state; int /*<<< orphan*/  page_flags; int /*<<< orphan*/  caching_state; int /*<<< orphan*/  num_pages; int /*<<< orphan*/  bdev; } ;
struct ttm_buffer_object {int /*<<< orphan*/  sg; int /*<<< orphan*/  num_pages; int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  tt_cached ; 
 int /*<<< orphan*/  tt_unpopulated ; 

void ttm_tt_init_fields(struct ttm_tt *ttm, struct ttm_buffer_object *bo,
			uint32_t page_flags)
{
	ttm->bdev = bo->bdev;
	ttm->num_pages = bo->num_pages;
	ttm->caching_state = tt_cached;
	ttm->page_flags = page_flags;
	ttm->state = tt_unpopulated;
	ttm->swap_storage = NULL;
	ttm->sg = bo->sg;
}