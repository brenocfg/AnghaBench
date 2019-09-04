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
struct TYPE_2__ {int /*<<< orphan*/  mem_type; } ;
struct ttm_buffer_object {int /*<<< orphan*/ * ttm; TYPE_1__ mem; int /*<<< orphan*/  resv; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTM_PL_SYSTEM ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int reservation_object_copy_fences (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
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

	ret = reservation_object_copy_fences(ghost->resv, bo->resv);
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