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
struct r5conf {int quiesce; int /*<<< orphan*/  wait_for_overlap; int /*<<< orphan*/  wait_for_quiescent; int /*<<< orphan*/  active_aligned_reads; int /*<<< orphan*/  active_stripes; } ;
struct mddev {struct r5conf* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_all_device_hash_locks_irq (struct r5conf*) ; 
 int /*<<< orphan*/  log_quiesce (struct r5conf*,int) ; 
 int /*<<< orphan*/  r5c_flush_cache (struct r5conf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_all_device_hash_locks_irq (struct r5conf*) ; 
 int /*<<< orphan*/  wait_event_cmd (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void raid5_quiesce(struct mddev *mddev, int quiesce)
{
	struct r5conf *conf = mddev->private;

	if (quiesce) {
		/* stop all writes */
		lock_all_device_hash_locks_irq(conf);
		/* '2' tells resync/reshape to pause so that all
		 * active stripes can drain
		 */
		r5c_flush_cache(conf, INT_MAX);
		conf->quiesce = 2;
		wait_event_cmd(conf->wait_for_quiescent,
				    atomic_read(&conf->active_stripes) == 0 &&
				    atomic_read(&conf->active_aligned_reads) == 0,
				    unlock_all_device_hash_locks_irq(conf),
				    lock_all_device_hash_locks_irq(conf));
		conf->quiesce = 1;
		unlock_all_device_hash_locks_irq(conf);
		/* allow reshape to continue */
		wake_up(&conf->wait_for_overlap);
	} else {
		/* re-enable writes */
		lock_all_device_hash_locks_irq(conf);
		conf->quiesce = 0;
		wake_up(&conf->wait_for_quiescent);
		wake_up(&conf->wait_for_overlap);
		unlock_all_device_hash_locks_irq(conf);
	}
	log_quiesce(conf, quiesce);
}