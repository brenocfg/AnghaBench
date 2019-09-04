#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ttm_object_file {int dummy; } ;
struct ttm_lock {struct ttm_object_file* vt_holder; int /*<<< orphan*/  base; int /*<<< orphan*/  queue; int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTM_VT_LOCK_PENDING ; 
 int /*<<< orphan*/  __ttm_vt_lock (struct ttm_lock*) ; 
 int /*<<< orphan*/  __ttm_vt_unlock (struct ttm_lock*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int ttm_base_object_init (struct ttm_object_file*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_lock_type ; 
 int /*<<< orphan*/  ttm_vt_lock_remove ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

int ttm_vt_lock(struct ttm_lock *lock,
		bool interruptible,
		struct ttm_object_file *tfile)
{
	int ret = 0;

	if (interruptible) {
		ret = wait_event_interruptible(lock->queue,
					       __ttm_vt_lock(lock));
		if (unlikely(ret != 0)) {
			spin_lock(&lock->lock);
			lock->flags &= ~TTM_VT_LOCK_PENDING;
			wake_up_all(&lock->queue);
			spin_unlock(&lock->lock);
			return ret;
		}
	} else
		wait_event(lock->queue, __ttm_vt_lock(lock));

	/*
	 * Add a base-object, the destructor of which will
	 * make sure the lock is released if the client dies
	 * while holding it.
	 */

	ret = ttm_base_object_init(tfile, &lock->base, false,
				   ttm_lock_type, &ttm_vt_lock_remove, NULL);
	if (ret)
		(void)__ttm_vt_unlock(lock);
	else
		lock->vt_holder = tfile;

	return ret;
}