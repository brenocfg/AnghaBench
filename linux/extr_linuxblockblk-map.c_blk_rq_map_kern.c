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
struct request_queue {int dummy; } ;
struct request {int /*<<< orphan*/  rq_flags; } ;
struct bio {int /*<<< orphan*/  bi_opf; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct bio*) ; 
 int PTR_ERR (struct bio*) ; 
 scalar_t__ READ ; 
 int /*<<< orphan*/  REQ_OP_MASK ; 
 int /*<<< orphan*/  RQF_COPY_USER ; 
 struct bio* bio_copy_kern (struct request_queue*,void*,unsigned int,int /*<<< orphan*/ ,int) ; 
 struct bio* bio_map_kern (struct request_queue*,void*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  blk_rq_aligned (struct request_queue*,unsigned long,unsigned int) ; 
 int blk_rq_append_bio (struct request*,struct bio**) ; 
 scalar_t__ object_is_on_stack (void*) ; 
 int queue_max_hw_sectors (struct request_queue*) ; 
 int /*<<< orphan*/  req_op (struct request*) ; 
 scalar_t__ rq_data_dir (struct request*) ; 
 scalar_t__ unlikely (int) ; 

int blk_rq_map_kern(struct request_queue *q, struct request *rq, void *kbuf,
		    unsigned int len, gfp_t gfp_mask)
{
	int reading = rq_data_dir(rq) == READ;
	unsigned long addr = (unsigned long) kbuf;
	int do_copy = 0;
	struct bio *bio, *orig_bio;
	int ret;

	if (len > (queue_max_hw_sectors(q) << 9))
		return -EINVAL;
	if (!len || !kbuf)
		return -EINVAL;

	do_copy = !blk_rq_aligned(q, addr, len) || object_is_on_stack(kbuf);
	if (do_copy)
		bio = bio_copy_kern(q, kbuf, len, gfp_mask, reading);
	else
		bio = bio_map_kern(q, kbuf, len, gfp_mask);

	if (IS_ERR(bio))
		return PTR_ERR(bio);

	bio->bi_opf &= ~REQ_OP_MASK;
	bio->bi_opf |= req_op(rq);

	if (do_copy)
		rq->rq_flags |= RQF_COPY_USER;

	orig_bio = bio;
	ret = blk_rq_append_bio(rq, &bio);
	if (unlikely(ret)) {
		/* request is too big */
		bio_put(orig_bio);
		return ret;
	}

	return 0;
}