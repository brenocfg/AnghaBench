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
struct coda_ctx {int /*<<< orphan*/  ctrls; TYPE_2__* dev; } ;
struct TYPE_4__ {TYPE_1__* devtype; } ;
struct TYPE_3__ {scalar_t__ product; } ;

/* Variables and functions */
 scalar_t__ CODA_7541 ; 
 scalar_t__ CODA_960 ; 
 scalar_t__ CODA_DX6 ; 
 scalar_t__ CODA_HX4 ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_BITRATE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_CYCLIC_INTRA_REFRESH_MB ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_GOP_SIZE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_CHROMA_QP_INDEX_OFFSET ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_CONSTRAINED_INTRA_PREDICTION ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_I_FRAME_QP ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_LEVEL ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_ALPHA ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_BETA ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_MODE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_MAX_QP ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_MIN_QP ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_PROFILE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_P_FRAME_QP ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_HEADER_MODE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_MPEG4_I_FRAME_QP ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_MPEG4_LEVEL ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_MPEG4_PROFILE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_MPEG4_P_FRAME_QP ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MAX_BYTES ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MAX_MB ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MODE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_VBV_DELAY ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_VBV_SIZE ; 
 int V4L2_MPEG_VIDEO_H264_LEVEL_2_0 ; 
 int V4L2_MPEG_VIDEO_H264_LEVEL_3_0 ; 
 int V4L2_MPEG_VIDEO_H264_LEVEL_3_1 ; 
 int V4L2_MPEG_VIDEO_H264_LEVEL_3_2 ; 
 int V4L2_MPEG_VIDEO_H264_LEVEL_4_0 ; 
 int V4L2_MPEG_VIDEO_H264_LOOP_FILTER_MODE_DISABLED_AT_SLICE_BOUNDARY ; 
 int V4L2_MPEG_VIDEO_H264_LOOP_FILTER_MODE_ENABLED ; 
 int V4L2_MPEG_VIDEO_H264_PROFILE_BASELINE ; 
 int V4L2_MPEG_VIDEO_HEADER_MODE_JOINED_WITH_1ST_FRAME ; 
 int V4L2_MPEG_VIDEO_HEADER_MODE_SEPARATE ; 
 int V4L2_MPEG_VIDEO_MPEG4_LEVEL_5 ; 
 int V4L2_MPEG_VIDEO_MPEG4_PROFILE_SIMPLE ; 
 int V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_MAX_BYTES ; 
 int V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_SINGLE ; 
 int /*<<< orphan*/  coda_ctrl_ops ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std_menu (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void coda_encode_ctrls(struct coda_ctx *ctx)
{
	int max_gop_size = (ctx->dev->devtype->product == CODA_DX6) ? 60 : 99;

	v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_BITRATE, 0, 32767000, 1000, 0);
	v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_GOP_SIZE, 0, max_gop_size, 1, 16);
	v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_H264_I_FRAME_QP, 0, 51, 1, 25);
	v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_H264_P_FRAME_QP, 0, 51, 1, 25);
	if (ctx->dev->devtype->product != CODA_960) {
		v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
			V4L2_CID_MPEG_VIDEO_H264_MIN_QP, 0, 51, 1, 12);
	}
	v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_H264_MAX_QP, 0, 51, 1, 51);
	v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_ALPHA, -6, 6, 1, 0);
	v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_BETA, -6, 6, 1, 0);
	v4l2_ctrl_new_std_menu(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_MODE,
		V4L2_MPEG_VIDEO_H264_LOOP_FILTER_MODE_DISABLED_AT_SLICE_BOUNDARY,
		0x0, V4L2_MPEG_VIDEO_H264_LOOP_FILTER_MODE_ENABLED);
	v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_H264_CONSTRAINED_INTRA_PREDICTION, 0, 1, 1,
		0);
	v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_H264_CHROMA_QP_INDEX_OFFSET, -12, 12, 1, 0);
	v4l2_ctrl_new_std_menu(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_H264_PROFILE,
		V4L2_MPEG_VIDEO_H264_PROFILE_BASELINE, 0x0,
		V4L2_MPEG_VIDEO_H264_PROFILE_BASELINE);
	if (ctx->dev->devtype->product == CODA_HX4 ||
	    ctx->dev->devtype->product == CODA_7541) {
		v4l2_ctrl_new_std_menu(&ctx->ctrls, &coda_ctrl_ops,
			V4L2_CID_MPEG_VIDEO_H264_LEVEL,
			V4L2_MPEG_VIDEO_H264_LEVEL_3_1,
			~((1 << V4L2_MPEG_VIDEO_H264_LEVEL_2_0) |
			  (1 << V4L2_MPEG_VIDEO_H264_LEVEL_3_0) |
			  (1 << V4L2_MPEG_VIDEO_H264_LEVEL_3_1)),
			V4L2_MPEG_VIDEO_H264_LEVEL_3_1);
	}
	if (ctx->dev->devtype->product == CODA_960) {
		v4l2_ctrl_new_std_menu(&ctx->ctrls, &coda_ctrl_ops,
			V4L2_CID_MPEG_VIDEO_H264_LEVEL,
			V4L2_MPEG_VIDEO_H264_LEVEL_4_0,
			~((1 << V4L2_MPEG_VIDEO_H264_LEVEL_2_0) |
			  (1 << V4L2_MPEG_VIDEO_H264_LEVEL_3_0) |
			  (1 << V4L2_MPEG_VIDEO_H264_LEVEL_3_1) |
			  (1 << V4L2_MPEG_VIDEO_H264_LEVEL_3_2) |
			  (1 << V4L2_MPEG_VIDEO_H264_LEVEL_4_0)),
			V4L2_MPEG_VIDEO_H264_LEVEL_4_0);
	}
	v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_MPEG4_I_FRAME_QP, 1, 31, 1, 2);
	v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_MPEG4_P_FRAME_QP, 1, 31, 1, 2);
	v4l2_ctrl_new_std_menu(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_MPEG4_PROFILE,
		V4L2_MPEG_VIDEO_MPEG4_PROFILE_SIMPLE, 0x0,
		V4L2_MPEG_VIDEO_MPEG4_PROFILE_SIMPLE);
	if (ctx->dev->devtype->product == CODA_HX4 ||
	    ctx->dev->devtype->product == CODA_7541 ||
	    ctx->dev->devtype->product == CODA_960) {
		v4l2_ctrl_new_std_menu(&ctx->ctrls, &coda_ctrl_ops,
			V4L2_CID_MPEG_VIDEO_MPEG4_LEVEL,
			V4L2_MPEG_VIDEO_MPEG4_LEVEL_5,
			~(1 << V4L2_MPEG_VIDEO_MPEG4_LEVEL_5),
			V4L2_MPEG_VIDEO_MPEG4_LEVEL_5);
	}
	v4l2_ctrl_new_std_menu(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MODE,
		V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_MAX_BYTES, 0x0,
		V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_SINGLE);
	v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MAX_MB, 1, 0x3fffffff, 1, 1);
	v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MAX_BYTES, 1, 0x3fffffff, 1,
		500);
	v4l2_ctrl_new_std_menu(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_HEADER_MODE,
		V4L2_MPEG_VIDEO_HEADER_MODE_JOINED_WITH_1ST_FRAME,
		(1 << V4L2_MPEG_VIDEO_HEADER_MODE_SEPARATE),
		V4L2_MPEG_VIDEO_HEADER_MODE_JOINED_WITH_1ST_FRAME);
	v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_CYCLIC_INTRA_REFRESH_MB, 0,
		1920 * 1088 / 256, 1, 0);
	v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_VBV_DELAY, 0, 0x7fff, 1, 0);
	/*
	 * The maximum VBV size value is 0x7fffffff bits,
	 * one bit less than 262144 KiB
	 */
	v4l2_ctrl_new_std(&ctx->ctrls, &coda_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_VBV_SIZE, 0, 262144, 1, 0);
}