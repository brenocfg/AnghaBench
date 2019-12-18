#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ttm_mem_type_manager {struct list_head* lru; } ;
struct ttm_lru_bulk_move_pos {TYPE_6__* last; TYPE_5__* first; } ;
struct ttm_lru_bulk_move {struct ttm_lru_bulk_move_pos* swap; struct ttm_lru_bulk_move_pos* vram; struct ttm_lru_bulk_move_pos* tt; } ;
struct list_head {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  resv; } ;
struct TYPE_12__ {int /*<<< orphan*/  swap; TYPE_2__ base; int /*<<< orphan*/  lru; } ;
struct TYPE_7__ {int /*<<< orphan*/  resv; } ;
struct TYPE_11__ {int /*<<< orphan*/  swap; TYPE_4__* bdev; TYPE_1__ base; int /*<<< orphan*/  lru; } ;
struct TYPE_10__ {TYPE_3__* glob; struct ttm_mem_type_manager* man; } ;
struct TYPE_9__ {struct list_head* swap_lru; } ;

/* Variables and functions */
 unsigned int TTM_MAX_BO_PRIORITY ; 
 size_t TTM_PL_TT ; 
 size_t TTM_PL_VRAM ; 
 int /*<<< orphan*/  dma_resv_assert_held (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_bulk_move_tail (struct list_head*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void ttm_bo_bulk_move_lru_tail(struct ttm_lru_bulk_move *bulk)
{
	unsigned i;

	for (i = 0; i < TTM_MAX_BO_PRIORITY; ++i) {
		struct ttm_lru_bulk_move_pos *pos = &bulk->tt[i];
		struct ttm_mem_type_manager *man;

		if (!pos->first)
			continue;

		dma_resv_assert_held(pos->first->base.resv);
		dma_resv_assert_held(pos->last->base.resv);

		man = &pos->first->bdev->man[TTM_PL_TT];
		list_bulk_move_tail(&man->lru[i], &pos->first->lru,
				    &pos->last->lru);
	}

	for (i = 0; i < TTM_MAX_BO_PRIORITY; ++i) {
		struct ttm_lru_bulk_move_pos *pos = &bulk->vram[i];
		struct ttm_mem_type_manager *man;

		if (!pos->first)
			continue;

		dma_resv_assert_held(pos->first->base.resv);
		dma_resv_assert_held(pos->last->base.resv);

		man = &pos->first->bdev->man[TTM_PL_VRAM];
		list_bulk_move_tail(&man->lru[i], &pos->first->lru,
				    &pos->last->lru);
	}

	for (i = 0; i < TTM_MAX_BO_PRIORITY; ++i) {
		struct ttm_lru_bulk_move_pos *pos = &bulk->swap[i];
		struct list_head *lru;

		if (!pos->first)
			continue;

		dma_resv_assert_held(pos->first->base.resv);
		dma_resv_assert_held(pos->last->base.resv);

		lru = &pos->first->bdev->glob->swap_lru[i];
		list_bulk_move_tail(lru, &pos->first->swap, &pos->last->swap);
	}
}