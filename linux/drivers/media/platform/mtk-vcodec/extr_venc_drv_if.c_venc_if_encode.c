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
struct venc_frm_buf {int dummy; } ;
struct venc_done_result {int dummy; } ;
struct mtk_vcodec_mem {int dummy; } ;
struct mtk_vcodec_ctx {TYPE_2__* dev; int /*<<< orphan*/  drv_handle; TYPE_1__* enc_if; } ;
typedef  enum venc_start_opt { ____Placeholder_venc_start_opt } venc_start_opt ;
struct TYPE_4__ {int /*<<< orphan*/  irqlock; struct mtk_vcodec_ctx* curr_ctx; int /*<<< orphan*/  pm; } ;
struct TYPE_3__ {int (* encode ) (int /*<<< orphan*/ ,int,struct venc_frm_buf*,struct mtk_vcodec_mem*,struct venc_done_result*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mtk_vcodec_enc_clock_off (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_vcodec_enc_clock_on (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_venc_lock (struct mtk_vcodec_ctx*) ; 
 int /*<<< orphan*/  mtk_venc_unlock (struct mtk_vcodec_ctx*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (int /*<<< orphan*/ ,int,struct venc_frm_buf*,struct mtk_vcodec_mem*,struct venc_done_result*) ; 

int venc_if_encode(struct mtk_vcodec_ctx *ctx,
		   enum venc_start_opt opt, struct venc_frm_buf *frm_buf,
		   struct mtk_vcodec_mem *bs_buf,
		   struct venc_done_result *result)
{
	int ret = 0;
	unsigned long flags;

	mtk_venc_lock(ctx);

	spin_lock_irqsave(&ctx->dev->irqlock, flags);
	ctx->dev->curr_ctx = ctx;
	spin_unlock_irqrestore(&ctx->dev->irqlock, flags);

	mtk_vcodec_enc_clock_on(&ctx->dev->pm);
	ret = ctx->enc_if->encode(ctx->drv_handle, opt, frm_buf,
				  bs_buf, result);
	mtk_vcodec_enc_clock_off(&ctx->dev->pm);

	spin_lock_irqsave(&ctx->dev->irqlock, flags);
	ctx->dev->curr_ctx = NULL;
	spin_unlock_irqrestore(&ctx->dev->irqlock, flags);

	mtk_venc_unlock(ctx);
	return ret;
}