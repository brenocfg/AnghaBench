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
struct TYPE_2__ {int /*<<< orphan*/  resv; } ;
struct ttm_buffer_object {int /*<<< orphan*/  wu_mutex; TYPE_1__ base; } ;

/* Variables and functions */
 int EINTR ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  dma_resv_is_locked (int /*<<< orphan*/ ) ; 
 int dma_resv_lock_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_resv_unlock (int /*<<< orphan*/ ) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

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
	if (!dma_resv_is_locked(bo->base.resv))
		goto out_unlock;
	ret = dma_resv_lock_interruptible(bo->base.resv, NULL);
	if (ret == -EINTR)
		ret = -ERESTARTSYS;
	if (unlikely(ret != 0))
		goto out_unlock;
	dma_resv_unlock(bo->base.resv);

out_unlock:
	mutex_unlock(&bo->wu_mutex);
	return ret;
}