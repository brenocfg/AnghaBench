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
struct pstore {int next_free; int /*<<< orphan*/  pending_count; } ;
struct dm_exception_store {int chunk_size; int /*<<< orphan*/  snap; } ;
struct dm_exception {int new_chunk; } ;
typedef  int sector_t ;
struct TYPE_2__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 TYPE_1__* dm_snap_cow (int /*<<< orphan*/ ) ; 
 int get_dev_size (int /*<<< orphan*/ ) ; 
 struct pstore* get_info (struct dm_exception_store*) ; 
 int /*<<< orphan*/  skip_metadata (struct pstore*) ; 

__attribute__((used)) static int persistent_prepare_exception(struct dm_exception_store *store,
					struct dm_exception *e)
{
	struct pstore *ps = get_info(store);
	sector_t size = get_dev_size(dm_snap_cow(store->snap)->bdev);

	/* Is there enough room ? */
	if (size < ((ps->next_free + 1) * store->chunk_size))
		return -ENOSPC;

	e->new_chunk = ps->next_free;

	/*
	 * Move onto the next free pending, making sure to take
	 * into account the location of the metadata chunks.
	 */
	ps->next_free++;
	skip_metadata(ps);

	atomic_inc(&ps->pending_count);
	return 0;
}