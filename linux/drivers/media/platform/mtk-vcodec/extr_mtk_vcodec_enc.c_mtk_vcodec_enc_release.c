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
struct mtk_vcodec_ctx {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_STATE_FREE ; 
 int /*<<< orphan*/  mtk_v4l2_err (char*,int) ; 
 int venc_if_deinit (struct mtk_vcodec_ctx*) ; 

void mtk_vcodec_enc_release(struct mtk_vcodec_ctx *ctx)
{
	int ret = venc_if_deinit(ctx);

	if (ret)
		mtk_v4l2_err("venc_if_deinit failed=%d", ret);

	ctx->state = MTK_STATE_FREE;
}