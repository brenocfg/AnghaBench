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
struct vb2_queue {int /*<<< orphan*/  type; } ;
struct cedrus_dev {TYPE_1__** dec_ops; } ;
struct TYPE_4__ {int pixelformat; } ;
struct cedrus_ctx {size_t current_codec; TYPE_2__ src_fmt; struct cedrus_dev* dev; } ;
struct TYPE_3__ {int (* start ) (struct cedrus_ctx*) ;} ;

/* Variables and functions */
 size_t CEDRUS_CODEC_H264 ; 
 size_t CEDRUS_CODEC_MPEG2 ; 
 int EINVAL ; 
#define  V4L2_PIX_FMT_H264_SLICE 129 
#define  V4L2_PIX_FMT_MPEG2_SLICE 128 
 scalar_t__ V4L2_TYPE_IS_OUTPUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VB2_BUF_STATE_QUEUED ; 
 int /*<<< orphan*/  cedrus_queue_cleanup (struct vb2_queue*,int /*<<< orphan*/ ) ; 
 int stub1 (struct cedrus_ctx*) ; 
 struct cedrus_ctx* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int cedrus_start_streaming(struct vb2_queue *vq, unsigned int count)
{
	struct cedrus_ctx *ctx = vb2_get_drv_priv(vq);
	struct cedrus_dev *dev = ctx->dev;
	int ret = 0;

	switch (ctx->src_fmt.pixelformat) {
	case V4L2_PIX_FMT_MPEG2_SLICE:
		ctx->current_codec = CEDRUS_CODEC_MPEG2;
		break;

	case V4L2_PIX_FMT_H264_SLICE:
		ctx->current_codec = CEDRUS_CODEC_H264;
		break;

	default:
		return -EINVAL;
	}

	if (V4L2_TYPE_IS_OUTPUT(vq->type) &&
	    dev->dec_ops[ctx->current_codec]->start)
		ret = dev->dec_ops[ctx->current_codec]->start(ctx);

	if (ret)
		cedrus_queue_cleanup(vq, VB2_BUF_STATE_QUEUED);

	return ret;
}