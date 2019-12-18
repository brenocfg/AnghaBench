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
struct TYPE_4__ {int /*<<< orphan*/  mem_type; } ;
struct TYPE_3__ {int /*<<< orphan*/  resv; } ;
struct ttm_buffer_object {int /*<<< orphan*/ * ttm; TYPE_2__ mem; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTM_PL_SYSTEM ; 
 int dma_resv_copy_fences (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ttm_bo_put (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  ttm_bo_unreserve (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  ttm_bo_wait (struct ttm_buffer_object*,int,int) ; 
 int ttm_buffer_object_transfer (struct ttm_buffer_object*,struct ttm_buffer_object**) ; 

int ttm_bo_pipeline_gutting(struct ttm_buffer_object *bo)
{
	struct ttm_buffer_object *ghost;
	int ret;

	ret = ttm_buffer_object_transfer(bo, &ghost);
	if (ret)
		return ret;

	ret = dma_resv_copy_fences(ghost->base.resv, bo->base.resv);
	/* Last resort, wait for the BO to be idle when we are OOM */
	if (ret)
		ttm_bo_wait(bo, false, false);

	memset(&bo->mem, 0, sizeof(bo->mem));
	bo->mem.mem_type = TTM_PL_SYSTEM;
	bo->ttm = NULL;

	ttm_bo_unreserve(ghost);
	ttm_bo_put(ghost);

	return 0;
}