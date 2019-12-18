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
struct mtk_vcodec_ctx {scalar_t__ state; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 scalar_t__ MTK_STATE_ABORT ; 
 scalar_t__ MTK_STATE_FREE ; 
 int /*<<< orphan*/  mtk_v4l2_debug (int,char*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int m2mops_venc_job_ready(void *m2m_priv)
{
	struct mtk_vcodec_ctx *ctx = m2m_priv;

	if (ctx->state == MTK_STATE_ABORT || ctx->state == MTK_STATE_FREE) {
		mtk_v4l2_debug(3, "[%d]Not ready: state=0x%x.",
			       ctx->id, ctx->state);
		return 0;
	}

	return 1;
}