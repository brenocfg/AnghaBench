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
struct dm_snapshot {int /*<<< orphan*/  lock; int /*<<< orphan*/  complete; int /*<<< orphan*/  valid; } ;
struct dm_exception {int /*<<< orphan*/  old_chunk; } ;
struct dm_snap_pending_exception {int /*<<< orphan*/  full_bio_end_io; struct bio* full_bio; int /*<<< orphan*/  origin_bios; int /*<<< orphan*/  snapshot_bios; struct dm_exception e; struct dm_snapshot* snap; } ;
struct dm_exception_table_lock {int dummy; } ;
struct bio {int /*<<< orphan*/  bi_end_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  __check_for_conflicting_io (struct dm_snapshot*,int /*<<< orphan*/ ) ; 
 scalar_t__ __chunk_is_tracked (struct dm_snapshot*,int /*<<< orphan*/ ) ; 
 struct dm_exception* alloc_completed_exception (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 int /*<<< orphan*/  bio_io_error (struct bio*) ; 
 struct bio* bio_list_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_exception_table_lock (struct dm_exception_table_lock*) ; 
 int /*<<< orphan*/  dm_exception_table_lock_init (struct dm_snapshot*,int /*<<< orphan*/ ,struct dm_exception_table_lock*) ; 
 int /*<<< orphan*/  dm_exception_table_unlock (struct dm_exception_table_lock*) ; 
 int /*<<< orphan*/  dm_insert_exception (int /*<<< orphan*/ *,struct dm_exception*) ; 
 int /*<<< orphan*/  dm_remove_exception (struct dm_exception*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error_bios (struct bio*) ; 
 int /*<<< orphan*/  flush_bios (struct bio*) ; 
 int /*<<< orphan*/  free_completed_exception (struct dm_exception*) ; 
 int /*<<< orphan*/  free_pending_exception (struct dm_snap_pending_exception*) ; 
 int /*<<< orphan*/  increment_pending_exceptions_done_count () ; 
 int /*<<< orphan*/  invalidate_snapshot (struct dm_snapshot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  retry_origin_bios (struct dm_snapshot*,struct bio*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pending_complete(void *context, int success)
{
	struct dm_snap_pending_exception *pe = context;
	struct dm_exception *e;
	struct dm_snapshot *s = pe->snap;
	struct bio *origin_bios = NULL;
	struct bio *snapshot_bios = NULL;
	struct bio *full_bio = NULL;
	struct dm_exception_table_lock lock;
	int error = 0;

	dm_exception_table_lock_init(s, pe->e.old_chunk, &lock);

	if (!success) {
		/* Read/write error - snapshot is unusable */
		invalidate_snapshot(s, -EIO);
		error = 1;

		dm_exception_table_lock(&lock);
		goto out;
	}

	e = alloc_completed_exception(GFP_NOIO);
	if (!e) {
		invalidate_snapshot(s, -ENOMEM);
		error = 1;

		dm_exception_table_lock(&lock);
		goto out;
	}
	*e = pe->e;

	down_read(&s->lock);
	dm_exception_table_lock(&lock);
	if (!s->valid) {
		up_read(&s->lock);
		free_completed_exception(e);
		error = 1;

		goto out;
	}

	/*
	 * Add a proper exception. After inserting the completed exception all
	 * subsequent snapshot reads to this chunk will be redirected to the
	 * COW device.  This ensures that we do not starve. Moreover, as long
	 * as the pending exception exists, neither origin writes nor snapshot
	 * merging can overwrite the chunk in origin.
	 */
	dm_insert_exception(&s->complete, e);
	up_read(&s->lock);

	/* Wait for conflicting reads to drain */
	if (__chunk_is_tracked(s, pe->e.old_chunk)) {
		dm_exception_table_unlock(&lock);
		__check_for_conflicting_io(s, pe->e.old_chunk);
		dm_exception_table_lock(&lock);
	}

out:
	/* Remove the in-flight exception from the list */
	dm_remove_exception(&pe->e);

	dm_exception_table_unlock(&lock);

	snapshot_bios = bio_list_get(&pe->snapshot_bios);
	origin_bios = bio_list_get(&pe->origin_bios);
	full_bio = pe->full_bio;
	if (full_bio)
		full_bio->bi_end_io = pe->full_bio_end_io;
	increment_pending_exceptions_done_count();

	/* Submit any pending write bios */
	if (error) {
		if (full_bio)
			bio_io_error(full_bio);
		error_bios(snapshot_bios);
	} else {
		if (full_bio)
			bio_endio(full_bio);
		flush_bios(snapshot_bios);
	}

	retry_origin_bios(s, origin_bios);

	free_pending_exception(pe);
}