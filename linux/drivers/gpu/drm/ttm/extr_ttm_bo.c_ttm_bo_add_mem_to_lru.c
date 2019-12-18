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
struct ttm_mem_type_manager {int flags; int /*<<< orphan*/ * lru; } ;
struct ttm_mem_reg {int placement; size_t mem_type; } ;
struct TYPE_4__ {int /*<<< orphan*/  resv; } ;
struct ttm_buffer_object {size_t priority; int /*<<< orphan*/  list_kref; int /*<<< orphan*/  swap; TYPE_2__* ttm; int /*<<< orphan*/  lru; TYPE_1__ base; struct ttm_bo_device* bdev; } ;
struct ttm_bo_device {TYPE_3__* glob; struct ttm_mem_type_manager* man; } ;
struct TYPE_6__ {int /*<<< orphan*/ * swap_lru; } ;
struct TYPE_5__ {int page_flags; } ;

/* Variables and functions */
 int TTM_MEMTYPE_FLAG_FIXED ; 
 int TTM_PAGE_FLAG_SG ; 
 int TTM_PAGE_FLAG_SWAPPED ; 
 int TTM_PL_FLAG_NO_EVICT ; 
 int /*<<< orphan*/  dma_resv_assert_held (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ttm_bo_add_mem_to_lru(struct ttm_buffer_object *bo,
				  struct ttm_mem_reg *mem)
{
	struct ttm_bo_device *bdev = bo->bdev;
	struct ttm_mem_type_manager *man;

	dma_resv_assert_held(bo->base.resv);

	if (!list_empty(&bo->lru))
		return;

	if (mem->placement & TTM_PL_FLAG_NO_EVICT)
		return;

	man = &bdev->man[mem->mem_type];
	list_add_tail(&bo->lru, &man->lru[bo->priority]);
	kref_get(&bo->list_kref);

	if (!(man->flags & TTM_MEMTYPE_FLAG_FIXED) && bo->ttm &&
	    !(bo->ttm->page_flags & (TTM_PAGE_FLAG_SG |
				     TTM_PAGE_FLAG_SWAPPED))) {
		list_add_tail(&bo->swap, &bdev->glob->swap_lru[bo->priority]);
		kref_get(&bo->list_kref);
	}
}