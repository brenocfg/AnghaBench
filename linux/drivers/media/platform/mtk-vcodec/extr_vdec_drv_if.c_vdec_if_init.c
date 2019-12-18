#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mtk_vcodec_ctx {TYPE_1__* dev; TYPE_2__* dec_if; } ;
struct TYPE_6__ {int (* init ) (struct mtk_vcodec_ctx*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  pm; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_PIX_FMT_H264 130 
#define  V4L2_PIX_FMT_VP8 129 
#define  V4L2_PIX_FMT_VP9 128 
 int /*<<< orphan*/  mtk_vcodec_dec_clock_off (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_vcodec_dec_clock_on (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_vdec_lock (struct mtk_vcodec_ctx*) ; 
 int /*<<< orphan*/  mtk_vdec_unlock (struct mtk_vcodec_ctx*) ; 
 int stub1 (struct mtk_vcodec_ctx*) ; 
 TYPE_2__ vdec_h264_if ; 
 TYPE_2__ vdec_vp8_if ; 
 TYPE_2__ vdec_vp9_if ; 

int vdec_if_init(struct mtk_vcodec_ctx *ctx, unsigned int fourcc)
{
	int ret = 0;

	switch (fourcc) {
	case V4L2_PIX_FMT_H264:
		ctx->dec_if = &vdec_h264_if;
		break;
	case V4L2_PIX_FMT_VP8:
		ctx->dec_if = &vdec_vp8_if;
		break;
	case V4L2_PIX_FMT_VP9:
		ctx->dec_if = &vdec_vp9_if;
		break;
	default:
		return -EINVAL;
	}

	mtk_vdec_lock(ctx);
	mtk_vcodec_dec_clock_on(&ctx->dev->pm);
	ret = ctx->dec_if->init(ctx);
	mtk_vcodec_dec_clock_off(&ctx->dev->pm);
	mtk_vdec_unlock(ctx);

	return ret;
}