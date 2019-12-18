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
struct dm_snapshot {TYPE_3__* ti; TYPE_2__* store; } ;
struct TYPE_6__ {char* error; } ;
struct TYPE_5__ {TYPE_1__* type; } ;
struct TYPE_4__ {int /*<<< orphan*/  commit_merge; int /*<<< orphan*/  prepare_merge; } ;

/* Variables and functions */
 int EINVAL ; 
 int __find_snapshots_sharing_cow (struct dm_snapshot*,struct dm_snapshot**,struct dm_snapshot**,struct dm_snapshot**) ; 
 int /*<<< orphan*/  dm_target_is_snapshot_merge (TYPE_3__*) ; 

__attribute__((used)) static int __validate_exception_handover(struct dm_snapshot *snap)
{
	struct dm_snapshot *snap_src = NULL, *snap_dest = NULL;
	struct dm_snapshot *snap_merge = NULL;

	/* Does snapshot need exceptions handed over to it? */
	if ((__find_snapshots_sharing_cow(snap, &snap_src, &snap_dest,
					  &snap_merge) == 2) ||
	    snap_dest) {
		snap->ti->error = "Snapshot cow pairing for exception "
				  "table handover failed";
		return -EINVAL;
	}

	/*
	 * If no snap_src was found, snap cannot become a handover
	 * destination.
	 */
	if (!snap_src)
		return 0;

	/*
	 * Non-snapshot-merge handover?
	 */
	if (!dm_target_is_snapshot_merge(snap->ti))
		return 1;

	/*
	 * Do not allow more than one merging snapshot.
	 */
	if (snap_merge) {
		snap->ti->error = "A snapshot is already merging.";
		return -EINVAL;
	}

	if (!snap_src->store->type->prepare_merge ||
	    !snap_src->store->type->commit_merge) {
		snap->ti->error = "Snapshot exception store does not "
				  "support snapshot-merge.";
		return -EINVAL;
	}

	return 1;
}