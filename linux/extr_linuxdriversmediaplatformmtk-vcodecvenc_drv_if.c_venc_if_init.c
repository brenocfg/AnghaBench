#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mtk_vcodec_ctx {TYPE_1__* dev; int /*<<< orphan*/  drv_handle; TYPE_2__* enc_if; } ;
struct TYPE_5__ {int (* init ) (struct mtk_vcodec_ctx*,unsigned long*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  pm; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_PIX_FMT_H264 129 
#define  V4L2_PIX_FMT_VP8 128 
 TYPE_2__* get_h264_enc_comm_if () ; 
 TYPE_2__* get_vp8_enc_comm_if () ; 
 int /*<<< orphan*/  mtk_vcodec_enc_clock_off (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_vcodec_enc_clock_on (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_venc_lock (struct mtk_vcodec_ctx*) ; 
 int /*<<< orphan*/  mtk_venc_unlock (struct mtk_vcodec_ctx*) ; 
 int stub1 (struct mtk_vcodec_ctx*,unsigned long*) ; 

int venc_if_init(struct mtk_vcodec_ctx *ctx, unsigned int fourcc)
{
	int ret = 0;

	switch (fourcc) {
	case V4L2_PIX_FMT_VP8:
		ctx->enc_if = get_vp8_enc_comm_if();
		break;
	case V4L2_PIX_FMT_H264:
		ctx->enc_if = get_h264_enc_comm_if();
		break;
	default:
		return -EINVAL;
	}

	mtk_venc_lock(ctx);
	mtk_vcodec_enc_clock_on(&ctx->dev->pm);
	ret = ctx->enc_if->init(ctx, (unsigned long *)&ctx->drv_handle);
	mtk_vcodec_enc_clock_off(&ctx->dev->pm);
	mtk_venc_unlock(ctx);

	return ret;
}