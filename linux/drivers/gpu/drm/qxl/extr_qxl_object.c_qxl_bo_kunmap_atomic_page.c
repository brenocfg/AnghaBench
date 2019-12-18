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
struct ttm_mem_type_manager {int dummy; } ;
struct qxl_device {int dummy; } ;
struct TYPE_6__ {size_t mem_type; } ;
struct TYPE_4__ {TYPE_3__ mem; TYPE_2__* bdev; } ;
struct qxl_bo {TYPE_1__ tbo; } ;
struct TYPE_5__ {struct ttm_mem_type_manager* man; } ;

/* Variables and functions */
 size_t TTM_PL_PRIV ; 
 size_t TTM_PL_VRAM ; 
 int /*<<< orphan*/  io_mapping_unmap_atomic (void*) ; 
 int /*<<< orphan*/  qxl_bo_kunmap (struct qxl_bo*) ; 
 int /*<<< orphan*/  ttm_mem_io_free (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ttm_mem_io_lock (struct ttm_mem_type_manager*,int) ; 
 int /*<<< orphan*/  ttm_mem_io_unlock (struct ttm_mem_type_manager*) ; 

void qxl_bo_kunmap_atomic_page(struct qxl_device *qdev,
			       struct qxl_bo *bo, void *pmap)
{
	struct ttm_mem_type_manager *man = &bo->tbo.bdev->man[bo->tbo.mem.mem_type];

	if ((bo->tbo.mem.mem_type != TTM_PL_VRAM) &&
	    (bo->tbo.mem.mem_type != TTM_PL_PRIV))
		goto fallback;

	io_mapping_unmap_atomic(pmap);

	(void) ttm_mem_io_lock(man, false);
	ttm_mem_io_free(bo->tbo.bdev, &bo->tbo.mem);
	ttm_mem_io_unlock(man);
	return;
 fallback:
	qxl_bo_kunmap(bo);
}