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
 int /*<<< orphan*/  vdec_if_deinit (struct mtk_vcodec_ctx*) ; 

void mtk_vcodec_dec_release(struct mtk_vcodec_ctx *ctx)
{
	vdec_if_deinit(ctx);
	ctx->state = MTK_STATE_FREE;
}