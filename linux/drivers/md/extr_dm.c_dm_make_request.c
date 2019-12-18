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
struct request_queue {struct mapped_device* queuedata; } ;
struct mapped_device {int /*<<< orphan*/  flags; } ;
struct dm_table {int dummy; } ;
struct bio {int bi_opf; } ;
typedef  int /*<<< orphan*/  blk_qc_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_QC_T_NONE ; 
 int /*<<< orphan*/  DMF_BLOCK_IO_FOR_SUSPEND ; 
 int REQ_RAHEAD ; 
 int /*<<< orphan*/  bio_io_error (struct bio*) ; 
 struct dm_table* dm_get_live_table (struct mapped_device*,int*) ; 
 int /*<<< orphan*/  dm_process_bio (struct mapped_device*,struct dm_table*,struct bio*) ; 
 int /*<<< orphan*/  dm_put_live_table (struct mapped_device*,int) ; 
 int /*<<< orphan*/  queue_io (struct mapped_device*,struct bio*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static blk_qc_t dm_make_request(struct request_queue *q, struct bio *bio)
{
	struct mapped_device *md = q->queuedata;
	blk_qc_t ret = BLK_QC_T_NONE;
	int srcu_idx;
	struct dm_table *map;

	map = dm_get_live_table(md, &srcu_idx);

	/* if we're suspended, we have to queue this io for later */
	if (unlikely(test_bit(DMF_BLOCK_IO_FOR_SUSPEND, &md->flags))) {
		dm_put_live_table(md, srcu_idx);

		if (!(bio->bi_opf & REQ_RAHEAD))
			queue_io(md, bio);
		else
			bio_io_error(bio);
		return ret;
	}

	ret = dm_process_bio(md, map, bio);

	dm_put_live_table(md, srcu_idx);
	return ret;
}