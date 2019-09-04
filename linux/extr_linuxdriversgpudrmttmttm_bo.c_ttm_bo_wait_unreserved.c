#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ttm_buffer_object {int /*<<< orphan*/  wu_mutex; TYPE_1__* resv; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINTR ; 
 int ERESTARTSYS ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int reservation_object_lock_interruptible (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reservation_object_unlock (TYPE_1__*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  ww_mutex_is_locked (int /*<<< orphan*/ *) ; 

int ttm_bo_wait_unreserved(struct ttm_buffer_object *bo)
{
	int ret;

	/*
	 * In the absense of a wait_unlocked API,
	 * Use the bo::wu_mutex to avoid triggering livelocks due to
	 * concurrent use of this function. Note that this use of
	 * bo::wu_mutex can go away if we change locking order to
	 * mmap_sem -> bo::reserve.
	 */
	ret = mutex_lock_interruptible(&bo->wu_mutex);
	if (unlikely(ret != 0))
		return -ERESTARTSYS;
	if (!ww_mutex_is_locked(&bo->resv->lock))
		goto out_unlock;
	ret = reservation_object_lock_interruptible(bo->resv, NULL);
	if (ret == -EINTR)
		ret = -ERESTARTSYS;
	if (unlikely(ret != 0))
		goto out_unlock;
	reservation_object_unlock(bo->resv);

out_unlock:
	mutex_unlock(&bo->wu_mutex);
	return ret;
}