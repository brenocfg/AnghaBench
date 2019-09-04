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
struct mapped_device {struct dm_target* immutable_target; } ;
struct dm_target_io {int dummy; } ;
struct dm_target {int dummy; } ;
struct dm_table {int dummy; } ;
struct clone_info {TYPE_2__* io; scalar_t__ sector_count; struct bio* bio; } ;
struct bio {int bi_opf; } ;
typedef  int /*<<< orphan*/  blk_qc_t ;
struct TYPE_4__ {TYPE_1__* md; } ;
struct TYPE_3__ {struct bio flush_bio; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_QC_T_NONE ; 
 int EIO ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int REQ_PREFLUSH ; 
 int WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __clone_and_map_simple_bio (struct clone_info*,struct dm_target_io*,int /*<<< orphan*/ *) ; 
 int __process_abnormal_io (struct clone_info*,struct dm_target*,int*) ; 
 int __send_empty_flush (struct clone_info*) ; 
 struct dm_target_io* alloc_tio (struct clone_info*,struct dm_target*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_io_error (struct bio*) ; 
 scalar_t__ bio_sectors (struct bio*) ; 
 int /*<<< orphan*/  dec_pending (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_target_is_valid (struct dm_target*) ; 
 int /*<<< orphan*/  errno_to_blk_status (int) ; 
 int /*<<< orphan*/  init_clone_info (struct clone_info*,struct mapped_device*,struct dm_table*,struct bio*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static blk_qc_t __process_bio(struct mapped_device *md,
			      struct dm_table *map, struct bio *bio)
{
	struct clone_info ci;
	blk_qc_t ret = BLK_QC_T_NONE;
	int error = 0;

	if (unlikely(!map)) {
		bio_io_error(bio);
		return ret;
	}

	init_clone_info(&ci, md, map, bio);

	if (bio->bi_opf & REQ_PREFLUSH) {
		ci.bio = &ci.io->md->flush_bio;
		ci.sector_count = 0;
		error = __send_empty_flush(&ci);
		/* dec_pending submits any data associated with flush */
	} else {
		struct dm_target *ti = md->immutable_target;
		struct dm_target_io *tio;

		/*
		 * Defend against IO still getting in during teardown
		 * - as was seen for a time with nvme-fcloop
		 */
		if (unlikely(WARN_ON_ONCE(!ti || !dm_target_is_valid(ti)))) {
			error = -EIO;
			goto out;
		}

		ci.bio = bio;
		ci.sector_count = bio_sectors(bio);
		if (unlikely(__process_abnormal_io(&ci, ti, &error)))
			goto out;

		tio = alloc_tio(&ci, ti, 0, GFP_NOIO);
		ret = __clone_and_map_simple_bio(&ci, tio, NULL);
	}
out:
	/* drop the extra reference count */
	dec_pending(ci.io, errno_to_blk_status(error));
	return ret;
}