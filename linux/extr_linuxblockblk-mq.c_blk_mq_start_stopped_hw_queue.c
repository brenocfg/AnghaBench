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
struct blk_mq_hw_ctx {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_MQ_S_STOPPED ; 
 int /*<<< orphan*/  blk_mq_hctx_stopped (struct blk_mq_hw_ctx*) ; 
 int /*<<< orphan*/  blk_mq_run_hw_queue (struct blk_mq_hw_ctx*,int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void blk_mq_start_stopped_hw_queue(struct blk_mq_hw_ctx *hctx, bool async)
{
	if (!blk_mq_hctx_stopped(hctx))
		return;

	clear_bit(BLK_MQ_S_STOPPED, &hctx->state);
	blk_mq_run_hw_queue(hctx, async);
}