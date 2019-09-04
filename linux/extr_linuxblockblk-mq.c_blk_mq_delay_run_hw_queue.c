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
struct blk_mq_hw_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __blk_mq_delay_run_hw_queue (struct blk_mq_hw_ctx*,int,unsigned long) ; 

void blk_mq_delay_run_hw_queue(struct blk_mq_hw_ctx *hctx, unsigned long msecs)
{
	__blk_mq_delay_run_hw_queue(hctx, true, msecs);
}