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
struct dm_io_region {int count; int /*<<< orphan*/  sector; int /*<<< orphan*/  bdev; } ;
struct dm_clone_region_hydration {unsigned long region_nr; struct clone* clone; } ;
struct clone {int region_size; unsigned int region_shift; int nr_regions; int /*<<< orphan*/  kcopyd_client; int /*<<< orphan*/  hydrations_in_flight; TYPE_3__* dest_dev; TYPE_2__* source_dev; TYPE_1__* ti; } ;
typedef  int sector_t ;
struct TYPE_6__ {int /*<<< orphan*/  bdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  bdev; } ;
struct TYPE_4__ {int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_kcopyd_copy (int /*<<< orphan*/ ,struct dm_io_region*,int,struct dm_io_region*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dm_clone_region_hydration*) ; 
 int /*<<< orphan*/  hydration_kcopyd_callback ; 
 int /*<<< orphan*/  region_to_sector (struct clone*,unsigned long) ; 

__attribute__((used)) static void hydration_copy(struct dm_clone_region_hydration *hd, unsigned int nr_regions)
{
	unsigned long region_start, region_end;
	sector_t tail_size, region_size, total_size;
	struct dm_io_region from, to;
	struct clone *clone = hd->clone;

	region_size = clone->region_size;
	region_start = hd->region_nr;
	region_end = region_start + nr_regions - 1;

	total_size = (nr_regions - 1) << clone->region_shift;

	if (region_end == clone->nr_regions - 1) {
		/*
		 * The last region of the target might be smaller than
		 * region_size.
		 */
		tail_size = clone->ti->len & (region_size - 1);
		if (!tail_size)
			tail_size = region_size;
	} else {
		tail_size = region_size;
	}

	total_size += tail_size;

	from.bdev = clone->source_dev->bdev;
	from.sector = region_to_sector(clone, region_start);
	from.count = total_size;

	to.bdev = clone->dest_dev->bdev;
	to.sector = from.sector;
	to.count = from.count;

	/* Issue copy */
	atomic_add(nr_regions, &clone->hydrations_in_flight);
	dm_kcopyd_copy(clone->kcopyd_client, &from, 1, &to, 0,
		       hydration_kcopyd_callback, hd);
}