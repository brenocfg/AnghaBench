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
struct dma_resv {int dummy; } ;
struct TYPE_4__ {struct dma_resv* resv; struct dma_resv _resv; } ;
struct ttm_buffer_object {TYPE_2__ base; int /*<<< orphan*/  list_kref; int /*<<< orphan*/  ddestroy; TYPE_1__* bdev; } ;
struct ttm_bo_global {int /*<<< orphan*/  lru_lock; } ;
struct TYPE_3__ {struct ttm_bo_global* glob; } ;

/* Variables and functions */
 int EBUSY ; 
 int HZ ; 
 scalar_t__ dma_resv_test_signaled_rcu (struct dma_resv*,int) ; 
 int /*<<< orphan*/  dma_resv_trylock (struct dma_resv*) ; 
 int /*<<< orphan*/  dma_resv_unlock (struct dma_resv*) ; 
 long dma_resv_wait_timeout_rcu (struct dma_resv*,int,int,int) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_cleanup_memtype_use (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  ttm_bo_del_from_lru (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  ttm_bo_ref_bug ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ttm_bo_cleanup_refs(struct ttm_buffer_object *bo,
			       bool interruptible, bool no_wait_gpu,
			       bool unlock_resv)
{
	struct ttm_bo_global *glob = bo->bdev->glob;
	struct dma_resv *resv;
	int ret;

	if (unlikely(list_empty(&bo->ddestroy)))
		resv = bo->base.resv;
	else
		resv = &bo->base._resv;

	if (dma_resv_test_signaled_rcu(resv, true))
		ret = 0;
	else
		ret = -EBUSY;

	if (ret && !no_wait_gpu) {
		long lret;

		if (unlock_resv)
			dma_resv_unlock(bo->base.resv);
		spin_unlock(&glob->lru_lock);

		lret = dma_resv_wait_timeout_rcu(resv, true,
							   interruptible,
							   30 * HZ);

		if (lret < 0)
			return lret;
		else if (lret == 0)
			return -EBUSY;

		spin_lock(&glob->lru_lock);
		if (unlock_resv && !dma_resv_trylock(bo->base.resv)) {
			/*
			 * We raced, and lost, someone else holds the reservation now,
			 * and is probably busy in ttm_bo_cleanup_memtype_use.
			 *
			 * Even if it's not the case, because we finished waiting any
			 * delayed destruction would succeed, so just return success
			 * here.
			 */
			spin_unlock(&glob->lru_lock);
			return 0;
		}
		ret = 0;
	}

	if (ret || unlikely(list_empty(&bo->ddestroy))) {
		if (unlock_resv)
			dma_resv_unlock(bo->base.resv);
		spin_unlock(&glob->lru_lock);
		return ret;
	}

	ttm_bo_del_from_lru(bo);
	list_del_init(&bo->ddestroy);
	kref_put(&bo->list_kref, ttm_bo_ref_bug);

	spin_unlock(&glob->lru_lock);
	ttm_bo_cleanup_memtype_use(bo);

	if (unlock_resv)
		dma_resv_unlock(bo->base.resv);

	return 0;
}