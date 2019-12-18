#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int error; } ;
struct venus_inst {TYPE_1__ ctrl_handler; } ;

/* Variables and functions */
 int AT_SLICE_BOUNDARY ; 
 int BITRATE_DEFAULT ; 
 int BITRATE_DEFAULT_PEAK ; 
 int BITRATE_MAX ; 
 int BITRATE_MIN ; 
 int BITRATE_STEP ; 
 int INTRA_REFRESH_MBS_MAX ; 
 int SLICE_BYTE_SIZE_MAX ; 
 int SLICE_BYTE_SIZE_MIN ; 
 int SLICE_MB_SIZE_MAX ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_BITRATE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_BITRATE_MODE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_BITRATE_PEAK ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_B_FRAMES ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_CYCLIC_INTRA_REFRESH_MB ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_FORCE_KEY_FRAME ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_GOP_SIZE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_B_FRAME_QP ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_ENTROPY_MODE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_I_FRAME_QP ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_I_PERIOD ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_LEVEL ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_ALPHA ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_BETA ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_MODE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_MAX_QP ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_MIN_QP ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_PROFILE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_P_FRAME_QP ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_HEADER_MODE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_HEVC_LEVEL ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_HEVC_PROFILE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_MPEG4_LEVEL ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_MPEG4_PROFILE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MAX_BYTES ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MAX_MB ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MODE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_VP8_PROFILE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_VPX_MAX_QP ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_VPX_MIN_QP ; 
 int V4L2_MPEG_VIDEO_BITRATE_MODE_CBR ; 
 int V4L2_MPEG_VIDEO_BITRATE_MODE_VBR ; 
 int V4L2_MPEG_VIDEO_H264_ENTROPY_MODE_CABAC ; 
 int V4L2_MPEG_VIDEO_H264_ENTROPY_MODE_CAVLC ; 
 int V4L2_MPEG_VIDEO_H264_LEVEL_1_0 ; 
 int V4L2_MPEG_VIDEO_H264_LEVEL_5_1 ; 
 int V4L2_MPEG_VIDEO_H264_LOOP_FILTER_MODE_DISABLED ; 
 int V4L2_MPEG_VIDEO_H264_PROFILE_BASELINE ; 
 int V4L2_MPEG_VIDEO_H264_PROFILE_CONSTRAINED_BASELINE ; 
 int V4L2_MPEG_VIDEO_H264_PROFILE_HIGH ; 
 int V4L2_MPEG_VIDEO_H264_PROFILE_MAIN ; 
 int V4L2_MPEG_VIDEO_H264_PROFILE_MULTIVIEW_HIGH ; 
 int V4L2_MPEG_VIDEO_H264_PROFILE_STEREO_HIGH ; 
 int V4L2_MPEG_VIDEO_HEADER_MODE_JOINED_WITH_1ST_FRAME ; 
 int V4L2_MPEG_VIDEO_HEADER_MODE_SEPARATE ; 
 int V4L2_MPEG_VIDEO_HEVC_LEVEL_1 ; 
 int V4L2_MPEG_VIDEO_HEVC_LEVEL_6_2 ; 
 int V4L2_MPEG_VIDEO_HEVC_PROFILE_MAIN ; 
 int V4L2_MPEG_VIDEO_HEVC_PROFILE_MAIN_10 ; 
 int V4L2_MPEG_VIDEO_HEVC_PROFILE_MAIN_STILL_PICTURE ; 
 int V4L2_MPEG_VIDEO_MPEG4_LEVEL_0 ; 
 int V4L2_MPEG_VIDEO_MPEG4_LEVEL_5 ; 
 int V4L2_MPEG_VIDEO_MPEG4_PROFILE_ADVANCED_CODING_EFFICIENCY ; 
 int V4L2_MPEG_VIDEO_MPEG4_PROFILE_ADVANCED_SIMPLE ; 
 int V4L2_MPEG_VIDEO_MPEG4_PROFILE_SIMPLE ; 
 int V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_MAX_BYTES ; 
 int V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_SINGLE ; 
 int V4L2_MPEG_VIDEO_VP8_PROFILE_0 ; 
 int V4L2_MPEG_VIDEO_VP8_PROFILE_3 ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (TYPE_1__*) ; 
 int v4l2_ctrl_handler_init (TYPE_1__*,int) ; 
 int v4l2_ctrl_handler_setup (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std_menu (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  venc_ctrl_ops ; 

int venc_ctrl_init(struct venus_inst *inst)
{
	int ret;

	ret = v4l2_ctrl_handler_init(&inst->ctrl_handler, 30);
	if (ret)
		return ret;

	v4l2_ctrl_new_std_menu(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_BITRATE_MODE,
		V4L2_MPEG_VIDEO_BITRATE_MODE_CBR,
		~((1 << V4L2_MPEG_VIDEO_BITRATE_MODE_VBR) |
		  (1 << V4L2_MPEG_VIDEO_BITRATE_MODE_CBR)),
		V4L2_MPEG_VIDEO_BITRATE_MODE_VBR);

	v4l2_ctrl_new_std_menu(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_H264_ENTROPY_MODE,
		V4L2_MPEG_VIDEO_H264_ENTROPY_MODE_CABAC,
		0, V4L2_MPEG_VIDEO_H264_ENTROPY_MODE_CAVLC);

	v4l2_ctrl_new_std_menu(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_MPEG4_PROFILE,
		V4L2_MPEG_VIDEO_MPEG4_PROFILE_ADVANCED_CODING_EFFICIENCY,
		~((1 << V4L2_MPEG_VIDEO_MPEG4_PROFILE_SIMPLE) |
		  (1 << V4L2_MPEG_VIDEO_MPEG4_PROFILE_ADVANCED_SIMPLE)),
		V4L2_MPEG_VIDEO_MPEG4_PROFILE_SIMPLE);

	v4l2_ctrl_new_std_menu(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_MPEG4_LEVEL,
		V4L2_MPEG_VIDEO_MPEG4_LEVEL_5,
		0, V4L2_MPEG_VIDEO_MPEG4_LEVEL_0);

	v4l2_ctrl_new_std_menu(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_HEVC_PROFILE,
		V4L2_MPEG_VIDEO_HEVC_PROFILE_MAIN_10,
		~((1 << V4L2_MPEG_VIDEO_HEVC_PROFILE_MAIN) |
		  (1 << V4L2_MPEG_VIDEO_HEVC_PROFILE_MAIN_STILL_PICTURE) |
		  (1 << V4L2_MPEG_VIDEO_HEVC_PROFILE_MAIN_10)),
		V4L2_MPEG_VIDEO_HEVC_PROFILE_MAIN);

	v4l2_ctrl_new_std_menu(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_HEVC_LEVEL,
		V4L2_MPEG_VIDEO_HEVC_LEVEL_6_2,
		0, V4L2_MPEG_VIDEO_HEVC_LEVEL_1);

	v4l2_ctrl_new_std_menu(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_H264_PROFILE,
		V4L2_MPEG_VIDEO_H264_PROFILE_MULTIVIEW_HIGH,
		~((1 << V4L2_MPEG_VIDEO_H264_PROFILE_BASELINE) |
		  (1 << V4L2_MPEG_VIDEO_H264_PROFILE_CONSTRAINED_BASELINE) |
		  (1 << V4L2_MPEG_VIDEO_H264_PROFILE_MAIN) |
		  (1 << V4L2_MPEG_VIDEO_H264_PROFILE_HIGH) |
		  (1 << V4L2_MPEG_VIDEO_H264_PROFILE_STEREO_HIGH) |
		  (1 << V4L2_MPEG_VIDEO_H264_PROFILE_MULTIVIEW_HIGH)),
		V4L2_MPEG_VIDEO_H264_PROFILE_HIGH);

	v4l2_ctrl_new_std_menu(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_H264_LEVEL,
		V4L2_MPEG_VIDEO_H264_LEVEL_5_1,
		0, V4L2_MPEG_VIDEO_H264_LEVEL_1_0);

	v4l2_ctrl_new_std_menu(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_MODE,
		AT_SLICE_BOUNDARY,
		0, V4L2_MPEG_VIDEO_H264_LOOP_FILTER_MODE_DISABLED);

	v4l2_ctrl_new_std_menu(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_HEADER_MODE,
		V4L2_MPEG_VIDEO_HEADER_MODE_JOINED_WITH_1ST_FRAME,
		1 << V4L2_MPEG_VIDEO_HEADER_MODE_JOINED_WITH_1ST_FRAME,
		V4L2_MPEG_VIDEO_HEADER_MODE_SEPARATE);

	v4l2_ctrl_new_std_menu(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MODE,
		V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_MAX_BYTES,
		0, V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_SINGLE);

	v4l2_ctrl_new_std_menu(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_VP8_PROFILE,
		V4L2_MPEG_VIDEO_VP8_PROFILE_3,
		0, V4L2_MPEG_VIDEO_VP8_PROFILE_0);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_BITRATE, BITRATE_MIN, BITRATE_MAX,
		BITRATE_STEP, BITRATE_DEFAULT);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_BITRATE_PEAK, BITRATE_MIN, BITRATE_MAX,
		BITRATE_STEP, BITRATE_DEFAULT_PEAK);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_H264_I_FRAME_QP, 1, 51, 1, 26);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_H264_P_FRAME_QP, 1, 51, 1, 28);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_H264_B_FRAME_QP, 1, 51, 1, 30);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_H264_MIN_QP, 1, 51, 1, 1);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_H264_MAX_QP, 1, 51, 1, 51);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MAX_BYTES, SLICE_BYTE_SIZE_MIN,
		SLICE_BYTE_SIZE_MAX, 1, SLICE_BYTE_SIZE_MIN);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MAX_MB, 1,
		SLICE_MB_SIZE_MAX, 1, 1);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_ALPHA, -6, 6, 1, 0);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_BETA, -6, 6, 1, 0);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_CYCLIC_INTRA_REFRESH_MB,
		0, INTRA_REFRESH_MBS_MAX, 1, 0);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_GOP_SIZE, 0, (1 << 16) - 1, 1, 30);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_VPX_MIN_QP, 1, 128, 1, 1);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_VPX_MAX_QP, 1, 128, 1, 128);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_B_FRAMES, 0, 4, 1, 0);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
		V4L2_CID_MPEG_VIDEO_H264_I_PERIOD, 0, (1 << 16) - 1, 1, 0);

	v4l2_ctrl_new_std(&inst->ctrl_handler, &venc_ctrl_ops,
			  V4L2_CID_MPEG_VIDEO_FORCE_KEY_FRAME, 0, 0, 0, 0);

	ret = inst->ctrl_handler.error;
	if (ret)
		goto err;

	ret = v4l2_ctrl_handler_setup(&inst->ctrl_handler);
	if (ret)
		goto err;

	return 0;
err:
	v4l2_ctrl_handler_free(&inst->ctrl_handler);
	return ret;
}