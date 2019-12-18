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

/* Variables and functions */
 scalar_t__ bcache_kobj ; 
 scalar_t__ bcache_major ; 
 scalar_t__ bcache_wq ; 
 int /*<<< orphan*/  bch_debug_exit () ; 
 scalar_t__ bch_journal_wq ; 
 int /*<<< orphan*/  bch_register_lock ; 
 int /*<<< orphan*/  bch_request_exit () ; 
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  kobject_put (scalar_t__) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reboot ; 
 int /*<<< orphan*/  unregister_blkdev (scalar_t__,char*) ; 
 int /*<<< orphan*/  unregister_reboot_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bcache_exit(void)
{
	bch_debug_exit();
	bch_request_exit();
	if (bcache_kobj)
		kobject_put(bcache_kobj);
	if (bcache_wq)
		destroy_workqueue(bcache_wq);
	if (bch_journal_wq)
		destroy_workqueue(bch_journal_wq);

	if (bcache_major)
		unregister_blkdev(bcache_major, "bcache");
	unregister_reboot_notifier(&reboot);
	mutex_destroy(&bch_register_lock);
}