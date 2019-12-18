#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * resv; int /*<<< orphan*/  _resv; int /*<<< orphan*/  vma_node; } ;
struct TYPE_5__ {int /*<<< orphan*/  placement; } ;
struct ttm_buffer_object {TYPE_4__ base; scalar_t__ acc_size; int /*<<< orphan*/ * destroy; int /*<<< orphan*/  kref; int /*<<< orphan*/  list_kref; int /*<<< orphan*/  cpu_writers; int /*<<< orphan*/ * moving; int /*<<< orphan*/  wu_mutex; int /*<<< orphan*/  io_reserve_lru; int /*<<< orphan*/  swap; int /*<<< orphan*/  lru; int /*<<< orphan*/  ddestroy; TYPE_3__* bdev; TYPE_1__ mem; } ;
struct ttm_transfer_obj {struct ttm_buffer_object base; struct ttm_buffer_object* bo; } ;
struct TYPE_7__ {TYPE_2__* glob; } ;
struct TYPE_6__ {int /*<<< orphan*/  bo_count; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TTM_PL_FLAG_NO_EVICT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_resv_init (int /*<<< orphan*/ *) ; 
 int dma_resv_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_vma_node_reset (int /*<<< orphan*/ *) ; 
 struct ttm_transfer_obj* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_get (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  ttm_transfered_destroy ; 

__attribute__((used)) static int ttm_buffer_object_transfer(struct ttm_buffer_object *bo,
				      struct ttm_buffer_object **new_obj)
{
	struct ttm_transfer_obj *fbo;
	int ret;

	fbo = kmalloc(sizeof(*fbo), GFP_KERNEL);
	if (!fbo)
		return -ENOMEM;

	fbo->base = *bo;
	fbo->base.mem.placement |= TTM_PL_FLAG_NO_EVICT;

	ttm_bo_get(bo);
	fbo->bo = bo;

	/**
	 * Fix up members that we shouldn't copy directly:
	 * TODO: Explicit member copy would probably be better here.
	 */

	atomic_inc(&bo->bdev->glob->bo_count);
	INIT_LIST_HEAD(&fbo->base.ddestroy);
	INIT_LIST_HEAD(&fbo->base.lru);
	INIT_LIST_HEAD(&fbo->base.swap);
	INIT_LIST_HEAD(&fbo->base.io_reserve_lru);
	mutex_init(&fbo->base.wu_mutex);
	fbo->base.moving = NULL;
	drm_vma_node_reset(&fbo->base.base.vma_node);
	atomic_set(&fbo->base.cpu_writers, 0);

	kref_init(&fbo->base.list_kref);
	kref_init(&fbo->base.kref);
	fbo->base.destroy = &ttm_transfered_destroy;
	fbo->base.acc_size = 0;
	fbo->base.base.resv = &fbo->base.base._resv;
	dma_resv_init(fbo->base.base.resv);
	ret = dma_resv_trylock(fbo->base.base.resv);
	WARN_ON(!ret);

	*new_obj = &fbo->base;
	return 0;
}