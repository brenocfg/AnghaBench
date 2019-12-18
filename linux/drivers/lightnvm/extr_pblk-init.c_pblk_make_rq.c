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
struct request_queue {struct pblk* queuedata; } ;
struct pblk {int /*<<< orphan*/  rl; } ;
struct bio {int bi_opf; } ;
typedef  int /*<<< orphan*/  blk_qc_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_QC_T_NONE ; 
 int /*<<< orphan*/  PBLK_IOTYPE_USER ; 
 scalar_t__ READ ; 
 scalar_t__ REQ_OP_DISCARD ; 
 int REQ_PREFLUSH ; 
 scalar_t__ bio_data_dir (struct bio*) ; 
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 scalar_t__ bio_op (struct bio*) ; 
 int /*<<< orphan*/  blk_queue_split (struct request_queue*,struct bio**) ; 
 int /*<<< orphan*/  pblk_discard (struct pblk*,struct bio*) ; 
 scalar_t__ pblk_get_secs (struct bio*) ; 
 scalar_t__ pblk_rl_max_io (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pblk_submit_read (struct pblk*,struct bio*) ; 
 int /*<<< orphan*/  pblk_write_to_cache (struct pblk*,struct bio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static blk_qc_t pblk_make_rq(struct request_queue *q, struct bio *bio)
{
	struct pblk *pblk = q->queuedata;

	if (bio_op(bio) == REQ_OP_DISCARD) {
		pblk_discard(pblk, bio);
		if (!(bio->bi_opf & REQ_PREFLUSH)) {
			bio_endio(bio);
			return BLK_QC_T_NONE;
		}
	}

	/* Read requests must be <= 256kb due to NVMe's 64 bit completion bitmap
	 * constraint. Writes can be of arbitrary size.
	 */
	if (bio_data_dir(bio) == READ) {
		blk_queue_split(q, &bio);
		pblk_submit_read(pblk, bio);
	} else {
		/* Prevent deadlock in the case of a modest LUN configuration
		 * and large user I/Os. Unless stalled, the rate limiter
		 * leaves at least 256KB available for user I/O.
		 */
		if (pblk_get_secs(bio) > pblk_rl_max_io(&pblk->rl))
			blk_queue_split(q, &bio);

		pblk_write_to_cache(pblk, bio, PBLK_IOTYPE_USER);
	}

	return BLK_QC_T_NONE;
}