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
struct r10conf {TYPE_1__* mirrors; } ;
struct r10bio {int sectors; int sector; TYPE_3__* devs; struct mddev* mddev; struct bio* master_bio; } ;
struct mddev {int /*<<< orphan*/  bio_set; struct r10conf* private; } ;
struct TYPE_6__ {int shift; } ;
struct md_rdev {int /*<<< orphan*/  bdev; TYPE_2__ badblocks; } ;
struct TYPE_8__ {int bi_sector; } ;
struct bio {TYPE_4__ bi_iter; } ;
typedef  int sector_t ;
struct TYPE_7__ {size_t devnum; int addr; } ;
struct TYPE_5__ {struct md_rdev* rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 int bdev_logical_block_size (int /*<<< orphan*/ ) ; 
 struct bio* bio_clone_fast (struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_set_op_attrs (struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_trim (struct bio*,int,int) ; 
 int choose_data_offset (struct r10bio*,struct md_rdev*) ; 
 scalar_t__ rdev_set_badblocks (struct md_rdev*,int,int,int /*<<< orphan*/ ) ; 
 int roundup (int,int) ; 
 scalar_t__ submit_bio_wait (struct bio*) ; 

__attribute__((used)) static int narrow_write_error(struct r10bio *r10_bio, int i)
{
	struct bio *bio = r10_bio->master_bio;
	struct mddev *mddev = r10_bio->mddev;
	struct r10conf *conf = mddev->private;
	struct md_rdev *rdev = conf->mirrors[r10_bio->devs[i].devnum].rdev;
	/* bio has the data to be written to slot 'i' where
	 * we just recently had a write error.
	 * We repeatedly clone the bio and trim down to one block,
	 * then try the write.  Where the write fails we record
	 * a bad block.
	 * It is conceivable that the bio doesn't exactly align with
	 * blocks.  We must handle this.
	 *
	 * We currently own a reference to the rdev.
	 */

	int block_sectors;
	sector_t sector;
	int sectors;
	int sect_to_write = r10_bio->sectors;
	int ok = 1;

	if (rdev->badblocks.shift < 0)
		return 0;

	block_sectors = roundup(1 << rdev->badblocks.shift,
				bdev_logical_block_size(rdev->bdev) >> 9);
	sector = r10_bio->sector;
	sectors = ((r10_bio->sector + block_sectors)
		   & ~(sector_t)(block_sectors - 1))
		- sector;

	while (sect_to_write) {
		struct bio *wbio;
		sector_t wsector;
		if (sectors > sect_to_write)
			sectors = sect_to_write;
		/* Write at 'sector' for 'sectors' */
		wbio = bio_clone_fast(bio, GFP_NOIO, &mddev->bio_set);
		bio_trim(wbio, sector - bio->bi_iter.bi_sector, sectors);
		wsector = r10_bio->devs[i].addr + (sector - r10_bio->sector);
		wbio->bi_iter.bi_sector = wsector +
				   choose_data_offset(r10_bio, rdev);
		bio_set_dev(wbio, rdev->bdev);
		bio_set_op_attrs(wbio, REQ_OP_WRITE, 0);

		if (submit_bio_wait(wbio) < 0)
			/* Failure! */
			ok = rdev_set_badblocks(rdev, wsector,
						sectors, 0)
				&& ok;

		bio_put(wbio);
		sect_to_write -= sectors;
		sector += sectors;
		sectors = block_sectors;
	}
	return ok;
}