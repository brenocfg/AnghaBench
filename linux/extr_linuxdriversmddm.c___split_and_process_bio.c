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
struct mapped_device {TYPE_4__* queue; } ;
struct dm_table {int dummy; } ;
struct clone_info {TYPE_2__* io; scalar_t__ sector_count; struct bio* bio; } ;
struct bio {int bi_opf; } ;
typedef  int /*<<< orphan*/  blk_qc_t ;
struct TYPE_8__ {int /*<<< orphan*/  bio_split; } ;
struct TYPE_7__ {scalar_t__ bio_list; } ;
struct TYPE_6__ {struct bio* orig_bio; TYPE_1__* md; } ;
struct TYPE_5__ {struct bio flush_bio; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_QC_T_NONE ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 scalar_t__ REQ_OP_ZONE_RESET ; 
 int REQ_PREFLUSH ; 
 int __send_empty_flush (struct clone_info*) ; 
 int __split_and_process_non_flush (struct clone_info*) ; 
 int /*<<< orphan*/  bio_chain (struct bio*,struct bio*) ; 
 int /*<<< orphan*/  bio_io_error (struct bio*) ; 
 scalar_t__ bio_op (struct bio*) ; 
 scalar_t__ bio_sectors (struct bio*) ; 
 struct bio* bio_split (struct bio*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_queue_split (TYPE_4__*,struct bio**) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  dec_pending (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno_to_blk_status (int) ; 
 int /*<<< orphan*/  generic_make_request (struct bio*) ; 
 int /*<<< orphan*/  init_clone_info (struct clone_info*,struct mapped_device*,struct dm_table*,struct bio*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static blk_qc_t __split_and_process_bio(struct mapped_device *md,
					struct dm_table *map, struct bio *bio)
{
	struct clone_info ci;
	blk_qc_t ret = BLK_QC_T_NONE;
	int error = 0;

	if (unlikely(!map)) {
		bio_io_error(bio);
		return ret;
	}

	blk_queue_split(md->queue, &bio);

	init_clone_info(&ci, md, map, bio);

	if (bio->bi_opf & REQ_PREFLUSH) {
		ci.bio = &ci.io->md->flush_bio;
		ci.sector_count = 0;
		error = __send_empty_flush(&ci);
		/* dec_pending submits any data associated with flush */
	} else if (bio_op(bio) == REQ_OP_ZONE_RESET) {
		ci.bio = bio;
		ci.sector_count = 0;
		error = __split_and_process_non_flush(&ci);
	} else {
		ci.bio = bio;
		ci.sector_count = bio_sectors(bio);
		while (ci.sector_count && !error) {
			error = __split_and_process_non_flush(&ci);
			if (current->bio_list && ci.sector_count && !error) {
				/*
				 * Remainder must be passed to generic_make_request()
				 * so that it gets handled *after* bios already submitted
				 * have been completely processed.
				 * We take a clone of the original to store in
				 * ci.io->orig_bio to be used by end_io_acct() and
				 * for dec_pending to use for completion handling.
				 * As this path is not used for REQ_OP_ZONE_REPORT,
				 * the usage of io->orig_bio in dm_remap_zone_report()
				 * won't be affected by this reassignment.
				 */
				struct bio *b = bio_split(bio, bio_sectors(bio) - ci.sector_count,
							  GFP_NOIO, &md->queue->bio_split);
				ci.io->orig_bio = b;
				bio_chain(b, bio);
				ret = generic_make_request(bio);
				break;
			}
		}
	}

	/* drop the extra reference count */
	dec_pending(ci.io, errno_to_blk_status(error));
	return ret;
}