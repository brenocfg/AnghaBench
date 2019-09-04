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
typedef  int /*<<< orphan*/  wait_queue_head_t ;
struct mtk_vcodec_ctx {scalar_t__ int_type; int /*<<< orphan*/  int_cond; int /*<<< orphan*/  type; int /*<<< orphan*/  id; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 long ERESTARTSYS ; 
 long msecs_to_jiffies (unsigned int) ; 
 int /*<<< orphan*/  mtk_v4l2_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int,scalar_t__,...) ; 
 long wait_event_interruptible_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 

int mtk_vcodec_wait_for_done_ctx(struct mtk_vcodec_ctx  *ctx, int command,
				 unsigned int timeout_ms)
{
	wait_queue_head_t *waitqueue;
	long timeout_jiff, ret;
	int status = 0;

	waitqueue = (wait_queue_head_t *)&ctx->queue;
	timeout_jiff = msecs_to_jiffies(timeout_ms);

	ret = wait_event_interruptible_timeout(*waitqueue,
				ctx->int_cond,
				timeout_jiff);

	if (!ret) {
		status = -1;	/* timeout */
		mtk_v4l2_err("[%d] cmd=%d, ctx->type=%d, wait_event_interruptible_timeout time=%ums out %d %d!",
				ctx->id, ctx->type, command, timeout_ms,
				ctx->int_cond, ctx->int_type);
	} else if (-ERESTARTSYS == ret) {
		mtk_v4l2_err("[%d] cmd=%d, ctx->type=%d, wait_event_interruptible_timeout interrupted by a signal %d %d",
				ctx->id, ctx->type, command, ctx->int_cond,
				ctx->int_type);
		status = -1;
	}

	ctx->int_cond = 0;
	ctx->int_type = 0;

	return status;
}