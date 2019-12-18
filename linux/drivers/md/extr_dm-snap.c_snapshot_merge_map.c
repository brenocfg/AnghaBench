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
struct dm_target {struct dm_snapshot* private; } ;
struct dm_snapshot {scalar_t__ first_merging_chunk; scalar_t__ num_merging_chunks; int /*<<< orphan*/  lock; TYPE_3__* origin; int /*<<< orphan*/  bios_queued_during_merge; int /*<<< orphan*/  complete; int /*<<< orphan*/  valid; int /*<<< orphan*/  store; TYPE_1__* cow; } ;
struct dm_exception {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  bi_sector; } ;
struct bio {int bi_opf; TYPE_2__ bi_iter; } ;
typedef  scalar_t__ chunk_t ;
struct TYPE_6__ {int /*<<< orphan*/  bdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int DM_MAPIO_REMAPPED ; 
 int DM_MAPIO_SUBMITTED ; 
 scalar_t__ REQ_OP_DISCARD ; 
 int REQ_PREFLUSH ; 
 scalar_t__ WRITE ; 
 scalar_t__ bio_data_dir (struct bio*) ; 
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 int /*<<< orphan*/  bio_list_add (int /*<<< orphan*/ *,struct bio*) ; 
 scalar_t__ bio_op (struct bio*) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_bio_get_target_bio_nr (struct bio*) ; 
 struct dm_exception* dm_lookup_exception (int /*<<< orphan*/ *,scalar_t__) ; 
 int do_origin (TYPE_3__*,struct bio*,int) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_tracked_chunk (struct bio*) ; 
 int /*<<< orphan*/  remap_exception (struct dm_snapshot*,struct dm_exception*,struct bio*,scalar_t__) ; 
 scalar_t__ sector_to_chunk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  track_chunk (struct dm_snapshot*,struct bio*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snapshot_merge_map(struct dm_target *ti, struct bio *bio)
{
	struct dm_exception *e;
	struct dm_snapshot *s = ti->private;
	int r = DM_MAPIO_REMAPPED;
	chunk_t chunk;

	init_tracked_chunk(bio);

	if (bio->bi_opf & REQ_PREFLUSH) {
		if (!dm_bio_get_target_bio_nr(bio))
			bio_set_dev(bio, s->origin->bdev);
		else
			bio_set_dev(bio, s->cow->bdev);
		return DM_MAPIO_REMAPPED;
	}

	if (unlikely(bio_op(bio) == REQ_OP_DISCARD)) {
		/* Once merging, discards no longer effect change */
		bio_endio(bio);
		return DM_MAPIO_SUBMITTED;
	}

	chunk = sector_to_chunk(s->store, bio->bi_iter.bi_sector);

	down_write(&s->lock);

	/* Full merging snapshots are redirected to the origin */
	if (!s->valid)
		goto redirect_to_origin;

	/* If the block is already remapped - use that */
	e = dm_lookup_exception(&s->complete, chunk);
	if (e) {
		/* Queue writes overlapping with chunks being merged */
		if (bio_data_dir(bio) == WRITE &&
		    chunk >= s->first_merging_chunk &&
		    chunk < (s->first_merging_chunk +
			     s->num_merging_chunks)) {
			bio_set_dev(bio, s->origin->bdev);
			bio_list_add(&s->bios_queued_during_merge, bio);
			r = DM_MAPIO_SUBMITTED;
			goto out_unlock;
		}

		remap_exception(s, e, bio, chunk);

		if (bio_data_dir(bio) == WRITE)
			track_chunk(s, bio, chunk);
		goto out_unlock;
	}

redirect_to_origin:
	bio_set_dev(bio, s->origin->bdev);

	if (bio_data_dir(bio) == WRITE) {
		up_write(&s->lock);
		return do_origin(s->origin, bio, false);
	}

out_unlock:
	up_write(&s->lock);

	return r;
}