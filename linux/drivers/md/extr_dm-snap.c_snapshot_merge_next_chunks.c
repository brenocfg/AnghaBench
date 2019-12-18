#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct dm_snapshot {int merge_failed; int num_merging_chunks; int /*<<< orphan*/  kcopyd_client; int /*<<< orphan*/  lock; scalar_t__ first_merging_chunk; TYPE_4__* store; TYPE_3__* cow; TYPE_2__* origin; int /*<<< orphan*/  valid; int /*<<< orphan*/  state_bits; } ;
struct dm_io_region {void* sector; int /*<<< orphan*/  count; int /*<<< orphan*/  bdev; } ;
typedef  int sector_t ;
typedef  scalar_t__ chunk_t ;
struct TYPE_9__ {int chunk_size; TYPE_1__* type; } ;
struct TYPE_8__ {int /*<<< orphan*/  bdev; } ;
struct TYPE_7__ {int /*<<< orphan*/  bdev; } ;
struct TYPE_6__ {int (* prepare_merge ) (TYPE_4__*,scalar_t__*,scalar_t__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DMERR (char*) ; 
 int /*<<< orphan*/  RUNNING_MERGE ; 
 int /*<<< orphan*/  SHUTDOWN_MERGE ; 
 int /*<<< orphan*/  __check_for_conflicting_io (struct dm_snapshot*,scalar_t__) ; 
 int /*<<< orphan*/  _pending_exceptions_done ; 
 void* chunk_to_sector (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  dm_kcopyd_copy (int /*<<< orphan*/ ,struct dm_io_region*,int,struct dm_io_region*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dm_snapshot*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 void* get_dev_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  merge_callback ; 
 int /*<<< orphan*/  merge_shutdown (struct dm_snapshot*) ; 
 int /*<<< orphan*/  min (int,void*) ; 
 scalar_t__ origin_write_extent (struct dm_snapshot*,void*,int) ; 
 scalar_t__ read_pending_exceptions_done_count () ; 
 int stub1 (TYPE_4__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void snapshot_merge_next_chunks(struct dm_snapshot *s)
{
	int i, linear_chunks;
	chunk_t old_chunk, new_chunk;
	struct dm_io_region src, dest;
	sector_t io_size;
	uint64_t previous_count;

	BUG_ON(!test_bit(RUNNING_MERGE, &s->state_bits));
	if (unlikely(test_bit(SHUTDOWN_MERGE, &s->state_bits)))
		goto shut;

	/*
	 * valid flag never changes during merge, so no lock required.
	 */
	if (!s->valid) {
		DMERR("Snapshot is invalid: can't merge");
		goto shut;
	}

	linear_chunks = s->store->type->prepare_merge(s->store, &old_chunk,
						      &new_chunk);
	if (linear_chunks <= 0) {
		if (linear_chunks < 0) {
			DMERR("Read error in exception store: "
			      "shutting down merge");
			down_write(&s->lock);
			s->merge_failed = 1;
			up_write(&s->lock);
		}
		goto shut;
	}

	/* Adjust old_chunk and new_chunk to reflect start of linear region */
	old_chunk = old_chunk + 1 - linear_chunks;
	new_chunk = new_chunk + 1 - linear_chunks;

	/*
	 * Use one (potentially large) I/O to copy all 'linear_chunks'
	 * from the exception store to the origin
	 */
	io_size = linear_chunks * s->store->chunk_size;

	dest.bdev = s->origin->bdev;
	dest.sector = chunk_to_sector(s->store, old_chunk);
	dest.count = min(io_size, get_dev_size(dest.bdev) - dest.sector);

	src.bdev = s->cow->bdev;
	src.sector = chunk_to_sector(s->store, new_chunk);
	src.count = dest.count;

	/*
	 * Reallocate any exceptions needed in other snapshots then
	 * wait for the pending exceptions to complete.
	 * Each time any pending exception (globally on the system)
	 * completes we are woken and repeat the process to find out
	 * if we can proceed.  While this may not seem a particularly
	 * efficient algorithm, it is not expected to have any
	 * significant impact on performance.
	 */
	previous_count = read_pending_exceptions_done_count();
	while (origin_write_extent(s, dest.sector, io_size)) {
		wait_event(_pending_exceptions_done,
			   (read_pending_exceptions_done_count() !=
			    previous_count));
		/* Retry after the wait, until all exceptions are done. */
		previous_count = read_pending_exceptions_done_count();
	}

	down_write(&s->lock);
	s->first_merging_chunk = old_chunk;
	s->num_merging_chunks = linear_chunks;
	up_write(&s->lock);

	/* Wait until writes to all 'linear_chunks' drain */
	for (i = 0; i < linear_chunks; i++)
		__check_for_conflicting_io(s, old_chunk + i);

	dm_kcopyd_copy(s->kcopyd_client, &src, 1, &dest, 0, merge_callback, s);
	return;

shut:
	merge_shutdown(s);
}