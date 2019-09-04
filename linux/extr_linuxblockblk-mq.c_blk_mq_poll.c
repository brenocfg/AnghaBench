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
struct request_queue {struct blk_mq_hw_ctx** queue_hw_ctx; int /*<<< orphan*/  queue_flags; } ;
struct request {int dummy; } ;
struct blk_mq_hw_ctx {int /*<<< orphan*/  sched_tags; int /*<<< orphan*/  tags; } ;
typedef  int /*<<< orphan*/  blk_qc_t ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_FLAG_POLL ; 
 int __blk_mq_poll (struct blk_mq_hw_ctx*,struct request*) ; 
 struct request* blk_mq_tag_to_rq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_qc_t_is_internal (int /*<<< orphan*/ ) ; 
 size_t blk_qc_t_to_queue_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_qc_t_to_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool blk_mq_poll(struct request_queue *q, blk_qc_t cookie)
{
	struct blk_mq_hw_ctx *hctx;
	struct request *rq;

	if (!test_bit(QUEUE_FLAG_POLL, &q->queue_flags))
		return false;

	hctx = q->queue_hw_ctx[blk_qc_t_to_queue_num(cookie)];
	if (!blk_qc_t_is_internal(cookie))
		rq = blk_mq_tag_to_rq(hctx->tags, blk_qc_t_to_tag(cookie));
	else {
		rq = blk_mq_tag_to_rq(hctx->sched_tags, blk_qc_t_to_tag(cookie));
		/*
		 * With scheduling, if the request has completed, we'll
		 * get a NULL return here, as we clear the sched tag when
		 * that happens. The request still remains valid, like always,
		 * so we should be safe with just the NULL check.
		 */
		if (!rq)
			return false;
	}

	return __blk_mq_poll(hctx, rq);
}