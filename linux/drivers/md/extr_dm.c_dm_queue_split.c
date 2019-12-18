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
struct mapped_device {TYPE_2__* queue; } ;
struct dm_target {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  bi_sector; } ;
struct bio {TYPE_1__ bi_iter; } ;
struct TYPE_4__ {int /*<<< orphan*/  bio_split; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  bio_chain (struct bio*,struct bio*) ; 
 unsigned int bio_sectors (struct bio*) ; 
 struct bio* bio_split (struct bio*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  generic_make_request (struct bio*) ; 
 int /*<<< orphan*/  max_io_len (int /*<<< orphan*/ ,struct dm_target*) ; 
 unsigned int min_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  sector_t ; 
 int /*<<< orphan*/  trace_block_split (TYPE_2__*,struct bio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dm_queue_split(struct mapped_device *md, struct dm_target *ti, struct bio **bio)
{
	unsigned len, sector_count;

	sector_count = bio_sectors(*bio);
	len = min_t(sector_t, max_io_len((*bio)->bi_iter.bi_sector, ti), sector_count);

	if (sector_count > len) {
		struct bio *split = bio_split(*bio, len, GFP_NOIO, &md->queue->bio_split);

		bio_chain(split, *bio);
		trace_block_split(md->queue, split, (*bio)->bi_iter.bi_sector);
		generic_make_request(*bio);
		*bio = split;
	}
}