#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mapped_device {int dummy; } ;
struct dm_target {int /*<<< orphan*/  table; struct dm_snapshot* private; } ;
struct dm_snapshot {int active; int /*<<< orphan*/  lock; int /*<<< orphan*/  state_bits; TYPE_3__* ti; TYPE_1__* origin; } ;
struct dm_origin {TYPE_2__* ti; } ;
struct TYPE_6__ {int /*<<< orphan*/  table; } ;
struct TYPE_5__ {int /*<<< orphan*/  table; } ;
struct TYPE_4__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RUNNING_MERGE ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int /*<<< orphan*/  __find_snapshots_sharing_cow (struct dm_snapshot*,struct dm_snapshot**,struct dm_snapshot**,struct dm_snapshot**) ; 
 int /*<<< orphan*/  __handover_exceptions (struct dm_snapshot*,struct dm_snapshot*) ; 
 struct dm_origin* __lookup_dm_origin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _origins_lock ; 
 scalar_t__ dm_hold (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_internal_resume_fast (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_internal_suspend_fast (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_put (struct mapped_device*) ; 
 struct mapped_device* dm_table_get_md (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reregister_snapshot (struct dm_snapshot*) ; 
 int /*<<< orphan*/  start_merge (struct dm_snapshot*) ; 
 int /*<<< orphan*/  stop_merge (struct dm_snapshot*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snapshot_resume(struct dm_target *ti)
{
	struct dm_snapshot *s = ti->private;
	struct dm_snapshot *snap_src = NULL, *snap_dest = NULL, *snap_merging = NULL;
	struct dm_origin *o;
	struct mapped_device *origin_md = NULL;
	bool must_restart_merging = false;

	down_read(&_origins_lock);

	o = __lookup_dm_origin(s->origin->bdev);
	if (o)
		origin_md = dm_table_get_md(o->ti->table);
	if (!origin_md) {
		(void) __find_snapshots_sharing_cow(s, NULL, NULL, &snap_merging);
		if (snap_merging)
			origin_md = dm_table_get_md(snap_merging->ti->table);
	}
	if (origin_md == dm_table_get_md(ti->table))
		origin_md = NULL;
	if (origin_md) {
		if (dm_hold(origin_md))
			origin_md = NULL;
	}

	up_read(&_origins_lock);

	if (origin_md) {
		dm_internal_suspend_fast(origin_md);
		if (snap_merging && test_bit(RUNNING_MERGE, &snap_merging->state_bits)) {
			must_restart_merging = true;
			stop_merge(snap_merging);
		}
	}

	down_read(&_origins_lock);

	(void) __find_snapshots_sharing_cow(s, &snap_src, &snap_dest, NULL);
	if (snap_src && snap_dest) {
		down_write(&snap_src->lock);
		down_write_nested(&snap_dest->lock, SINGLE_DEPTH_NESTING);
		__handover_exceptions(snap_src, snap_dest);
		up_write(&snap_dest->lock);
		up_write(&snap_src->lock);
	}

	up_read(&_origins_lock);

	if (origin_md) {
		if (must_restart_merging)
			start_merge(snap_merging);
		dm_internal_resume_fast(origin_md);
		dm_put(origin_md);
	}

	/* Now we have correct chunk size, reregister */
	reregister_snapshot(s);

	down_write(&s->lock);
	s->active = 1;
	up_write(&s->lock);
}