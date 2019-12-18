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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {int /*<<< orphan*/  hevc; int /*<<< orphan*/  h264; int /*<<< orphan*/  mpeg4; } ;
struct TYPE_5__ {int /*<<< orphan*/  vpx; int /*<<< orphan*/  hevc; int /*<<< orphan*/  h264; int /*<<< orphan*/  mpeg4; } ;
struct venc_controls {int /*<<< orphan*/  num_b_frames; int /*<<< orphan*/  num_p_frames; int /*<<< orphan*/  gop_size; int /*<<< orphan*/  vp8_max_qp; int /*<<< orphan*/  vp8_min_qp; int /*<<< orphan*/  h264_i_period; int /*<<< orphan*/  header_mode; int /*<<< orphan*/  h264_loop_filter_mode; int /*<<< orphan*/  h264_loop_filter_beta; int /*<<< orphan*/  h264_loop_filter_alpha; int /*<<< orphan*/  multi_slice_max_mb; int /*<<< orphan*/  multi_slice_max_bytes; int /*<<< orphan*/  multi_slice_mode; int /*<<< orphan*/  h264_max_qp; int /*<<< orphan*/  h264_min_qp; int /*<<< orphan*/  h264_b_qp; int /*<<< orphan*/  h264_p_qp; int /*<<< orphan*/  h264_i_qp; TYPE_3__ level; TYPE_2__ profile; int /*<<< orphan*/  h264_entropy_mode; int /*<<< orphan*/  bitrate_peak; int /*<<< orphan*/  bitrate; int /*<<< orphan*/  bitrate_mode; } ;
struct TYPE_4__ {struct venc_controls enc; } ;
struct venus_inst {int /*<<< orphan*/  lock; int /*<<< orphan*/  streamon_cap; int /*<<< orphan*/  streamon_out; TYPE_1__ controls; } ;
struct v4l2_ctrl {int id; int /*<<< orphan*/  val; } ;
struct hfi_enable {int enable; int /*<<< orphan*/  layer_id; int /*<<< orphan*/  bitrate; } ;
struct hfi_bitrate {int enable; int /*<<< orphan*/  layer_id; int /*<<< orphan*/  bitrate; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HFI_PROPERTY_CONFIG_VENC_REQUEST_SYNC_FRAME ; 
 int /*<<< orphan*/  HFI_PROPERTY_CONFIG_VENC_TARGET_BITRATE ; 
#define  V4L2_CID_MPEG_VIDEO_BITRATE 157 
#define  V4L2_CID_MPEG_VIDEO_BITRATE_MODE 156 
#define  V4L2_CID_MPEG_VIDEO_BITRATE_PEAK 155 
#define  V4L2_CID_MPEG_VIDEO_B_FRAMES 154 
#define  V4L2_CID_MPEG_VIDEO_CYCLIC_INTRA_REFRESH_MB 153 
#define  V4L2_CID_MPEG_VIDEO_FORCE_KEY_FRAME 152 
#define  V4L2_CID_MPEG_VIDEO_GOP_SIZE 151 
#define  V4L2_CID_MPEG_VIDEO_H264_B_FRAME_QP 150 
#define  V4L2_CID_MPEG_VIDEO_H264_ENTROPY_MODE 149 
#define  V4L2_CID_MPEG_VIDEO_H264_I_FRAME_QP 148 
#define  V4L2_CID_MPEG_VIDEO_H264_I_PERIOD 147 
#define  V4L2_CID_MPEG_VIDEO_H264_LEVEL 146 
#define  V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_ALPHA 145 
#define  V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_BETA 144 
#define  V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_MODE 143 
#define  V4L2_CID_MPEG_VIDEO_H264_MAX_QP 142 
#define  V4L2_CID_MPEG_VIDEO_H264_MIN_QP 141 
#define  V4L2_CID_MPEG_VIDEO_H264_PROFILE 140 
#define  V4L2_CID_MPEG_VIDEO_H264_P_FRAME_QP 139 
#define  V4L2_CID_MPEG_VIDEO_HEADER_MODE 138 
#define  V4L2_CID_MPEG_VIDEO_HEVC_LEVEL 137 
#define  V4L2_CID_MPEG_VIDEO_HEVC_PROFILE 136 
#define  V4L2_CID_MPEG_VIDEO_MPEG4_LEVEL 135 
#define  V4L2_CID_MPEG_VIDEO_MPEG4_PROFILE 134 
#define  V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MAX_BYTES 133 
#define  V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MAX_MB 132 
#define  V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MODE 131 
#define  V4L2_CID_MPEG_VIDEO_VP8_PROFILE 130 
#define  V4L2_CID_MPEG_VIDEO_VPX_MAX_QP 129 
#define  V4L2_CID_MPEG_VIDEO_VPX_MIN_QP 128 
 struct venus_inst* ctrl_to_inst (struct v4l2_ctrl*) ; 
 int hfi_session_set_property (struct venus_inst*,int /*<<< orphan*/ ,struct hfi_enable*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int venc_calc_bpframes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int venc_op_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct venus_inst *inst = ctrl_to_inst(ctrl);
	struct venc_controls *ctr = &inst->controls.enc;
	struct hfi_enable en = { .enable = 1 };
	struct hfi_bitrate brate;
	u32 bframes;
	u32 ptype;
	int ret;

	switch (ctrl->id) {
	case V4L2_CID_MPEG_VIDEO_BITRATE_MODE:
		ctr->bitrate_mode = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_BITRATE:
		ctr->bitrate = ctrl->val;
		mutex_lock(&inst->lock);
		if (inst->streamon_out && inst->streamon_cap) {
			ptype = HFI_PROPERTY_CONFIG_VENC_TARGET_BITRATE;
			brate.bitrate = ctr->bitrate;
			brate.layer_id = 0;

			ret = hfi_session_set_property(inst, ptype, &brate);
			if (ret) {
				mutex_unlock(&inst->lock);
				return ret;
			}
		}
		mutex_unlock(&inst->lock);
		break;
	case V4L2_CID_MPEG_VIDEO_BITRATE_PEAK:
		ctr->bitrate_peak = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_H264_ENTROPY_MODE:
		ctr->h264_entropy_mode = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_MPEG4_PROFILE:
		ctr->profile.mpeg4 = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_H264_PROFILE:
		ctr->profile.h264 = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_PROFILE:
		ctr->profile.hevc = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_VP8_PROFILE:
		ctr->profile.vpx = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_MPEG4_LEVEL:
		ctr->level.mpeg4 = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_H264_LEVEL:
		ctr->level.h264 = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_LEVEL:
		ctr->level.hevc = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_H264_I_FRAME_QP:
		ctr->h264_i_qp = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_H264_P_FRAME_QP:
		ctr->h264_p_qp = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_H264_B_FRAME_QP:
		ctr->h264_b_qp = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_H264_MIN_QP:
		ctr->h264_min_qp = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_H264_MAX_QP:
		ctr->h264_max_qp = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MODE:
		ctr->multi_slice_mode = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MAX_BYTES:
		ctr->multi_slice_max_bytes = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MAX_MB:
		ctr->multi_slice_max_mb = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_ALPHA:
		ctr->h264_loop_filter_alpha = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_BETA:
		ctr->h264_loop_filter_beta = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_MODE:
		ctr->h264_loop_filter_mode = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEADER_MODE:
		ctr->header_mode = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_CYCLIC_INTRA_REFRESH_MB:
		break;
	case V4L2_CID_MPEG_VIDEO_GOP_SIZE:
		ret = venc_calc_bpframes(ctrl->val, ctr->num_b_frames, &bframes,
					 &ctr->num_p_frames);
		if (ret)
			return ret;

		ctr->gop_size = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_H264_I_PERIOD:
		ctr->h264_i_period = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_VPX_MIN_QP:
		ctr->vp8_min_qp = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_VPX_MAX_QP:
		ctr->vp8_max_qp = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_B_FRAMES:
		ret = venc_calc_bpframes(ctr->gop_size, ctrl->val, &bframes,
					 &ctr->num_p_frames);
		if (ret)
			return ret;

		ctr->num_b_frames = bframes;
		break;
	case V4L2_CID_MPEG_VIDEO_FORCE_KEY_FRAME:
		mutex_lock(&inst->lock);
		if (inst->streamon_out && inst->streamon_cap) {
			ptype = HFI_PROPERTY_CONFIG_VENC_REQUEST_SYNC_FRAME;
			ret = hfi_session_set_property(inst, ptype, &en);

			if (ret) {
				mutex_unlock(&inst->lock);
				return ret;
			}
		}
		mutex_unlock(&inst->lock);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}