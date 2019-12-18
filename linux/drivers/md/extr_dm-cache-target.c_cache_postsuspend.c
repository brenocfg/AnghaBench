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
struct dm_target {struct cache* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  in_flight; } ;
struct cache {TYPE_1__ tracker; int /*<<< orphan*/  wq; int /*<<< orphan*/  waker; int /*<<< orphan*/  nr_io_migrations; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ CM_WRITE ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 scalar_t__ get_cache_mode (struct cache*) ; 
 int /*<<< orphan*/  prevent_background_work (struct cache*) ; 
 int /*<<< orphan*/  requeue_deferred_bios (struct cache*) ; 
 int /*<<< orphan*/  sync_metadata (struct cache*) ; 

__attribute__((used)) static void cache_postsuspend(struct dm_target *ti)
{
	struct cache *cache = ti->private;

	prevent_background_work(cache);
	BUG_ON(atomic_read(&cache->nr_io_migrations));

	cancel_delayed_work(&cache->waker);
	flush_workqueue(cache->wq);
	WARN_ON(cache->tracker.in_flight);

	/*
	 * If it's a flush suspend there won't be any deferred bios, so this
	 * call is harmless.
	 */
	requeue_deferred_bios(cache);

	if (get_cache_mode(cache) == CM_WRITE)
		(void) sync_metadata(cache);
}