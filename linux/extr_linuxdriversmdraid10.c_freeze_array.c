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
struct r10conf {scalar_t__ nr_queued; int /*<<< orphan*/  resync_lock; int /*<<< orphan*/  array_freeze_pending; int /*<<< orphan*/  nr_pending; int /*<<< orphan*/  wait_barrier; int /*<<< orphan*/  nr_waiting; int /*<<< orphan*/  barrier; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_pending_writes (struct r10conf*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_lock_irq_cmd (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void freeze_array(struct r10conf *conf, int extra)
{
	/* stop syncio and normal IO and wait for everything to
	 * go quiet.
	 * We increment barrier and nr_waiting, and then
	 * wait until nr_pending match nr_queued+extra
	 * This is called in the context of one normal IO request
	 * that has failed. Thus any sync request that might be pending
	 * will be blocked by nr_pending, and we need to wait for
	 * pending IO requests to complete or be queued for re-try.
	 * Thus the number queued (nr_queued) plus this request (extra)
	 * must match the number of pending IOs (nr_pending) before
	 * we continue.
	 */
	spin_lock_irq(&conf->resync_lock);
	conf->array_freeze_pending++;
	conf->barrier++;
	conf->nr_waiting++;
	wait_event_lock_irq_cmd(conf->wait_barrier,
				atomic_read(&conf->nr_pending) == conf->nr_queued+extra,
				conf->resync_lock,
				flush_pending_writes(conf));

	conf->array_freeze_pending--;
	spin_unlock_irq(&conf->resync_lock);
}