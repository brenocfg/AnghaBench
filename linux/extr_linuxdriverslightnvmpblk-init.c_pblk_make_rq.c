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
struct pblk {int dummy; } ;
struct bio {int bi_opf; } ;
typedef  int /*<<< orphan*/  blk_qc_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_QC_T_NONE ; 
#define  NVM_IO_DONE 129 
#define  NVM_IO_ERR 128 
 scalar_t__ REQ_OP_DISCARD ; 
 int REQ_PREFLUSH ; 
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 int /*<<< orphan*/  bio_io_error (struct bio*) ; 
 scalar_t__ bio_op (struct bio*) ; 
 int /*<<< orphan*/  pblk_discard (struct pblk*,struct bio*) ; 
 int pblk_rw_io (struct request_queue*,struct pblk*,struct bio*) ; 

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

	switch (pblk_rw_io(q, pblk, bio)) {
	case NVM_IO_ERR:
		bio_io_error(bio);
		break;
	case NVM_IO_DONE:
		bio_endio(bio);
		break;
	}

	return BLK_QC_T_NONE;
}