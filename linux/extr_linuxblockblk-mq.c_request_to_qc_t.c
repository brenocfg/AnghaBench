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
struct request {int tag; int internal_tag; } ;
struct blk_mq_hw_ctx {int /*<<< orphan*/  queue_num; } ;
typedef  int /*<<< orphan*/  blk_qc_t ;

/* Variables and functions */
 int /*<<< orphan*/  blk_tag_to_qc_t (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static blk_qc_t request_to_qc_t(struct blk_mq_hw_ctx *hctx, struct request *rq)
{
	if (rq->tag != -1)
		return blk_tag_to_qc_t(rq->tag, hctx->queue_num, false);

	return blk_tag_to_qc_t(rq->internal_tag, hctx->queue_num, true);
}