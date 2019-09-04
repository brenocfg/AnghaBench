#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int /*<<< orphan*/  bio_split; } ;
struct TYPE_2__ {int /*<<< orphan*/  bi_sector; } ;
struct bio {unsigned int bi_phys_segments; TYPE_1__ bi_iter; int /*<<< orphan*/  bi_opf; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_QUEUE_ENTERED ; 
 int /*<<< orphan*/  BIO_SEG_VALID ; 
 int /*<<< orphan*/  REQ_NOMERGE ; 
#define  REQ_OP_DISCARD 131 
#define  REQ_OP_SECURE_ERASE 130 
#define  REQ_OP_WRITE_SAME 129 
#define  REQ_OP_WRITE_ZEROES 128 
 int /*<<< orphan*/  bio_chain (struct bio*,struct bio*) ; 
 int bio_op (struct bio*) ; 
 int /*<<< orphan*/  bio_set_flag (struct bio*,int /*<<< orphan*/ ) ; 
 struct bio* blk_bio_discard_split (struct request_queue*,struct bio*,int /*<<< orphan*/ *,unsigned int*) ; 
 struct bio* blk_bio_segment_split (struct request_queue*,struct bio*,int /*<<< orphan*/ *,unsigned int*) ; 
 struct bio* blk_bio_write_same_split (struct request_queue*,struct bio*,int /*<<< orphan*/ *,unsigned int*) ; 
 struct bio* blk_bio_write_zeroes_split (struct request_queue*,struct bio*,int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  generic_make_request (struct bio*) ; 
 int /*<<< orphan*/  trace_block_split (struct request_queue*,struct bio*,int /*<<< orphan*/ ) ; 

void blk_queue_split(struct request_queue *q, struct bio **bio)
{
	struct bio *split, *res;
	unsigned nsegs;

	switch (bio_op(*bio)) {
	case REQ_OP_DISCARD:
	case REQ_OP_SECURE_ERASE:
		split = blk_bio_discard_split(q, *bio, &q->bio_split, &nsegs);
		break;
	case REQ_OP_WRITE_ZEROES:
		split = blk_bio_write_zeroes_split(q, *bio, &q->bio_split, &nsegs);
		break;
	case REQ_OP_WRITE_SAME:
		split = blk_bio_write_same_split(q, *bio, &q->bio_split, &nsegs);
		break;
	default:
		split = blk_bio_segment_split(q, *bio, &q->bio_split, &nsegs);
		break;
	}

	/* physical segments can be figured out during splitting */
	res = split ? split : *bio;
	res->bi_phys_segments = nsegs;
	bio_set_flag(res, BIO_SEG_VALID);

	if (split) {
		/* there isn't chance to merge the splitted bio */
		split->bi_opf |= REQ_NOMERGE;

		/*
		 * Since we're recursing into make_request here, ensure
		 * that we mark this bio as already having entered the queue.
		 * If not, and the queue is going away, we can get stuck
		 * forever on waiting for the queue reference to drop. But
		 * that will never happen, as we're already holding a
		 * reference to it.
		 */
		bio_set_flag(*bio, BIO_QUEUE_ENTERED);

		bio_chain(split, *bio);
		trace_block_split(q, split, (*bio)->bi_iter.bi_sector);
		generic_make_request(*bio);
		*bio = split;
	}
}