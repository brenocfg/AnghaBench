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
struct TYPE_4__ {int bi_sector; int bi_size; } ;
struct dm_verity_io {int block; int n_blocks; TYPE_2__ iter; int /*<<< orphan*/  orig_bi_end_io; struct dm_verity* v; } ;
struct dm_verity {int data_dev_block_bits; int data_blocks; TYPE_1__* data_dev; } ;
struct dm_target {int /*<<< orphan*/  per_io_data_size; struct dm_verity* private; } ;
struct bio {TYPE_2__ bi_iter; struct dm_verity_io* bi_private; int /*<<< orphan*/  bi_end_io; } ;
struct TYPE_3__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR_LIMIT (char*) ; 
 int DM_MAPIO_KILL ; 
 int DM_MAPIO_SUBMITTED ; 
 int SECTOR_SHIFT ; 
 scalar_t__ WRITE ; 
 scalar_t__ bio_data_dir (struct bio*) ; 
 int bio_end_sector (struct bio*) ; 
 unsigned int bio_sectors (struct bio*) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 struct dm_verity_io* dm_per_bio_data (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_make_request (struct bio*) ; 
 int /*<<< orphan*/  verity_end_io ; 
 int /*<<< orphan*/  verity_fec_init_io (struct dm_verity_io*) ; 
 int verity_map_sector (struct dm_verity*,int) ; 
 int /*<<< orphan*/  verity_submit_prefetch (struct dm_verity*,struct dm_verity_io*) ; 

__attribute__((used)) static int verity_map(struct dm_target *ti, struct bio *bio)
{
	struct dm_verity *v = ti->private;
	struct dm_verity_io *io;

	bio_set_dev(bio, v->data_dev->bdev);
	bio->bi_iter.bi_sector = verity_map_sector(v, bio->bi_iter.bi_sector);

	if (((unsigned)bio->bi_iter.bi_sector | bio_sectors(bio)) &
	    ((1 << (v->data_dev_block_bits - SECTOR_SHIFT)) - 1)) {
		DMERR_LIMIT("unaligned io");
		return DM_MAPIO_KILL;
	}

	if (bio_end_sector(bio) >>
	    (v->data_dev_block_bits - SECTOR_SHIFT) > v->data_blocks) {
		DMERR_LIMIT("io out of range");
		return DM_MAPIO_KILL;
	}

	if (bio_data_dir(bio) == WRITE)
		return DM_MAPIO_KILL;

	io = dm_per_bio_data(bio, ti->per_io_data_size);
	io->v = v;
	io->orig_bi_end_io = bio->bi_end_io;
	io->block = bio->bi_iter.bi_sector >> (v->data_dev_block_bits - SECTOR_SHIFT);
	io->n_blocks = bio->bi_iter.bi_size >> v->data_dev_block_bits;

	bio->bi_end_io = verity_end_io;
	bio->bi_private = io;
	io->iter = bio->bi_iter;

	verity_fec_init_io(io);

	verity_submit_prefetch(v, io);

	generic_make_request(bio);

	return DM_MAPIO_SUBMITTED;
}