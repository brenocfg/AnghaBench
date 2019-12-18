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
struct mapped_device {int dummy; } ;
struct dm_target_io {int dummy; } ;
struct dm_target {int dummy; } ;
struct dm_table {int dummy; } ;
struct clone_info {int /*<<< orphan*/  io; scalar_t__ sector_count; struct bio* bio; } ;
struct bio {int bi_opf; } ;
typedef  int /*<<< orphan*/  blk_qc_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_QC_T_NONE ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int REQ_OP_WRITE ; 
 int REQ_PREFLUSH ; 
 int REQ_SYNC ; 
 int /*<<< orphan*/  __clone_and_map_simple_bio (struct clone_info*,struct dm_target_io*,int /*<<< orphan*/ *) ; 
 scalar_t__ __process_abnormal_io (struct clone_info*,struct dm_target*,int*) ; 
 int __send_empty_flush (struct clone_info*) ; 
 struct dm_target_io* alloc_tio (struct clone_info*,struct dm_target*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_init (struct bio*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bio_sectors (struct bio*) ; 
 int /*<<< orphan*/  dec_pending (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno_to_blk_status (int) ; 
 int /*<<< orphan*/  init_clone_info (struct clone_info*,struct mapped_device*,struct dm_table*,struct bio*) ; 

__attribute__((used)) static blk_qc_t __process_bio(struct mapped_device *md, struct dm_table *map,
			      struct bio *bio, struct dm_target *ti)
{
	struct clone_info ci;
	blk_qc_t ret = BLK_QC_T_NONE;
	int error = 0;

	init_clone_info(&ci, md, map, bio);

	if (bio->bi_opf & REQ_PREFLUSH) {
		struct bio flush_bio;

		/*
		 * Use an on-stack bio for this, it's safe since we don't
		 * need to reference it after submit. It's just used as
		 * the basis for the clone(s).
		 */
		bio_init(&flush_bio, NULL, 0);
		flush_bio.bi_opf = REQ_OP_WRITE | REQ_PREFLUSH | REQ_SYNC;
		ci.bio = &flush_bio;
		ci.sector_count = 0;
		error = __send_empty_flush(&ci);
		/* dec_pending submits any data associated with flush */
	} else {
		struct dm_target_io *tio;

		ci.bio = bio;
		ci.sector_count = bio_sectors(bio);
		if (__process_abnormal_io(&ci, ti, &error))
			goto out;

		tio = alloc_tio(&ci, ti, 0, GFP_NOIO);
		ret = __clone_and_map_simple_bio(&ci, tio, NULL);
	}
out:
	/* drop the extra reference count */
	dec_pending(ci.io, errno_to_blk_status(error));
	return ret;
}