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
struct gsc_ctx {int state; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int GSC_CTX_ABORT ; 
 int GSC_CTX_STOP_REQ ; 
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  gsc_ctx_state_lock_clear (int,struct gsc_ctx*) ; 
 int gsc_m2m_ctx_stop_req (struct gsc_ctx*) ; 
 int /*<<< orphan*/  gsc_m2m_job_finish (struct gsc_ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __gsc_m2m_job_abort(struct gsc_ctx *ctx)
{
	int ret;

	ret = gsc_m2m_ctx_stop_req(ctx);
	if ((ret == -ETIMEDOUT) || (ctx->state & GSC_CTX_ABORT)) {
		gsc_ctx_state_lock_clear(GSC_CTX_STOP_REQ | GSC_CTX_ABORT, ctx);
		gsc_m2m_job_finish(ctx, VB2_BUF_STATE_ERROR);
	}
}