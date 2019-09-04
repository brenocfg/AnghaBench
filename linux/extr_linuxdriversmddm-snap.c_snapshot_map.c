#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct dm_target {struct dm_snapshot* private; } ;
struct dm_snapshot {int snapshot_overflowed; int /*<<< orphan*/  lock; TYPE_3__* origin; TYPE_4__* store; int /*<<< orphan*/  complete; int /*<<< orphan*/  valid; TYPE_1__* cow; } ;
struct dm_exception {int dummy; } ;
struct dm_snap_pending_exception {int started; int /*<<< orphan*/  snapshot_bios; struct dm_exception e; } ;
struct TYPE_6__ {int bi_size; int /*<<< orphan*/  bi_sector; } ;
struct bio {int bi_opf; TYPE_2__ bi_iter; } ;
typedef  int /*<<< orphan*/  chunk_t ;
struct TYPE_8__ {int chunk_size; scalar_t__ userspace_supports_overflow; } ;
struct TYPE_7__ {int /*<<< orphan*/  bdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 int DM_MAPIO_KILL ; 
 int DM_MAPIO_REMAPPED ; 
 int DM_MAPIO_SUBMITTED ; 
 int /*<<< orphan*/  ENOMEM ; 
 int REQ_PREFLUSH ; 
 int SECTOR_SHIFT ; 
 scalar_t__ WRITE ; 
 struct dm_snap_pending_exception* __find_pending_exception (struct dm_snapshot*,struct dm_snap_pending_exception*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __invalidate_snapshot (struct dm_snapshot*,int /*<<< orphan*/ ) ; 
 struct dm_snap_pending_exception* __lookup_pending_exception (struct dm_snapshot*,int /*<<< orphan*/ ) ; 
 struct dm_snap_pending_exception* alloc_pending_exception (struct dm_snapshot*) ; 
 scalar_t__ bio_data_dir (struct bio*) ; 
 int /*<<< orphan*/  bio_list_add (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 struct dm_exception* dm_lookup_exception (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_pending_exception (struct dm_snap_pending_exception*) ; 
 int /*<<< orphan*/  init_tracked_chunk (struct bio*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remap_exception (struct dm_snapshot*,struct dm_exception*,struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sector_to_chunk (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_copy (struct dm_snap_pending_exception*) ; 
 int /*<<< orphan*/  start_full_bio (struct dm_snap_pending_exception*,struct bio*) ; 
 int /*<<< orphan*/  track_chunk (struct dm_snapshot*,struct bio*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int snapshot_map(struct dm_target *ti, struct bio *bio)
{
	struct dm_exception *e;
	struct dm_snapshot *s = ti->private;
	int r = DM_MAPIO_REMAPPED;
	chunk_t chunk;
	struct dm_snap_pending_exception *pe = NULL;

	init_tracked_chunk(bio);

	if (bio->bi_opf & REQ_PREFLUSH) {
		bio_set_dev(bio, s->cow->bdev);
		return DM_MAPIO_REMAPPED;
	}

	chunk = sector_to_chunk(s->store, bio->bi_iter.bi_sector);

	/* Full snapshots are not usable */
	/* To get here the table must be live so s->active is always set. */
	if (!s->valid)
		return DM_MAPIO_KILL;

	mutex_lock(&s->lock);

	if (!s->valid || (unlikely(s->snapshot_overflowed) &&
	    bio_data_dir(bio) == WRITE)) {
		r = DM_MAPIO_KILL;
		goto out_unlock;
	}

	/* If the block is already remapped - use that, else remap it */
	e = dm_lookup_exception(&s->complete, chunk);
	if (e) {
		remap_exception(s, e, bio, chunk);
		goto out_unlock;
	}

	/*
	 * Write to snapshot - higher level takes care of RW/RO
	 * flags so we should only get this if we are
	 * writeable.
	 */
	if (bio_data_dir(bio) == WRITE) {
		pe = __lookup_pending_exception(s, chunk);
		if (!pe) {
			mutex_unlock(&s->lock);
			pe = alloc_pending_exception(s);
			mutex_lock(&s->lock);

			if (!s->valid || s->snapshot_overflowed) {
				free_pending_exception(pe);
				r = DM_MAPIO_KILL;
				goto out_unlock;
			}

			e = dm_lookup_exception(&s->complete, chunk);
			if (e) {
				free_pending_exception(pe);
				remap_exception(s, e, bio, chunk);
				goto out_unlock;
			}

			pe = __find_pending_exception(s, pe, chunk);
			if (!pe) {
				if (s->store->userspace_supports_overflow) {
					s->snapshot_overflowed = 1;
					DMERR("Snapshot overflowed: Unable to allocate exception.");
				} else
					__invalidate_snapshot(s, -ENOMEM);
				r = DM_MAPIO_KILL;
				goto out_unlock;
			}
		}

		remap_exception(s, &pe->e, bio, chunk);

		r = DM_MAPIO_SUBMITTED;

		if (!pe->started &&
		    bio->bi_iter.bi_size ==
		    (s->store->chunk_size << SECTOR_SHIFT)) {
			pe->started = 1;
			mutex_unlock(&s->lock);
			start_full_bio(pe, bio);
			goto out;
		}

		bio_list_add(&pe->snapshot_bios, bio);

		if (!pe->started) {
			/* this is protected by snap->lock */
			pe->started = 1;
			mutex_unlock(&s->lock);
			start_copy(pe);
			goto out;
		}
	} else {
		bio_set_dev(bio, s->origin->bdev);
		track_chunk(s, bio, chunk);
	}

out_unlock:
	mutex_unlock(&s->lock);
out:
	return r;
}