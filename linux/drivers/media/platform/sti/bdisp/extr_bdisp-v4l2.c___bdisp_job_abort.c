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
struct bdisp_ctx {int state; } ;

/* Variables and functions */
 int BDISP_CTX_ABORT ; 
 int BDISP_CTX_STOP_REQ ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  bdisp_ctx_state_lock_clear (int,struct bdisp_ctx*) ; 
 int bdisp_ctx_stop_req (struct bdisp_ctx*) ; 
 int /*<<< orphan*/  bdisp_job_finish (struct bdisp_ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __bdisp_job_abort(struct bdisp_ctx *ctx)
{
	int ret;

	ret = bdisp_ctx_stop_req(ctx);
	if ((ret == -ETIMEDOUT) || (ctx->state & BDISP_CTX_ABORT)) {
		bdisp_ctx_state_lock_clear(BDISP_CTX_STOP_REQ | BDISP_CTX_ABORT,
					   ctx);
		bdisp_job_finish(ctx, VB2_BUF_STATE_ERROR);
	}
}