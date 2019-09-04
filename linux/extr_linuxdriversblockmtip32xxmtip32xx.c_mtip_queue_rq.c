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
struct request {int dummy; } ;
struct blk_mq_queue_data {struct request* rq; } ;
struct blk_mq_hw_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  BLK_STS_OK ; 
 int /*<<< orphan*/  BLK_STS_RESOURCE ; 
 int /*<<< orphan*/  blk_mq_start_request (struct request*) ; 
 scalar_t__ blk_rq_is_passthrough (struct request*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mtip_check_unal_depth (struct blk_mq_hw_ctx*,struct request*) ; 
 int /*<<< orphan*/  mtip_init_cmd_header (struct request*) ; 
 int /*<<< orphan*/  mtip_issue_reserved_cmd (struct blk_mq_hw_ctx*,struct request*) ; 
 int mtip_submit_request (struct blk_mq_hw_ctx*,struct request*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static blk_status_t mtip_queue_rq(struct blk_mq_hw_ctx *hctx,
			 const struct blk_mq_queue_data *bd)
{
	struct request *rq = bd->rq;
	int ret;

	mtip_init_cmd_header(rq);

	if (blk_rq_is_passthrough(rq))
		return mtip_issue_reserved_cmd(hctx, rq);

	if (unlikely(mtip_check_unal_depth(hctx, rq)))
		return BLK_STS_RESOURCE;

	blk_mq_start_request(rq);

	ret = mtip_submit_request(hctx, rq);
	if (likely(!ret))
		return BLK_STS_OK;
	return BLK_STS_IOERR;
}