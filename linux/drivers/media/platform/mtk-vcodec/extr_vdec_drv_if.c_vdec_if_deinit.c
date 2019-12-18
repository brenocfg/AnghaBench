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
struct mtk_vcodec_ctx {int /*<<< orphan*/ * drv_handle; TYPE_2__* dev; TYPE_1__* dec_if; } ;
struct TYPE_4__ {int /*<<< orphan*/  pm; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* deinit ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mtk_vcodec_dec_clock_off (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_vcodec_dec_clock_on (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_vdec_lock (struct mtk_vcodec_ctx*) ; 
 int /*<<< orphan*/  mtk_vdec_unlock (struct mtk_vcodec_ctx*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

void vdec_if_deinit(struct mtk_vcodec_ctx *ctx)
{
	if (!ctx->drv_handle)
		return;

	mtk_vdec_lock(ctx);
	mtk_vcodec_dec_clock_on(&ctx->dev->pm);
	ctx->dec_if->deinit(ctx->drv_handle);
	mtk_vcodec_dec_clock_off(&ctx->dev->pm);
	mtk_vdec_unlock(ctx);

	ctx->drv_handle = NULL;
}