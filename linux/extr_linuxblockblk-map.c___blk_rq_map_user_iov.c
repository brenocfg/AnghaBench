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
struct rq_map_data {int dummy; } ;
struct request_queue {int dummy; } ;
struct request {struct request_queue* q; } ;
struct iov_iter {int dummy; } ;
struct bio {int /*<<< orphan*/  bi_opf; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct bio*) ; 
 int PTR_ERR (struct bio*) ; 
 int /*<<< orphan*/  REQ_OP_MASK ; 
 int /*<<< orphan*/  __blk_rq_unmap_user (struct bio*) ; 
 struct bio* bio_copy_user_iov (struct request_queue*,struct rq_map_data*,struct iov_iter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_get (struct bio*) ; 
 struct bio* bio_map_user_iov (struct request_queue*,struct iov_iter*,int /*<<< orphan*/ ) ; 
 int blk_rq_append_bio (struct request*,struct bio**) ; 
 int /*<<< orphan*/  req_op (struct request*) ; 

__attribute__((used)) static int __blk_rq_map_user_iov(struct request *rq,
		struct rq_map_data *map_data, struct iov_iter *iter,
		gfp_t gfp_mask, bool copy)
{
	struct request_queue *q = rq->q;
	struct bio *bio, *orig_bio;
	int ret;

	if (copy)
		bio = bio_copy_user_iov(q, map_data, iter, gfp_mask);
	else
		bio = bio_map_user_iov(q, iter, gfp_mask);

	if (IS_ERR(bio))
		return PTR_ERR(bio);

	bio->bi_opf &= ~REQ_OP_MASK;
	bio->bi_opf |= req_op(rq);

	orig_bio = bio;

	/*
	 * We link the bounce buffer in and could have to traverse it
	 * later so we have to get a ref to prevent it from being freed
	 */
	ret = blk_rq_append_bio(rq, &bio);
	if (ret) {
		__blk_rq_unmap_user(orig_bio);
		return ret;
	}
	bio_get(bio);

	return 0;
}