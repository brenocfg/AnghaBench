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
struct blk_mq_hw_ctx {int /*<<< orphan*/  state; int /*<<< orphan*/  run_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_MQ_S_STOPPED ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void blk_mq_stop_hw_queue(struct blk_mq_hw_ctx *hctx)
{
	cancel_delayed_work(&hctx->run_work);

	set_bit(BLK_MQ_S_STOPPED, &hctx->state);
}