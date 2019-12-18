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
struct mapped_device {int /*<<< orphan*/  queue; struct dm_target* immutable_target; } ;
struct dm_target {int dummy; } ;
struct dm_table {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  bi_sector; } ;
struct bio {TYPE_1__ bi_iter; } ;
typedef  int /*<<< orphan*/  blk_qc_t ;
struct TYPE_4__ {scalar_t__ bio_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_QC_T_NONE ; 
 scalar_t__ DM_TYPE_NVME_BIO_BASED ; 
 int /*<<< orphan*/  __process_bio (struct mapped_device*,struct dm_table*,struct bio*,struct dm_target*) ; 
 int /*<<< orphan*/  __split_and_process_bio (struct mapped_device*,struct dm_table*,struct bio*) ; 
 int /*<<< orphan*/  bio_io_error (struct bio*) ; 
 int /*<<< orphan*/  blk_queue_split (int /*<<< orphan*/ ,struct bio**) ; 
 TYPE_2__* current ; 
 scalar_t__ dm_get_md_type (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_queue_split (struct mapped_device*,struct dm_target*,struct bio**) ; 
 struct dm_target* dm_table_find_target (struct dm_table*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_abnormal_io (struct bio*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static blk_qc_t dm_process_bio(struct mapped_device *md,
			       struct dm_table *map, struct bio *bio)
{
	blk_qc_t ret = BLK_QC_T_NONE;
	struct dm_target *ti = md->immutable_target;

	if (unlikely(!map)) {
		bio_io_error(bio);
		return ret;
	}

	if (!ti) {
		ti = dm_table_find_target(map, bio->bi_iter.bi_sector);
		if (unlikely(!ti)) {
			bio_io_error(bio);
			return ret;
		}
	}

	/*
	 * If in ->make_request_fn we need to use blk_queue_split(), otherwise
	 * queue_limits for abnormal requests (e.g. discard, writesame, etc)
	 * won't be imposed.
	 */
	if (current->bio_list) {
		blk_queue_split(md->queue, &bio);
		if (!is_abnormal_io(bio))
			dm_queue_split(md, ti, &bio);
	}

	if (dm_get_md_type(md) == DM_TYPE_NVME_BIO_BASED)
		return __process_bio(md, map, bio, ti);
	else
		return __split_and_process_bio(md, map, bio);
}