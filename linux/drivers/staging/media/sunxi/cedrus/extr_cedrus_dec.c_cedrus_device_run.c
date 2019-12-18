#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct media_request {int dummy; } ;
struct TYPE_15__ {void* sps; void* slice_params; void* scaling_matrix; void* pps; void* decode_params; } ;
struct TYPE_14__ {void* quantization; void* slice_params; } ;
struct cedrus_run {int /*<<< orphan*/  dst; TYPE_8__* src; TYPE_6__ h264; TYPE_5__ mpeg2; } ;
struct cedrus_dev {TYPE_7__** dec_ops; } ;
struct TYPE_13__ {int pixelformat; } ;
struct TYPE_10__ {int /*<<< orphan*/  m2m_ctx; } ;
struct cedrus_ctx {size_t current_codec; int /*<<< orphan*/  hdl; TYPE_4__ src_fmt; TYPE_1__ fh; struct cedrus_dev* dev; } ;
struct TYPE_11__ {struct media_request* req; } ;
struct TYPE_12__ {TYPE_2__ req_obj; } ;
struct TYPE_17__ {TYPE_3__ vb2_buf; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* trigger ) (struct cedrus_ctx*) ;int /*<<< orphan*/  (* setup ) (struct cedrus_ctx*,struct cedrus_run*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_DECODE_PARAMS ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_PPS ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_SCALING_MATRIX ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_SLICE_PARAMS ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_SPS ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_MPEG2_QUANTIZATION ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_MPEG2_SLICE_PARAMS ; 
#define  V4L2_PIX_FMT_H264_SLICE 129 
#define  V4L2_PIX_FMT_MPEG2_SLICE 128 
 void* cedrus_find_control_data (struct cedrus_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct cedrus_ctx*,struct cedrus_run*) ; 
 int /*<<< orphan*/  stub2 (struct cedrus_ctx*) ; 
 int /*<<< orphan*/  v4l2_ctrl_request_complete (struct media_request*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_request_setup (struct media_request*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_copy_metadata (TYPE_8__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_m2m_next_dst_buf (int /*<<< orphan*/ ) ; 
 TYPE_8__* v4l2_m2m_next_src_buf (int /*<<< orphan*/ ) ; 

void cedrus_device_run(void *priv)
{
	struct cedrus_ctx *ctx = priv;
	struct cedrus_dev *dev = ctx->dev;
	struct cedrus_run run = {};
	struct media_request *src_req;

	run.src = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
	run.dst = v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);

	/* Apply request(s) controls if needed. */
	src_req = run.src->vb2_buf.req_obj.req;

	if (src_req)
		v4l2_ctrl_request_setup(src_req, &ctx->hdl);

	switch (ctx->src_fmt.pixelformat) {
	case V4L2_PIX_FMT_MPEG2_SLICE:
		run.mpeg2.slice_params = cedrus_find_control_data(ctx,
			V4L2_CID_MPEG_VIDEO_MPEG2_SLICE_PARAMS);
		run.mpeg2.quantization = cedrus_find_control_data(ctx,
			V4L2_CID_MPEG_VIDEO_MPEG2_QUANTIZATION);
		break;

	case V4L2_PIX_FMT_H264_SLICE:
		run.h264.decode_params = cedrus_find_control_data(ctx,
			V4L2_CID_MPEG_VIDEO_H264_DECODE_PARAMS);
		run.h264.pps = cedrus_find_control_data(ctx,
			V4L2_CID_MPEG_VIDEO_H264_PPS);
		run.h264.scaling_matrix = cedrus_find_control_data(ctx,
			V4L2_CID_MPEG_VIDEO_H264_SCALING_MATRIX);
		run.h264.slice_params = cedrus_find_control_data(ctx,
			V4L2_CID_MPEG_VIDEO_H264_SLICE_PARAMS);
		run.h264.sps = cedrus_find_control_data(ctx,
			V4L2_CID_MPEG_VIDEO_H264_SPS);
		break;

	default:
		break;
	}

	v4l2_m2m_buf_copy_metadata(run.src, run.dst, true);

	dev->dec_ops[ctx->current_codec]->setup(ctx, &run);

	/* Complete request(s) controls if needed. */

	if (src_req)
		v4l2_ctrl_request_complete(src_req, &ctx->hdl);

	dev->dec_ops[ctx->current_codec]->trigger(ctx);
}