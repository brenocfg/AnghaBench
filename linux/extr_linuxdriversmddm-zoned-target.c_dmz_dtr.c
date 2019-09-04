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
struct dmz_target {int /*<<< orphan*/  chunk_lock; int /*<<< orphan*/  bio_set; int /*<<< orphan*/  metadata; int /*<<< orphan*/  flush_wq; int /*<<< orphan*/  flush_work; int /*<<< orphan*/  reclaim; int /*<<< orphan*/  chunk_wq; } ;
struct dm_target {struct dmz_target* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  bioset_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmz_dtr_metadata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmz_dtr_reclaim (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmz_flush_metadata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmz_put_zoned_device (struct dm_target*) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct dmz_target*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dmz_dtr(struct dm_target *ti)
{
	struct dmz_target *dmz = ti->private;

	flush_workqueue(dmz->chunk_wq);
	destroy_workqueue(dmz->chunk_wq);

	dmz_dtr_reclaim(dmz->reclaim);

	cancel_delayed_work_sync(&dmz->flush_work);
	destroy_workqueue(dmz->flush_wq);

	(void) dmz_flush_metadata(dmz->metadata);

	dmz_dtr_metadata(dmz->metadata);

	bioset_exit(&dmz->bio_set);

	dmz_put_zoned_device(ti);

	mutex_destroy(&dmz->chunk_lock);

	kfree(dmz);
}