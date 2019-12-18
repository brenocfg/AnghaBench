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
struct queue_limits {int /*<<< orphan*/  max_discard_sectors; int /*<<< orphan*/  discard_granularity; } ;
struct dm_target {struct dm_snapshot* private; } ;
struct dm_snapshot {TYPE_1__* store; scalar_t__ discard_zeroes_cow; } ;
struct TYPE_2__ {int /*<<< orphan*/  chunk_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  __find_snapshots_sharing_cow (struct dm_snapshot*,struct dm_snapshot**,struct dm_snapshot**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _origins_lock ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snapshot_io_hints(struct dm_target *ti, struct queue_limits *limits)
{
	struct dm_snapshot *snap = ti->private;

	if (snap->discard_zeroes_cow) {
		struct dm_snapshot *snap_src = NULL, *snap_dest = NULL;

		down_read(&_origins_lock);

		(void) __find_snapshots_sharing_cow(snap, &snap_src, &snap_dest, NULL);
		if (snap_src && snap_dest)
			snap = snap_src;

		/* All discards are split on chunk_size boundary */
		limits->discard_granularity = snap->store->chunk_size;
		limits->max_discard_sectors = snap->store->chunk_size;

		up_read(&_origins_lock);
	}
}