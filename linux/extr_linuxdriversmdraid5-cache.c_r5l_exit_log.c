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
struct r5l_log {int /*<<< orphan*/  io_kc; int /*<<< orphan*/  io_pool; int /*<<< orphan*/  bs; int /*<<< orphan*/  meta_pool; int /*<<< orphan*/  reclaim_thread; int /*<<< orphan*/  disable_writeback_work; } ;
struct r5conf {TYPE_1__* mddev; struct r5l_log* log; } ;
struct TYPE_2__ {int /*<<< orphan*/  sb_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  bioset_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct r5l_log*) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_unregister_thread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mempool_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void r5l_exit_log(struct r5conf *conf)
{
	struct r5l_log *log = conf->log;

	conf->log = NULL;
	synchronize_rcu();

	/* Ensure disable_writeback_work wakes up and exits */
	wake_up(&conf->mddev->sb_wait);
	flush_work(&log->disable_writeback_work);
	md_unregister_thread(&log->reclaim_thread);
	mempool_exit(&log->meta_pool);
	bioset_exit(&log->bs);
	mempool_exit(&log->io_pool);
	kmem_cache_destroy(log->io_kc);
	kfree(log);
}