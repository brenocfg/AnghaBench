#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ttm_lru_bulk_move {int /*<<< orphan*/ * swap; int /*<<< orphan*/ * vram; int /*<<< orphan*/ * tt; } ;
struct TYPE_4__ {int placement; int mem_type; } ;
struct TYPE_6__ {int /*<<< orphan*/  resv; } ;
struct ttm_buffer_object {size_t priority; TYPE_2__* ttm; TYPE_1__ mem; TYPE_3__ base; } ;
struct TYPE_5__ {int page_flags; } ;

/* Variables and functions */
 int TTM_PAGE_FLAG_SG ; 
 int TTM_PAGE_FLAG_SWAPPED ; 
 int TTM_PL_FLAG_NO_EVICT ; 
#define  TTM_PL_TT 129 
#define  TTM_PL_VRAM 128 
 int /*<<< orphan*/  dma_resv_assert_held (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_bo_add_to_lru (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  ttm_bo_bulk_move_set_pos (int /*<<< orphan*/ *,struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  ttm_bo_del_from_lru (struct ttm_buffer_object*) ; 

void ttm_bo_move_to_lru_tail(struct ttm_buffer_object *bo,
			     struct ttm_lru_bulk_move *bulk)
{
	dma_resv_assert_held(bo->base.resv);

	ttm_bo_del_from_lru(bo);
	ttm_bo_add_to_lru(bo);

	if (bulk && !(bo->mem.placement & TTM_PL_FLAG_NO_EVICT)) {
		switch (bo->mem.mem_type) {
		case TTM_PL_TT:
			ttm_bo_bulk_move_set_pos(&bulk->tt[bo->priority], bo);
			break;

		case TTM_PL_VRAM:
			ttm_bo_bulk_move_set_pos(&bulk->vram[bo->priority], bo);
			break;
		}
		if (bo->ttm && !(bo->ttm->page_flags &
				 (TTM_PAGE_FLAG_SG | TTM_PAGE_FLAG_SWAPPED)))
			ttm_bo_bulk_move_set_pos(&bulk->swap[bo->priority], bo);
	}
}