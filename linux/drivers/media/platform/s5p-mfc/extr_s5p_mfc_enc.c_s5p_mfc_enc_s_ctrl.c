#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct v4l2_ctrl {int id; int val; } ;
struct TYPE_9__ {int rc_frame_qp; int rc_p_frame_qp; int rc_b_frame_qp; int rc_framerate; int rc_min_qp; int rc_max_qp; int level_v4l2; int profile; int tier; int max_partition_depth; int num_refs_for_p; int refreshtype; int const_intra_period_enable; int lossless_cu_enable; int wavefront_enable; int loopfilter; int hier_qp_enable; int hier_qp_type; int num_hier_layer; int* hier_qp_layer; int* hier_bit_layer; int general_pb_enable; int temporal_id_enable; int strong_intra_smooth; int intra_pu_split_disable; int tmv_prediction_disable; int max_num_merge_mv; int encoding_nostartcode_enable; int refreshperiod; int lf_beta_offset_div2; int lf_tc_offset_div2; int size_of_length_field; int prepend_sps_pps_to_idr; int /*<<< orphan*/  level; } ;
struct TYPE_8__ {int num_partitions; int imd_4x4; int num_ref; int filter_level; int filter_sharpness; int golden_frame_ref_period; int golden_frame_sel; int rc_min_qp; int rc_max_qp; int rc_frame_qp; int rc_p_frame_qp; int profile; } ;
struct TYPE_7__ {int level_v4l2; int level; int rc_frame_qp; int rc_min_qp; int rc_max_qp; int rc_p_frame_qp; int rc_b_frame_qp; int quarter_pixel; int /*<<< orphan*/  profile; } ;
struct TYPE_6__ {int cpb_size; int level_v4l2; int level; int loop_filter_mode; int loop_filter_alpha; int loop_filter_beta; int entropy_mode; int num_ref_pic_4p; int _8x8_transform; int rc_frame_qp; int rc_min_qp; int rc_max_qp; int rc_p_frame_qp; int rc_b_frame_qp; int rc_mb_dark; int rc_mb_smooth; int rc_mb_static; int rc_mb_activity; int vui_sar; int vui_ext_sar_width; int vui_ext_sar_height; int open_gop; int open_gop_size; int /*<<< orphan*/  vui_sar_idc; int /*<<< orphan*/  profile; } ;
struct TYPE_10__ {TYPE_4__ hevc; TYPE_3__ vp8; TYPE_2__ mpeg4; TYPE_1__ h264; } ;
struct s5p_mfc_enc_params {int gop_size; int slice_mode; int slice_mb; int slice_bit; int intra_refresh_mb; int pad; int pad_luma; int pad_cb; int pad_cr; int rc_frame; int rc_bitrate; int rc_reaction_coeff; int vbv_size; int mv_h_range; int mv_v_range; int seq_hdr_mode; int frame_skip_mode; int fixed_target_bit; int num_b_frame; int rc_mb; TYPE_5__ codec; } ;
struct s5p_mfc_dev {int /*<<< orphan*/  v4l2_dev; } ;
struct s5p_mfc_ctx {int force_frame_type; struct s5p_mfc_enc_params enc_params; struct s5p_mfc_dev* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IS_MFCV6_PLUS (struct s5p_mfc_dev*) ; 
 int /*<<< orphan*/  S5P_FIMV_ENC_PROFILE_H264_BASELINE ; 
 int /*<<< orphan*/  S5P_FIMV_ENC_PROFILE_H264_CONSTRAINED_BASELINE ; 
 int /*<<< orphan*/  S5P_FIMV_ENC_PROFILE_H264_HIGH ; 
 int /*<<< orphan*/  S5P_FIMV_ENC_PROFILE_H264_MAIN ; 
 int /*<<< orphan*/  S5P_FIMV_ENC_PROFILE_MPEG4_ADVANCED_SIMPLE ; 
 int /*<<< orphan*/  S5P_FIMV_ENC_PROFILE_MPEG4_SIMPLE ; 
#define  V4L2_CID_MPEG_MFC51_VIDEO_FORCE_FRAME_TYPE 249 
#define  V4L2_CID_MPEG_MFC51_VIDEO_FRAME_SKIP_MODE 248 
#define  V4L2_CID_MPEG_MFC51_VIDEO_H264_ADAPTIVE_RC_ACTIVITY 247 
#define  V4L2_CID_MPEG_MFC51_VIDEO_H264_ADAPTIVE_RC_DARK 246 
#define  V4L2_CID_MPEG_MFC51_VIDEO_H264_ADAPTIVE_RC_SMOOTH 245 
#define  V4L2_CID_MPEG_MFC51_VIDEO_H264_ADAPTIVE_RC_STATIC 244 
#define  V4L2_CID_MPEG_MFC51_VIDEO_H264_NUM_REF_PIC_FOR_P 243 
#define  V4L2_CID_MPEG_MFC51_VIDEO_PADDING 242 
#define  V4L2_CID_MPEG_MFC51_VIDEO_PADDING_YUV 241 
#define  V4L2_CID_MPEG_MFC51_VIDEO_RC_FIXED_TARGET_BIT 240 
#define  V4L2_CID_MPEG_MFC51_VIDEO_RC_REACTION_COEFF 239 
#define  V4L2_CID_MPEG_VIDEO_BITRATE 238 
#define  V4L2_CID_MPEG_VIDEO_B_FRAMES 237 
#define  V4L2_CID_MPEG_VIDEO_CYCLIC_INTRA_REFRESH_MB 236 
#define  V4L2_CID_MPEG_VIDEO_FORCE_KEY_FRAME 235 
#define  V4L2_CID_MPEG_VIDEO_FRAME_RC_ENABLE 234 
#define  V4L2_CID_MPEG_VIDEO_GOP_CLOSURE 233 
#define  V4L2_CID_MPEG_VIDEO_GOP_SIZE 232 
#define  V4L2_CID_MPEG_VIDEO_H263_B_FRAME_QP 231 
#define  V4L2_CID_MPEG_VIDEO_H263_I_FRAME_QP 230 
#define  V4L2_CID_MPEG_VIDEO_H263_MAX_QP 229 
#define  V4L2_CID_MPEG_VIDEO_H263_MIN_QP 228 
#define  V4L2_CID_MPEG_VIDEO_H263_P_FRAME_QP 227 
#define  V4L2_CID_MPEG_VIDEO_H264_8X8_TRANSFORM 226 
#define  V4L2_CID_MPEG_VIDEO_H264_B_FRAME_QP 225 
#define  V4L2_CID_MPEG_VIDEO_H264_CPB_SIZE 224 
#define  V4L2_CID_MPEG_VIDEO_H264_ENTROPY_MODE 223 
#define  V4L2_CID_MPEG_VIDEO_H264_I_FRAME_QP 222 
#define  V4L2_CID_MPEG_VIDEO_H264_I_PERIOD 221 
#define  V4L2_CID_MPEG_VIDEO_H264_LEVEL 220 
#define  V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_ALPHA 219 
#define  V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_BETA 218 
#define  V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_MODE 217 
#define  V4L2_CID_MPEG_VIDEO_H264_MAX_QP 216 
#define  V4L2_CID_MPEG_VIDEO_H264_MIN_QP 215 
#define  V4L2_CID_MPEG_VIDEO_H264_PROFILE 214 
#define  V4L2_CID_MPEG_VIDEO_H264_P_FRAME_QP 213 
#define  V4L2_CID_MPEG_VIDEO_H264_VUI_EXT_SAR_HEIGHT 212 
#define  V4L2_CID_MPEG_VIDEO_H264_VUI_EXT_SAR_WIDTH 211 
#define  V4L2_CID_MPEG_VIDEO_H264_VUI_SAR_ENABLE 210 
#define  V4L2_CID_MPEG_VIDEO_H264_VUI_SAR_IDC 209 
#define  V4L2_CID_MPEG_VIDEO_HEADER_MODE 208 
#define  V4L2_CID_MPEG_VIDEO_HEVC_B_FRAME_QP 207 
#define  V4L2_CID_MPEG_VIDEO_HEVC_CONST_INTRA_PRED 206 
#define  V4L2_CID_MPEG_VIDEO_HEVC_FRAME_RATE_RESOLUTION 205 
#define  V4L2_CID_MPEG_VIDEO_HEVC_GENERAL_PB 204 
#define  V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L0_BR 203 
#define  V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L0_QP 202 
#define  V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L1_BR 201 
#define  V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L1_QP 200 
#define  V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L2_BR 199 
#define  V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L2_QP 198 
#define  V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L3_BR 197 
#define  V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L3_QP 196 
#define  V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L4_BR 195 
#define  V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L4_QP 194 
#define  V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L5_BR 193 
#define  V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L5_QP 192 
#define  V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L6_BR 191 
#define  V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L6_QP 190 
#define  V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_LAYER 189 
#define  V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_TYPE 188 
#define  V4L2_CID_MPEG_VIDEO_HEVC_HIER_QP 187 
#define  V4L2_CID_MPEG_VIDEO_HEVC_INTRA_PU_SPLIT 186 
#define  V4L2_CID_MPEG_VIDEO_HEVC_I_FRAME_QP 185 
#define  V4L2_CID_MPEG_VIDEO_HEVC_LEVEL 184 
#define  V4L2_CID_MPEG_VIDEO_HEVC_LF_BETA_OFFSET_DIV2 183 
#define  V4L2_CID_MPEG_VIDEO_HEVC_LF_TC_OFFSET_DIV2 182 
#define  V4L2_CID_MPEG_VIDEO_HEVC_LOOP_FILTER_MODE 181 
#define  V4L2_CID_MPEG_VIDEO_HEVC_LOSSLESS_CU 180 
#define  V4L2_CID_MPEG_VIDEO_HEVC_MAX_NUM_MERGE_MV_MINUS1 179 
#define  V4L2_CID_MPEG_VIDEO_HEVC_MAX_PARTITION_DEPTH 178 
#define  V4L2_CID_MPEG_VIDEO_HEVC_MAX_QP 177 
#define  V4L2_CID_MPEG_VIDEO_HEVC_MIN_QP 176 
#define  V4L2_CID_MPEG_VIDEO_HEVC_PROFILE 175 
#define  V4L2_CID_MPEG_VIDEO_HEVC_P_FRAME_QP 174 
#define  V4L2_CID_MPEG_VIDEO_HEVC_REFRESH_PERIOD 173 
#define  V4L2_CID_MPEG_VIDEO_HEVC_REFRESH_TYPE 172 
#define  V4L2_CID_MPEG_VIDEO_HEVC_SIZE_OF_LENGTH_FIELD 171 
#define  V4L2_CID_MPEG_VIDEO_HEVC_STRONG_SMOOTHING 170 
#define  V4L2_CID_MPEG_VIDEO_HEVC_TEMPORAL_ID 169 
#define  V4L2_CID_MPEG_VIDEO_HEVC_TIER 168 
#define  V4L2_CID_MPEG_VIDEO_HEVC_TMV_PREDICTION 167 
#define  V4L2_CID_MPEG_VIDEO_HEVC_WAVEFRONT 166 
#define  V4L2_CID_MPEG_VIDEO_HEVC_WITHOUT_STARTCODE 165 
#define  V4L2_CID_MPEG_VIDEO_MB_RC_ENABLE 164 
#define  V4L2_CID_MPEG_VIDEO_MPEG4_B_FRAME_QP 163 
#define  V4L2_CID_MPEG_VIDEO_MPEG4_I_FRAME_QP 162 
#define  V4L2_CID_MPEG_VIDEO_MPEG4_LEVEL 161 
#define  V4L2_CID_MPEG_VIDEO_MPEG4_MAX_QP 160 
#define  V4L2_CID_MPEG_VIDEO_MPEG4_MIN_QP 159 
#define  V4L2_CID_MPEG_VIDEO_MPEG4_PROFILE 158 
#define  V4L2_CID_MPEG_VIDEO_MPEG4_P_FRAME_QP 157 
#define  V4L2_CID_MPEG_VIDEO_MPEG4_QPEL 156 
#define  V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MAX_BYTES 155 
#define  V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MAX_MB 154 
#define  V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MODE 153 
#define  V4L2_CID_MPEG_VIDEO_MV_H_SEARCH_RANGE 152 
#define  V4L2_CID_MPEG_VIDEO_MV_V_SEARCH_RANGE 151 
#define  V4L2_CID_MPEG_VIDEO_PREPEND_SPSPPS_TO_IDR 150 
#define  V4L2_CID_MPEG_VIDEO_REF_NUMBER_FOR_PFRAMES 149 
#define  V4L2_CID_MPEG_VIDEO_VBV_SIZE 148 
#define  V4L2_CID_MPEG_VIDEO_VP8_PROFILE 147 
#define  V4L2_CID_MPEG_VIDEO_VPX_FILTER_LEVEL 146 
#define  V4L2_CID_MPEG_VIDEO_VPX_FILTER_SHARPNESS 145 
#define  V4L2_CID_MPEG_VIDEO_VPX_GOLDEN_FRAME_REF_PERIOD 144 
#define  V4L2_CID_MPEG_VIDEO_VPX_GOLDEN_FRAME_SEL 143 
#define  V4L2_CID_MPEG_VIDEO_VPX_IMD_DISABLE_4X4 142 
#define  V4L2_CID_MPEG_VIDEO_VPX_I_FRAME_QP 141 
#define  V4L2_CID_MPEG_VIDEO_VPX_MAX_QP 140 
#define  V4L2_CID_MPEG_VIDEO_VPX_MIN_QP 139 
#define  V4L2_CID_MPEG_VIDEO_VPX_NUM_PARTITIONS 138 
#define  V4L2_CID_MPEG_VIDEO_VPX_NUM_REF_FRAMES 137 
#define  V4L2_CID_MPEG_VIDEO_VPX_P_FRAME_QP 136 
 int V4L2_MPEG_MFC51_VIDEO_FORCE_FRAME_TYPE_I_FRAME ; 
#define  V4L2_MPEG_VIDEO_H264_PROFILE_BASELINE 135 
#define  V4L2_MPEG_VIDEO_H264_PROFILE_CONSTRAINED_BASELINE 134 
#define  V4L2_MPEG_VIDEO_H264_PROFILE_HIGH 133 
#define  V4L2_MPEG_VIDEO_H264_PROFILE_MAIN 132 
#define  V4L2_MPEG_VIDEO_HEVC_PROFILE_MAIN 131 
#define  V4L2_MPEG_VIDEO_HEVC_PROFILE_MAIN_STILL_PICTURE 130 
#define  V4L2_MPEG_VIDEO_MPEG4_PROFILE_ADVANCED_SIMPLE 129 
#define  V4L2_MPEG_VIDEO_MPEG4_PROFILE_SIMPLE 128 
 int /*<<< orphan*/  __enc_update_hevc_qp_ctrls_range (struct s5p_mfc_ctx*,int,int) ; 
 struct s5p_mfc_ctx* ctrl_to_ctx (struct v4l2_ctrl*) ; 
 int h264_level (int) ; 
 int /*<<< orphan*/  hevc_level (int) ; 
 int /*<<< orphan*/  mfc_err (char*) ; 
 int mpeg4_level (int) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  vui_sar_idc (int) ; 

__attribute__((used)) static int s5p_mfc_enc_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct s5p_mfc_ctx *ctx = ctrl_to_ctx(ctrl);
	struct s5p_mfc_dev *dev = ctx->dev;
	struct s5p_mfc_enc_params *p = &ctx->enc_params;
	int ret = 0;

	switch (ctrl->id) {
	case V4L2_CID_MPEG_VIDEO_GOP_SIZE:
		p->gop_size = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MODE:
		p->slice_mode = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MAX_MB:
		p->slice_mb = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_MULTI_SLICE_MAX_BYTES:
		p->slice_bit = ctrl->val * 8;
		break;
	case V4L2_CID_MPEG_VIDEO_CYCLIC_INTRA_REFRESH_MB:
		p->intra_refresh_mb = ctrl->val;
		break;
	case V4L2_CID_MPEG_MFC51_VIDEO_PADDING:
		p->pad = ctrl->val;
		break;
	case V4L2_CID_MPEG_MFC51_VIDEO_PADDING_YUV:
		p->pad_luma = (ctrl->val >> 16) & 0xff;
		p->pad_cb = (ctrl->val >> 8) & 0xff;
		p->pad_cr = (ctrl->val >> 0) & 0xff;
		break;
	case V4L2_CID_MPEG_VIDEO_FRAME_RC_ENABLE:
		p->rc_frame = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_BITRATE:
		p->rc_bitrate = ctrl->val;
		break;
	case V4L2_CID_MPEG_MFC51_VIDEO_RC_REACTION_COEFF:
		p->rc_reaction_coeff = ctrl->val;
		break;
	case V4L2_CID_MPEG_MFC51_VIDEO_FORCE_FRAME_TYPE:
		ctx->force_frame_type = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_FORCE_KEY_FRAME:
		ctx->force_frame_type =
			V4L2_MPEG_MFC51_VIDEO_FORCE_FRAME_TYPE_I_FRAME;
		break;
	case V4L2_CID_MPEG_VIDEO_VBV_SIZE:
		p->vbv_size = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_MV_H_SEARCH_RANGE:
		p->mv_h_range = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_MV_V_SEARCH_RANGE:
		p->mv_v_range = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_H264_CPB_SIZE:
		p->codec.h264.cpb_size = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEADER_MODE:
		p->seq_hdr_mode = ctrl->val;
		break;
	case V4L2_CID_MPEG_MFC51_VIDEO_FRAME_SKIP_MODE:
		p->frame_skip_mode = ctrl->val;
		break;
	case V4L2_CID_MPEG_MFC51_VIDEO_RC_FIXED_TARGET_BIT:
		p->fixed_target_bit = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_B_FRAMES:
		p->num_b_frame = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_H264_PROFILE:
		switch (ctrl->val) {
		case V4L2_MPEG_VIDEO_H264_PROFILE_MAIN:
			p->codec.h264.profile =
					S5P_FIMV_ENC_PROFILE_H264_MAIN;
			break;
		case V4L2_MPEG_VIDEO_H264_PROFILE_HIGH:
			p->codec.h264.profile =
					S5P_FIMV_ENC_PROFILE_H264_HIGH;
			break;
		case V4L2_MPEG_VIDEO_H264_PROFILE_BASELINE:
			p->codec.h264.profile =
				S5P_FIMV_ENC_PROFILE_H264_BASELINE;
			break;
		case V4L2_MPEG_VIDEO_H264_PROFILE_CONSTRAINED_BASELINE:
			if (IS_MFCV6_PLUS(dev))
				p->codec.h264.profile =
				S5P_FIMV_ENC_PROFILE_H264_CONSTRAINED_BASELINE;
			else
				ret = -EINVAL;
			break;
		default:
			ret = -EINVAL;
		}
		break;
	case V4L2_CID_MPEG_VIDEO_H264_LEVEL:
		p->codec.h264.level_v4l2 = ctrl->val;
		p->codec.h264.level = h264_level(ctrl->val);
		if (p->codec.h264.level < 0) {
			mfc_err("Level number is wrong\n");
			ret = p->codec.h264.level;
		}
		break;
	case V4L2_CID_MPEG_VIDEO_MPEG4_LEVEL:
		p->codec.mpeg4.level_v4l2 = ctrl->val;
		p->codec.mpeg4.level = mpeg4_level(ctrl->val);
		if (p->codec.mpeg4.level < 0) {
			mfc_err("Level number is wrong\n");
			ret = p->codec.mpeg4.level;
		}
		break;
	case V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_MODE:
		p->codec.h264.loop_filter_mode = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_ALPHA:
		p->codec.h264.loop_filter_alpha = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_H264_LOOP_FILTER_BETA:
		p->codec.h264.loop_filter_beta = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_H264_ENTROPY_MODE:
		p->codec.h264.entropy_mode = ctrl->val;
		break;
	case V4L2_CID_MPEG_MFC51_VIDEO_H264_NUM_REF_PIC_FOR_P:
		p->codec.h264.num_ref_pic_4p = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_H264_8X8_TRANSFORM:
		p->codec.h264._8x8_transform = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_MB_RC_ENABLE:
		p->rc_mb = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_H264_I_FRAME_QP:
		p->codec.h264.rc_frame_qp = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_H264_MIN_QP:
		p->codec.h264.rc_min_qp = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_H264_MAX_QP:
		p->codec.h264.rc_max_qp = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_H264_P_FRAME_QP:
		p->codec.h264.rc_p_frame_qp = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_H264_B_FRAME_QP:
		p->codec.h264.rc_b_frame_qp = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_MPEG4_I_FRAME_QP:
	case V4L2_CID_MPEG_VIDEO_H263_I_FRAME_QP:
		p->codec.mpeg4.rc_frame_qp = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_MPEG4_MIN_QP:
	case V4L2_CID_MPEG_VIDEO_H263_MIN_QP:
		p->codec.mpeg4.rc_min_qp = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_MPEG4_MAX_QP:
	case V4L2_CID_MPEG_VIDEO_H263_MAX_QP:
		p->codec.mpeg4.rc_max_qp = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_MPEG4_P_FRAME_QP:
	case V4L2_CID_MPEG_VIDEO_H263_P_FRAME_QP:
		p->codec.mpeg4.rc_p_frame_qp = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_MPEG4_B_FRAME_QP:
	case V4L2_CID_MPEG_VIDEO_H263_B_FRAME_QP:
		p->codec.mpeg4.rc_b_frame_qp = ctrl->val;
		break;
	case V4L2_CID_MPEG_MFC51_VIDEO_H264_ADAPTIVE_RC_DARK:
		p->codec.h264.rc_mb_dark = ctrl->val;
		break;
	case V4L2_CID_MPEG_MFC51_VIDEO_H264_ADAPTIVE_RC_SMOOTH:
		p->codec.h264.rc_mb_smooth = ctrl->val;
		break;
	case V4L2_CID_MPEG_MFC51_VIDEO_H264_ADAPTIVE_RC_STATIC:
		p->codec.h264.rc_mb_static = ctrl->val;
		break;
	case V4L2_CID_MPEG_MFC51_VIDEO_H264_ADAPTIVE_RC_ACTIVITY:
		p->codec.h264.rc_mb_activity = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_H264_VUI_SAR_ENABLE:
		p->codec.h264.vui_sar = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_H264_VUI_SAR_IDC:
		p->codec.h264.vui_sar_idc = vui_sar_idc(ctrl->val);
		break;
	case V4L2_CID_MPEG_VIDEO_H264_VUI_EXT_SAR_WIDTH:
		p->codec.h264.vui_ext_sar_width = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_H264_VUI_EXT_SAR_HEIGHT:
		p->codec.h264.vui_ext_sar_height = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_GOP_CLOSURE:
		p->codec.h264.open_gop = !ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_H264_I_PERIOD:
		p->codec.h264.open_gop_size = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_MPEG4_PROFILE:
		switch (ctrl->val) {
		case V4L2_MPEG_VIDEO_MPEG4_PROFILE_SIMPLE:
			p->codec.mpeg4.profile =
				S5P_FIMV_ENC_PROFILE_MPEG4_SIMPLE;
			break;
		case V4L2_MPEG_VIDEO_MPEG4_PROFILE_ADVANCED_SIMPLE:
			p->codec.mpeg4.profile =
			S5P_FIMV_ENC_PROFILE_MPEG4_ADVANCED_SIMPLE;
			break;
		default:
			ret = -EINVAL;
		}
		break;
	case V4L2_CID_MPEG_VIDEO_MPEG4_QPEL:
		p->codec.mpeg4.quarter_pixel = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_VPX_NUM_PARTITIONS:
		p->codec.vp8.num_partitions = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_VPX_IMD_DISABLE_4X4:
		p->codec.vp8.imd_4x4 = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_VPX_NUM_REF_FRAMES:
		p->codec.vp8.num_ref = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_VPX_FILTER_LEVEL:
		p->codec.vp8.filter_level = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_VPX_FILTER_SHARPNESS:
		p->codec.vp8.filter_sharpness = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_VPX_GOLDEN_FRAME_REF_PERIOD:
		p->codec.vp8.golden_frame_ref_period = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_VPX_GOLDEN_FRAME_SEL:
		p->codec.vp8.golden_frame_sel = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_VPX_MIN_QP:
		p->codec.vp8.rc_min_qp = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_VPX_MAX_QP:
		p->codec.vp8.rc_max_qp = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_VPX_I_FRAME_QP:
		p->codec.vp8.rc_frame_qp = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_VPX_P_FRAME_QP:
		p->codec.vp8.rc_p_frame_qp = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_VP8_PROFILE:
		p->codec.vp8.profile = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_I_FRAME_QP:
		p->codec.hevc.rc_frame_qp = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_P_FRAME_QP:
		p->codec.hevc.rc_p_frame_qp = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_B_FRAME_QP:
		p->codec.hevc.rc_b_frame_qp = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_FRAME_RATE_RESOLUTION:
		p->codec.hevc.rc_framerate = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_MIN_QP:
		p->codec.hevc.rc_min_qp = ctrl->val;
		__enc_update_hevc_qp_ctrls_range(ctx, ctrl->val,
						 p->codec.hevc.rc_max_qp);
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_MAX_QP:
		p->codec.hevc.rc_max_qp = ctrl->val;
		__enc_update_hevc_qp_ctrls_range(ctx, p->codec.hevc.rc_min_qp,
						 ctrl->val);
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_LEVEL:
		p->codec.hevc.level_v4l2 = ctrl->val;
		p->codec.hevc.level = hevc_level(ctrl->val);
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_PROFILE:
		switch (ctrl->val) {
		case V4L2_MPEG_VIDEO_HEVC_PROFILE_MAIN:
			p->codec.hevc.profile =
				V4L2_MPEG_VIDEO_HEVC_PROFILE_MAIN;
			break;
		case V4L2_MPEG_VIDEO_HEVC_PROFILE_MAIN_STILL_PICTURE:
			p->codec.hevc.profile =
			V4L2_MPEG_VIDEO_HEVC_PROFILE_MAIN_STILL_PICTURE;
			break;
		default:
			ret = -EINVAL;
		}
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_TIER:
		p->codec.hevc.tier = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_MAX_PARTITION_DEPTH:
		p->codec.hevc.max_partition_depth = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_REF_NUMBER_FOR_PFRAMES:
		p->codec.hevc.num_refs_for_p = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_REFRESH_TYPE:
		p->codec.hevc.refreshtype = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_CONST_INTRA_PRED:
		p->codec.hevc.const_intra_period_enable = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_LOSSLESS_CU:
		p->codec.hevc.lossless_cu_enable = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_WAVEFRONT:
		p->codec.hevc.wavefront_enable = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_LOOP_FILTER_MODE:
		p->codec.hevc.loopfilter = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_HIER_QP:
		p->codec.hevc.hier_qp_enable = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_TYPE:
		p->codec.hevc.hier_qp_type = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_LAYER:
		p->codec.hevc.num_hier_layer = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L0_QP:
		p->codec.hevc.hier_qp_layer[0] = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L1_QP:
		p->codec.hevc.hier_qp_layer[1] = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L2_QP:
		p->codec.hevc.hier_qp_layer[2] = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L3_QP:
		p->codec.hevc.hier_qp_layer[3] = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L4_QP:
		p->codec.hevc.hier_qp_layer[4] = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L5_QP:
		p->codec.hevc.hier_qp_layer[5] = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L6_QP:
		p->codec.hevc.hier_qp_layer[6] = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L0_BR:
		p->codec.hevc.hier_bit_layer[0] = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L1_BR:
		p->codec.hevc.hier_bit_layer[1] = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L2_BR:
		p->codec.hevc.hier_bit_layer[2] = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L3_BR:
		p->codec.hevc.hier_bit_layer[3] = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L4_BR:
		p->codec.hevc.hier_bit_layer[4] = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L5_BR:
		p->codec.hevc.hier_bit_layer[5] = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_HIER_CODING_L6_BR:
		p->codec.hevc.hier_bit_layer[6] = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_GENERAL_PB:
		p->codec.hevc.general_pb_enable = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_TEMPORAL_ID:
		p->codec.hevc.temporal_id_enable = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_STRONG_SMOOTHING:
		p->codec.hevc.strong_intra_smooth = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_INTRA_PU_SPLIT:
		p->codec.hevc.intra_pu_split_disable = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_TMV_PREDICTION:
		p->codec.hevc.tmv_prediction_disable = !ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_MAX_NUM_MERGE_MV_MINUS1:
		p->codec.hevc.max_num_merge_mv = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_WITHOUT_STARTCODE:
		p->codec.hevc.encoding_nostartcode_enable = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_REFRESH_PERIOD:
		p->codec.hevc.refreshperiod = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_LF_BETA_OFFSET_DIV2:
		p->codec.hevc.lf_beta_offset_div2 = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_LF_TC_OFFSET_DIV2:
		p->codec.hevc.lf_tc_offset_div2 = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_HEVC_SIZE_OF_LENGTH_FIELD:
		p->codec.hevc.size_of_length_field = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_PREPEND_SPSPPS_TO_IDR:
		p->codec.hevc.prepend_sps_pps_to_idr = ctrl->val;
		break;
	default:
		v4l2_err(&dev->v4l2_dev, "Invalid control, id=%d, val=%d\n",
							ctrl->id, ctrl->val);
		ret = -EINVAL;
	}
	return ret;
}