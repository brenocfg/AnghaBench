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
typedef  int /*<<< orphan*/  uint32_t ;
struct ttm_placement {int dummy; } ;
struct ttm_operation_ctx {int dummy; } ;
struct ttm_mem_global {int dummy; } ;
struct TYPE_4__ {int io_reserved_vm; scalar_t__ io_reserved_count; } ;
struct TYPE_5__ {unsigned long size; unsigned long num_pages; int placement; TYPE_1__ bus; int /*<<< orphan*/  page_alignment; int /*<<< orphan*/ * mm_node; int /*<<< orphan*/  mem_type; } ;
struct reservation_object {int dummy; } ;
struct ttm_buffer_object {void (* destroy ) (struct ttm_buffer_object*) ;int type; unsigned long num_pages; size_t acc_size; TYPE_2__ mem; struct reservation_object* resv; int /*<<< orphan*/  vma_node; struct ttm_bo_device* bdev; struct reservation_object ttm_resv; struct sg_table* sg; int /*<<< orphan*/ * moving; int /*<<< orphan*/  wu_mutex; int /*<<< orphan*/  io_reserve_lru; int /*<<< orphan*/  swap; int /*<<< orphan*/  ddestroy; int /*<<< orphan*/  lru; int /*<<< orphan*/  cpu_writers; int /*<<< orphan*/  list_kref; int /*<<< orphan*/  kref; } ;
struct ttm_bo_device {TYPE_3__* glob; int /*<<< orphan*/  vma_manager; } ;
struct sg_table {int dummy; } ;
typedef  enum ttm_bo_type { ____Placeholder_ttm_bo_type } ttm_bo_type ;
struct TYPE_6__ {int /*<<< orphan*/  lru_lock; int /*<<< orphan*/  bo_count; struct ttm_mem_global* mem_glob; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PAGE_SIZE ; 
 int TTM_PL_FLAG_CACHED ; 
 int TTM_PL_FLAG_NO_EVICT ; 
 int TTM_PL_FLAG_SYSTEM ; 
 int /*<<< orphan*/  TTM_PL_SYSTEM ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_vma_node_reset (int /*<<< orphan*/ *) ; 
 int drm_vma_offset_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  kfree (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  reservation_object_assert_held (struct reservation_object*) ; 
 int /*<<< orphan*/  reservation_object_init (struct reservation_object*) ; 
 int reservation_object_trylock (struct reservation_object*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 void stub1 (struct ttm_buffer_object*) ; 
 void stub2 (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  ttm_bo_add_to_lru (struct ttm_buffer_object*) ; 
 void ttm_bo_default_destroy (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  ttm_bo_put (struct ttm_buffer_object*) ; 
 scalar_t__ ttm_bo_type_device ; 
 scalar_t__ ttm_bo_type_sg ; 
 int /*<<< orphan*/  ttm_bo_unreserve (struct ttm_buffer_object*) ; 
 int ttm_bo_validate (struct ttm_buffer_object*,struct ttm_placement*,struct ttm_operation_ctx*) ; 
 int ttm_mem_global_alloc (struct ttm_mem_global*,size_t,struct ttm_operation_ctx*) ; 
 int /*<<< orphan*/  ttm_mem_global_free (struct ttm_mem_global*,size_t) ; 
 scalar_t__ unlikely (int) ; 

int ttm_bo_init_reserved(struct ttm_bo_device *bdev,
			 struct ttm_buffer_object *bo,
			 unsigned long size,
			 enum ttm_bo_type type,
			 struct ttm_placement *placement,
			 uint32_t page_alignment,
			 struct ttm_operation_ctx *ctx,
			 size_t acc_size,
			 struct sg_table *sg,
			 struct reservation_object *resv,
			 void (*destroy) (struct ttm_buffer_object *))
{
	int ret = 0;
	unsigned long num_pages;
	struct ttm_mem_global *mem_glob = bdev->glob->mem_glob;
	bool locked;

	ret = ttm_mem_global_alloc(mem_glob, acc_size, ctx);
	if (ret) {
		pr_err("Out of kernel memory\n");
		if (destroy)
			(*destroy)(bo);
		else
			kfree(bo);
		return -ENOMEM;
	}

	num_pages = (size + PAGE_SIZE - 1) >> PAGE_SHIFT;
	if (num_pages == 0) {
		pr_err("Illegal buffer object size\n");
		if (destroy)
			(*destroy)(bo);
		else
			kfree(bo);
		ttm_mem_global_free(mem_glob, acc_size);
		return -EINVAL;
	}
	bo->destroy = destroy ? destroy : ttm_bo_default_destroy;

	kref_init(&bo->kref);
	kref_init(&bo->list_kref);
	atomic_set(&bo->cpu_writers, 0);
	INIT_LIST_HEAD(&bo->lru);
	INIT_LIST_HEAD(&bo->ddestroy);
	INIT_LIST_HEAD(&bo->swap);
	INIT_LIST_HEAD(&bo->io_reserve_lru);
	mutex_init(&bo->wu_mutex);
	bo->bdev = bdev;
	bo->type = type;
	bo->num_pages = num_pages;
	bo->mem.size = num_pages << PAGE_SHIFT;
	bo->mem.mem_type = TTM_PL_SYSTEM;
	bo->mem.num_pages = bo->num_pages;
	bo->mem.mm_node = NULL;
	bo->mem.page_alignment = page_alignment;
	bo->mem.bus.io_reserved_vm = false;
	bo->mem.bus.io_reserved_count = 0;
	bo->moving = NULL;
	bo->mem.placement = (TTM_PL_FLAG_SYSTEM | TTM_PL_FLAG_CACHED);
	bo->acc_size = acc_size;
	bo->sg = sg;
	if (resv) {
		bo->resv = resv;
		reservation_object_assert_held(bo->resv);
	} else {
		bo->resv = &bo->ttm_resv;
	}
	reservation_object_init(&bo->ttm_resv);
	atomic_inc(&bo->bdev->glob->bo_count);
	drm_vma_node_reset(&bo->vma_node);

	/*
	 * For ttm_bo_type_device buffers, allocate
	 * address space from the device.
	 */
	if (bo->type == ttm_bo_type_device ||
	    bo->type == ttm_bo_type_sg)
		ret = drm_vma_offset_add(&bdev->vma_manager, &bo->vma_node,
					 bo->mem.num_pages);

	/* passed reservation objects should already be locked,
	 * since otherwise lockdep will be angered in radeon.
	 */
	if (!resv) {
		locked = reservation_object_trylock(bo->resv);
		WARN_ON(!locked);
	}

	if (likely(!ret))
		ret = ttm_bo_validate(bo, placement, ctx);

	if (unlikely(ret)) {
		if (!resv)
			ttm_bo_unreserve(bo);

		ttm_bo_put(bo);
		return ret;
	}

	if (resv && !(bo->mem.placement & TTM_PL_FLAG_NO_EVICT)) {
		spin_lock(&bdev->glob->lru_lock);
		ttm_bo_add_to_lru(bo);
		spin_unlock(&bdev->glob->lru_lock);
	}

	return ret;
}