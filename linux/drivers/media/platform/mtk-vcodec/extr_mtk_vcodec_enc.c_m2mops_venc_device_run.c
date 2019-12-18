#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mtk_vcodec_ctx {scalar_t__ state; int /*<<< orphan*/  encode_work; TYPE_3__* dev; TYPE_2__* q_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  encode_workqueue; } ;
struct TYPE_5__ {TYPE_1__* fmt; } ;
struct TYPE_4__ {scalar_t__ fourcc; } ;

/* Variables and functions */
 size_t MTK_Q_DATA_DST ; 
 scalar_t__ MTK_STATE_HEADER ; 
 scalar_t__ V4L2_PIX_FMT_H264 ; 
 int /*<<< orphan*/  mtk_venc_encode_header (struct mtk_vcodec_ctx*) ; 
 int /*<<< orphan*/  mtk_venc_param_change (struct mtk_vcodec_ctx*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void m2mops_venc_device_run(void *priv)
{
	struct mtk_vcodec_ctx *ctx = priv;

	if ((ctx->q_data[MTK_Q_DATA_DST].fmt->fourcc == V4L2_PIX_FMT_H264) &&
	    (ctx->state != MTK_STATE_HEADER)) {
		/* encode h264 sps/pps header */
		mtk_venc_encode_header(ctx);
		queue_work(ctx->dev->encode_workqueue, &ctx->encode_work);
		return;
	}

	mtk_venc_param_change(ctx);
	queue_work(ctx->dev->encode_workqueue, &ctx->encode_work);
}