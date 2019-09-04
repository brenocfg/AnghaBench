#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mtk_vcodec_ctx {scalar_t__ drv_handle; TYPE_1__* dev; TYPE_2__* enc_if; } ;
struct TYPE_4__ {int (* deinit ) (scalar_t__) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtk_vcodec_enc_clock_off (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_vcodec_enc_clock_on (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_venc_lock (struct mtk_vcodec_ctx*) ; 
 int /*<<< orphan*/  mtk_venc_unlock (struct mtk_vcodec_ctx*) ; 
 int stub1 (scalar_t__) ; 

int venc_if_deinit(struct mtk_vcodec_ctx *ctx)
{
	int ret = 0;

	if (ctx->drv_handle == 0)
		return 0;

	mtk_venc_lock(ctx);
	mtk_vcodec_enc_clock_on(&ctx->dev->pm);
	ret = ctx->enc_if->deinit(ctx->drv_handle);
	mtk_vcodec_enc_clock_off(&ctx->dev->pm);
	mtk_venc_unlock(ctx);

	ctx->drv_handle = 0;

	return ret;
}