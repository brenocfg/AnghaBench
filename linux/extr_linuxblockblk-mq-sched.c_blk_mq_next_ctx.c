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
struct blk_mq_hw_ctx {unsigned int nr_ctx; struct blk_mq_ctx** ctxs; } ;
struct blk_mq_ctx {unsigned int index_hw; } ;

/* Variables and functions */

__attribute__((used)) static struct blk_mq_ctx *blk_mq_next_ctx(struct blk_mq_hw_ctx *hctx,
					  struct blk_mq_ctx *ctx)
{
	unsigned idx = ctx->index_hw;

	if (++idx == hctx->nr_ctx)
		idx = 0;

	return hctx->ctxs[idx];
}