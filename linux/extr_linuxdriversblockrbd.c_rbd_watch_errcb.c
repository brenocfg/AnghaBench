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
typedef  int /*<<< orphan*/  u64 ;
struct rbd_device {scalar_t__ watch_state; int /*<<< orphan*/  watch_mutex; int /*<<< orphan*/  watch_dwork; int /*<<< orphan*/  task_wq; int /*<<< orphan*/  lock_rwsem; } ;

/* Variables and functions */
 scalar_t__ RBD_WATCH_STATE_ERROR ; 
 scalar_t__ RBD_WATCH_STATE_REGISTERED ; 
 int /*<<< orphan*/  __rbd_unregister_watch (struct rbd_device*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rbd_empty_cid ; 
 int /*<<< orphan*/  rbd_set_owner_cid (struct rbd_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbd_warn (struct rbd_device*,char*,int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rbd_watch_errcb(void *arg, u64 cookie, int err)
{
	struct rbd_device *rbd_dev = arg;

	rbd_warn(rbd_dev, "encountered watch error: %d", err);

	down_write(&rbd_dev->lock_rwsem);
	rbd_set_owner_cid(rbd_dev, &rbd_empty_cid);
	up_write(&rbd_dev->lock_rwsem);

	mutex_lock(&rbd_dev->watch_mutex);
	if (rbd_dev->watch_state == RBD_WATCH_STATE_REGISTERED) {
		__rbd_unregister_watch(rbd_dev);
		rbd_dev->watch_state = RBD_WATCH_STATE_ERROR;

		queue_delayed_work(rbd_dev->task_wq, &rbd_dev->watch_dwork, 0);
	}
	mutex_unlock(&rbd_dev->watch_mutex);
}