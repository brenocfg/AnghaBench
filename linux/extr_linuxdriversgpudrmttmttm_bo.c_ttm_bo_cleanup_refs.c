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
struct reservation_object {int dummy; } ;
struct ttm_buffer_object {struct reservation_object* resv; int /*<<< orphan*/  list_kref; int /*<<< orphan*/  ddestroy; struct reservation_object ttm_resv; TYPE_1__* bdev; } ;
struct ttm_bo_global {int /*<<< orphan*/  lru_lock; } ;
struct TYPE_2__ {struct ttm_bo_global* glob; } ;

/* Variables and functions */
 int EBUSY ; 
 int HZ ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ reservation_object_test_signaled_rcu (struct reservation_object*,int) ; 
 int /*<<< orphan*/  reservation_object_trylock (struct reservation_object*) ; 
 int /*<<< orphan*/  reservation_object_unlock (struct reservation_object*) ; 
 long reservation_object_wait_timeout_rcu (struct reservation_object*,int,int,int) ; 
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
	struct reservation_object *resv;
	int ret;

	if (unlikely(list_empty(&bo->ddestroy)))
		resv = bo->resv;
	else
		resv = &bo->ttm_resv;

	if (reservation_object_test_signaled_rcu(resv, true))
		ret = 0;
	else
		ret = -EBUSY;

	if (ret && !no_wait_gpu) {
		long lret;

		if (unlock_resv)
			reservation_object_unlock(bo->resv);
		spin_unlock(&glob->lru_lock);

		lret = reservation_object_wait_timeout_rcu(resv, true,
							   interruptible,
							   30 * HZ);

		if (lret < 0)
			return lret;
		else if (lret == 0)
			return -EBUSY;

		spin_lock(&glob->lru_lock);
		if (unlock_resv && !reservation_object_trylock(bo->resv)) {
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
			reservation_object_unlock(bo->resv);
		spin_unlock(&glob->lru_lock);
		return ret;
	}

	ttm_bo_del_from_lru(bo);
	list_del_init(&bo->ddestroy);
	kref_put(&bo->list_kref, ttm_bo_ref_bug);

	spin_unlock(&glob->lru_lock);
	ttm_bo_cleanup_memtype_use(bo);

	if (unlock_resv)
		reservation_object_unlock(bo->resv);

	return 0;
}