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
struct bio_list {int dummy; } ;
struct mirror_set {int /*<<< orphan*/  kmirrord_wq; int /*<<< orphan*/  rh; int /*<<< orphan*/  lock; struct bio_list holds; int /*<<< orphan*/  suspend; } ;
struct dm_target {scalar_t__ private; } ;
struct dm_dirty_log {TYPE_1__* type; } ;
struct bio {int dummy; } ;
struct TYPE_2__ {scalar_t__ (* presuspend ) (struct dm_dirty_log*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DMWARN (char*) ; 
 int /*<<< orphan*/  _kmirrord_recovery_stopped ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bio_list_init (struct bio_list*) ; 
 struct bio* bio_list_pop (struct bio_list*) ; 
 struct dm_dirty_log* dm_rh_dirty_log (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_rh_recovery_in_flight (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_rh_stop_recovery (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hold_bio (struct mirror_set*,struct bio*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct dm_dirty_log*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mirror_presuspend(struct dm_target *ti)
{
	struct mirror_set *ms = (struct mirror_set *) ti->private;
	struct dm_dirty_log *log = dm_rh_dirty_log(ms->rh);

	struct bio_list holds;
	struct bio *bio;

	atomic_set(&ms->suspend, 1);

	/*
	 * Process bios in the hold list to start recovery waiting
	 * for bios in the hold list. After the process, no bio has
	 * a chance to be added in the hold list because ms->suspend
	 * is set.
	 */
	spin_lock_irq(&ms->lock);
	holds = ms->holds;
	bio_list_init(&ms->holds);
	spin_unlock_irq(&ms->lock);

	while ((bio = bio_list_pop(&holds)))
		hold_bio(ms, bio);

	/*
	 * We must finish up all the work that we've
	 * generated (i.e. recovery work).
	 */
	dm_rh_stop_recovery(ms->rh);

	wait_event(_kmirrord_recovery_stopped,
		   !dm_rh_recovery_in_flight(ms->rh));

	if (log->type->presuspend && log->type->presuspend(log))
		/* FIXME: need better error handling */
		DMWARN("log presuspend failed");

	/*
	 * Now that recovery is complete/stopped and the
	 * delayed bios are queued, we need to wait for
	 * the worker thread to complete.  This way,
	 * we know that all of our I/O has been pushed.
	 */
	flush_workqueue(ms->kmirrord_wq);
}