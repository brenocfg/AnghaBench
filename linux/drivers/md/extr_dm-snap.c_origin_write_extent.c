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
struct origin {int /*<<< orphan*/  snapshots; } ;
struct dm_snapshot {TYPE_2__* ti; TYPE_1__* origin; } ;
typedef  unsigned int sector_t ;
struct TYPE_4__ {unsigned int max_io_len; } ;
struct TYPE_3__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 scalar_t__ DM_MAPIO_SUBMITTED ; 
 struct origin* __lookup_origin (int /*<<< orphan*/ ) ; 
 scalar_t__ __origin_write (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _origins_lock ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int origin_write_extent(struct dm_snapshot *merging_snap,
			       sector_t sector, unsigned size)
{
	int must_wait = 0;
	sector_t n;
	struct origin *o;

	/*
	 * The origin's __minimum_chunk_size() got stored in max_io_len
	 * by snapshot_merge_resume().
	 */
	down_read(&_origins_lock);
	o = __lookup_origin(merging_snap->origin->bdev);
	for (n = 0; n < size; n += merging_snap->ti->max_io_len)
		if (__origin_write(&o->snapshots, sector + n, NULL) ==
		    DM_MAPIO_SUBMITTED)
			must_wait = 1;
	up_read(&_origins_lock);

	return must_wait;
}