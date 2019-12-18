#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dm_snapshot {int merge_failed; int /*<<< orphan*/  lock; int /*<<< orphan*/  num_merging_chunks; TYPE_2__* store; } ;
struct bio {int dummy; } ;
struct TYPE_4__ {TYPE_1__* type; } ;
struct TYPE_3__ {scalar_t__ (* commit_merge ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 struct bio* __release_queued_bios_after_merge (struct dm_snapshot*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error_bios (struct bio*) ; 
 int /*<<< orphan*/  merge_shutdown (struct dm_snapshot*) ; 
 scalar_t__ remove_single_exception_chunk (struct dm_snapshot*) ; 
 int /*<<< orphan*/  snapshot_merge_next_chunks (struct dm_snapshot*) ; 
 scalar_t__ stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void merge_callback(int read_err, unsigned long write_err, void *context)
{
	struct dm_snapshot *s = context;
	struct bio *b = NULL;

	if (read_err || write_err) {
		if (read_err)
			DMERR("Read error: shutting down merge.");
		else
			DMERR("Write error: shutting down merge.");
		goto shut;
	}

	if (s->store->type->commit_merge(s->store,
					 s->num_merging_chunks) < 0) {
		DMERR("Write error in exception store: shutting down merge");
		goto shut;
	}

	if (remove_single_exception_chunk(s) < 0)
		goto shut;

	snapshot_merge_next_chunks(s);

	return;

shut:
	down_write(&s->lock);
	s->merge_failed = 1;
	b = __release_queued_bios_after_merge(s);
	up_write(&s->lock);
	error_bios(b);

	merge_shutdown(s);
}