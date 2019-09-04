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
struct TYPE_2__ {int placement; } ;
struct ttm_buffer_object {int /*<<< orphan*/  ddestroy; int /*<<< orphan*/  list_kref; int /*<<< orphan*/  ttm_resv; int /*<<< orphan*/ * resv; TYPE_1__ mem; struct ttm_bo_device* bdev; } ;
struct ttm_bo_global {int /*<<< orphan*/  lru_lock; } ;
struct ttm_bo_device {int /*<<< orphan*/  wq; int /*<<< orphan*/  ddestroy; struct ttm_bo_global* glob; } ;

/* Variables and functions */
 int EBUSY ; 
 int HZ ; 
 int TTM_PL_FLAG_NO_EVICT ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ reservation_object_test_signaled_rcu (int /*<<< orphan*/ *,int) ; 
 scalar_t__ reservation_object_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reservation_object_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reservation_object_wait_timeout_rcu (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_add_to_lru (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  ttm_bo_cleanup_memtype_use (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  ttm_bo_del_from_lru (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  ttm_bo_flush_all_fences (struct ttm_buffer_object*) ; 
 int ttm_bo_individualize_resv (struct ttm_buffer_object*) ; 

__attribute__((used)) static void ttm_bo_cleanup_refs_or_queue(struct ttm_buffer_object *bo)
{
	struct ttm_bo_device *bdev = bo->bdev;
	struct ttm_bo_global *glob = bdev->glob;
	int ret;

	ret = ttm_bo_individualize_resv(bo);
	if (ret) {
		/* Last resort, if we fail to allocate memory for the
		 * fences block for the BO to become idle
		 */
		reservation_object_wait_timeout_rcu(bo->resv, true, false,
						    30 * HZ);
		spin_lock(&glob->lru_lock);
		goto error;
	}

	spin_lock(&glob->lru_lock);
	ret = reservation_object_trylock(bo->resv) ? 0 : -EBUSY;
	if (!ret) {
		if (reservation_object_test_signaled_rcu(&bo->ttm_resv, true)) {
			ttm_bo_del_from_lru(bo);
			spin_unlock(&glob->lru_lock);
			if (bo->resv != &bo->ttm_resv)
				reservation_object_unlock(&bo->ttm_resv);

			ttm_bo_cleanup_memtype_use(bo);
			reservation_object_unlock(bo->resv);
			return;
		}

		ttm_bo_flush_all_fences(bo);

		/*
		 * Make NO_EVICT bos immediately available to
		 * shrinkers, now that they are queued for
		 * destruction.
		 */
		if (bo->mem.placement & TTM_PL_FLAG_NO_EVICT) {
			bo->mem.placement &= ~TTM_PL_FLAG_NO_EVICT;
			ttm_bo_add_to_lru(bo);
		}

		reservation_object_unlock(bo->resv);
	}
	if (bo->resv != &bo->ttm_resv)
		reservation_object_unlock(&bo->ttm_resv);

error:
	kref_get(&bo->list_kref);
	list_add_tail(&bo->ddestroy, &bdev->ddestroy);
	spin_unlock(&glob->lru_lock);

	schedule_delayed_work(&bdev->wq,
			      ((HZ / 100) < 1) ? 1 : HZ / 100);
}