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
struct r1conf {int array_frozen; int /*<<< orphan*/  resync_lock; int /*<<< orphan*/  wait_barrier; int /*<<< orphan*/  mddev; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_pending_writes (struct r1conf*) ; 
 int get_unqueued_pending (struct r1conf*) ; 
 int /*<<< orphan*/  raid1_log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_lock_irq_cmd (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void freeze_array(struct r1conf *conf, int extra)
{
	/* Stop sync I/O and normal I/O and wait for everything to
	 * go quiet.
	 * This is called in two situations:
	 * 1) management command handlers (reshape, remove disk, quiesce).
	 * 2) one normal I/O request failed.

	 * After array_frozen is set to 1, new sync IO will be blocked at
	 * raise_barrier(), and new normal I/O will blocked at _wait_barrier()
	 * or wait_read_barrier(). The flying I/Os will either complete or be
	 * queued. When everything goes quite, there are only queued I/Os left.

	 * Every flying I/O contributes to a conf->nr_pending[idx], idx is the
	 * barrier bucket index which this I/O request hits. When all sync and
	 * normal I/O are queued, sum of all conf->nr_pending[] will match sum
	 * of all conf->nr_queued[]. But normal I/O failure is an exception,
	 * in handle_read_error(), we may call freeze_array() before trying to
	 * fix the read error. In this case, the error read I/O is not queued,
	 * so get_unqueued_pending() == 1.
	 *
	 * Therefore before this function returns, we need to wait until
	 * get_unqueued_pendings(conf) gets equal to extra. For
	 * normal I/O context, extra is 1, in rested situations extra is 0.
	 */
	spin_lock_irq(&conf->resync_lock);
	conf->array_frozen = 1;
	raid1_log(conf->mddev, "wait freeze");
	wait_event_lock_irq_cmd(
		conf->wait_barrier,
		get_unqueued_pending(conf) == extra,
		conf->resync_lock,
		flush_pending_writes(conf));
	spin_unlock_irq(&conf->resync_lock);
}