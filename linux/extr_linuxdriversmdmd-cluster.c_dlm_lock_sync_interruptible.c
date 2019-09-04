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
struct mddev {int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {scalar_t__ sb_status; int /*<<< orphan*/  sb_lkid; } ;
struct dlm_lock_resource {int sync_locking_done; int mode; TYPE_1__ lksb; int /*<<< orphan*/  name; int /*<<< orphan*/  ls; int /*<<< orphan*/  sync_locking; int /*<<< orphan*/  bast; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_LKF_CANCEL ; 
 int EPERM ; 
 int /*<<< orphan*/  MD_CLOSING ; 
 int dlm_lock (int /*<<< orphan*/ ,int,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dlm_lock_resource*,int /*<<< orphan*/ ) ; 
 int dlm_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,struct dlm_lock_resource*) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_ast ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dlm_lock_sync_interruptible(struct dlm_lock_resource *res, int mode,
				       struct mddev *mddev)
{
	int ret = 0;

	ret = dlm_lock(res->ls, mode, &res->lksb,
			res->flags, res->name, strlen(res->name),
			0, sync_ast, res, res->bast);
	if (ret)
		return ret;

	wait_event(res->sync_locking, res->sync_locking_done
				      || kthread_should_stop()
				      || test_bit(MD_CLOSING, &mddev->flags));
	if (!res->sync_locking_done) {
		/*
		 * the convert queue contains the lock request when request is
		 * interrupted, and sync_ast could still be run, so need to
		 * cancel the request and reset completion
		 */
		ret = dlm_unlock(res->ls, res->lksb.sb_lkid, DLM_LKF_CANCEL,
			&res->lksb, res);
		res->sync_locking_done = false;
		if (unlikely(ret != 0))
			pr_info("failed to cancel previous lock request "
				 "%s return %d\n", res->name, ret);
		return -EPERM;
	} else
		res->sync_locking_done = false;
	if (res->lksb.sb_status == 0)
		res->mode = mode;
	return res->lksb.sb_status;
}