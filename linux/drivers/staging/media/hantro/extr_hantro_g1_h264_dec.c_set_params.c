#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct vb2_v4l2_buffer {int /*<<< orphan*/  vb2_buf; } ;
struct v4l2_ctrl_h264_sps {int flags; scalar_t__ chroma_format_idc; scalar_t__ log2_max_frame_num_minus4; int /*<<< orphan*/  max_num_ref_frames; scalar_t__ pic_height_in_map_units_minus1; scalar_t__ pic_width_in_mbs_minus1; } ;
struct v4l2_ctrl_h264_slice_params {int flags; int /*<<< orphan*/  pic_order_cnt_bit_size; int /*<<< orphan*/  pic_parameter_set_id; int /*<<< orphan*/  idr_pic_id; int /*<<< orphan*/  dec_ref_pic_marking_bit_size; int /*<<< orphan*/  frame_num; } ;
struct v4l2_ctrl_h264_pps {int flags; scalar_t__ num_ref_idx_l1_default_active_minus1; scalar_t__ num_ref_idx_l0_default_active_minus1; int /*<<< orphan*/  weighted_bipred_idc; scalar_t__ pic_init_qp_minus26; int /*<<< orphan*/  second_chroma_qp_index_offset; int /*<<< orphan*/  chroma_qp_index_offset; } ;
struct v4l2_ctrl_h264_decode_params {int flags; scalar_t__ nal_ref_idc; } ;
struct hantro_h264_dec_ctrls {struct v4l2_ctrl_h264_pps* pps; struct v4l2_ctrl_h264_sps* sps; struct v4l2_ctrl_h264_slice_params* slices; struct v4l2_ctrl_h264_decode_params* decode; } ;
struct hantro_dev {int dummy; } ;
struct TYPE_2__ {struct hantro_h264_dec_ctrls ctrls; } ;
struct hantro_ctx {struct hantro_dev* dev; TYPE_1__ h264_dec; } ;

/* Variables and functions */
 int /*<<< orphan*/  G1_REG_DEC_CTRL0 ; 
 int G1_REG_DEC_CTRL0_DEC_AXI_WR_ID (int) ; 
 int G1_REG_DEC_CTRL0_PICORD_COUNT_E ; 
 int G1_REG_DEC_CTRL0_PIC_FIELDMODE_E ; 
 int G1_REG_DEC_CTRL0_PIC_INTERLACE_E ; 
 int G1_REG_DEC_CTRL0_PIC_TOPFIELD_E ; 
 int G1_REG_DEC_CTRL0_SEQ_MBAFF_E ; 
 int G1_REG_DEC_CTRL0_WRITE_MVS_E ; 
 int /*<<< orphan*/  G1_REG_DEC_CTRL1 ; 
 int G1_REG_DEC_CTRL1_PIC_MB_HEIGHT_P (scalar_t__) ; 
 int G1_REG_DEC_CTRL1_PIC_MB_WIDTH (scalar_t__) ; 
 int G1_REG_DEC_CTRL1_REF_FRAMES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G1_REG_DEC_CTRL2 ; 
 int G1_REG_DEC_CTRL2_CH_QP_OFFSET (int /*<<< orphan*/ ) ; 
 int G1_REG_DEC_CTRL2_CH_QP_OFFSET2 (int /*<<< orphan*/ ) ; 
 int G1_REG_DEC_CTRL2_FIELDPIC_FLAG_E ; 
 int G1_REG_DEC_CTRL2_TYPE1_QUANT_E ; 
 int /*<<< orphan*/  G1_REG_DEC_CTRL3 ; 
 int G1_REG_DEC_CTRL3_INIT_QP (scalar_t__) ; 
 int G1_REG_DEC_CTRL3_START_CODE_E ; 
 int G1_REG_DEC_CTRL3_STREAM_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G1_REG_DEC_CTRL4 ; 
 int G1_REG_DEC_CTRL4_BLACKWHITE_E ; 
 int G1_REG_DEC_CTRL4_CABAC_E ; 
 int G1_REG_DEC_CTRL4_DIR_8X8_INFER_E ; 
 int G1_REG_DEC_CTRL4_FRAMENUM (int /*<<< orphan*/ ) ; 
 int G1_REG_DEC_CTRL4_FRAMENUM_LEN (scalar_t__) ; 
 int G1_REG_DEC_CTRL4_WEIGHT_BIPR_IDC (int /*<<< orphan*/ ) ; 
 int G1_REG_DEC_CTRL4_WEIGHT_PRED_E ; 
 int /*<<< orphan*/  G1_REG_DEC_CTRL5 ; 
 int G1_REG_DEC_CTRL5_8X8TRANS_FLAG_E ; 
 int G1_REG_DEC_CTRL5_CONST_INTRA_E ; 
 int G1_REG_DEC_CTRL5_FILT_CTRL_PRES ; 
 int G1_REG_DEC_CTRL5_IDR_PIC_E ; 
 int G1_REG_DEC_CTRL5_IDR_PIC_ID (int /*<<< orphan*/ ) ; 
 int G1_REG_DEC_CTRL5_RDPIC_CNT_PRES ; 
 int G1_REG_DEC_CTRL5_REFPIC_MK_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G1_REG_DEC_CTRL6 ; 
 int G1_REG_DEC_CTRL6_POC_LENGTH (int /*<<< orphan*/ ) ; 
 int G1_REG_DEC_CTRL6_PPS_ID (int /*<<< orphan*/ ) ; 
 int G1_REG_DEC_CTRL6_REFIDX0_ACTIVE (scalar_t__) ; 
 int G1_REG_DEC_CTRL6_REFIDX1_ACTIVE (scalar_t__) ; 
 int /*<<< orphan*/  G1_REG_ERR_CONC ; 
 int /*<<< orphan*/  G1_REG_PRED_FLT ; 
 int G1_REG_PRED_FLT_PRED_BC_TAP_0_0 (int) ; 
 int G1_REG_PRED_FLT_PRED_BC_TAP_0_1 (int) ; 
 int G1_REG_PRED_FLT_PRED_BC_TAP_0_2 (int) ; 
 int /*<<< orphan*/  G1_REG_REF_BUF_CTRL ; 
 int /*<<< orphan*/  G1_REG_REF_BUF_CTRL2 ; 
 int G1_REG_REF_BUF_CTRL2_APF_THRESHOLD (int) ; 
 int V4L2_H264_DECODE_PARAM_FLAG_IDR_PIC ; 
 int V4L2_H264_PPS_FLAG_CONSTRAINED_INTRA_PRED ; 
 int V4L2_H264_PPS_FLAG_DEBLOCKING_FILTER_CONTROL_PRESENT ; 
 int V4L2_H264_PPS_FLAG_ENTROPY_CODING_MODE ; 
 int V4L2_H264_PPS_FLAG_REDUNDANT_PIC_CNT_PRESENT ; 
 int V4L2_H264_PPS_FLAG_TRANSFORM_8X8_MODE ; 
 int V4L2_H264_PPS_FLAG_WEIGHTED_PRED ; 
 int V4L2_H264_SLICE_FLAG_BOTTOM_FIELD ; 
 int V4L2_H264_SLICE_FLAG_FIELD_PIC ; 
 int V4L2_H264_SPS_FLAG_DIRECT_8X8_INFERENCE ; 
 int V4L2_H264_SPS_FLAG_FRAME_MBS_ONLY ; 
 int V4L2_H264_SPS_FLAG_MB_ADAPTIVE_FRAME_FIELD ; 
 struct vb2_v4l2_buffer* hantro_get_src_buf (struct hantro_ctx*) ; 
 int /*<<< orphan*/  vb2_get_plane_payload (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdpu_write_relaxed (struct hantro_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_params(struct hantro_ctx *ctx)
{
	const struct hantro_h264_dec_ctrls *ctrls = &ctx->h264_dec.ctrls;
	const struct v4l2_ctrl_h264_decode_params *dec_param = ctrls->decode;
	const struct v4l2_ctrl_h264_slice_params *slices = ctrls->slices;
	const struct v4l2_ctrl_h264_sps *sps = ctrls->sps;
	const struct v4l2_ctrl_h264_pps *pps = ctrls->pps;
	struct vb2_v4l2_buffer *src_buf = hantro_get_src_buf(ctx);
	struct hantro_dev *vpu = ctx->dev;
	u32 reg;

	/* Decoder control register 0. */
	reg = G1_REG_DEC_CTRL0_DEC_AXI_WR_ID(0x0);
	if (sps->flags & V4L2_H264_SPS_FLAG_MB_ADAPTIVE_FRAME_FIELD)
		reg |= G1_REG_DEC_CTRL0_SEQ_MBAFF_E;
	reg |= G1_REG_DEC_CTRL0_PICORD_COUNT_E;
	if (dec_param->nal_ref_idc)
		reg |= G1_REG_DEC_CTRL0_WRITE_MVS_E;

	if (!(sps->flags & V4L2_H264_SPS_FLAG_FRAME_MBS_ONLY) &&
	    (sps->flags & V4L2_H264_SPS_FLAG_MB_ADAPTIVE_FRAME_FIELD ||
	     slices[0].flags & V4L2_H264_SLICE_FLAG_FIELD_PIC))
		reg |= G1_REG_DEC_CTRL0_PIC_INTERLACE_E;
	if (slices[0].flags & V4L2_H264_SLICE_FLAG_FIELD_PIC)
		reg |= G1_REG_DEC_CTRL0_PIC_FIELDMODE_E;
	if (!(slices[0].flags & V4L2_H264_SLICE_FLAG_BOTTOM_FIELD))
		reg |= G1_REG_DEC_CTRL0_PIC_TOPFIELD_E;
	vdpu_write_relaxed(vpu, reg, G1_REG_DEC_CTRL0);

	/* Decoder control register 1. */
	reg = G1_REG_DEC_CTRL1_PIC_MB_WIDTH(sps->pic_width_in_mbs_minus1 + 1) |
	      G1_REG_DEC_CTRL1_PIC_MB_HEIGHT_P(sps->pic_height_in_map_units_minus1 + 1) |
	      G1_REG_DEC_CTRL1_REF_FRAMES(sps->max_num_ref_frames);
	vdpu_write_relaxed(vpu, reg, G1_REG_DEC_CTRL1);

	/* Decoder control register 2. */
	reg = G1_REG_DEC_CTRL2_CH_QP_OFFSET(pps->chroma_qp_index_offset) |
	      G1_REG_DEC_CTRL2_CH_QP_OFFSET2(pps->second_chroma_qp_index_offset);

	/* always use the matrix sent from userspace */
	reg |= G1_REG_DEC_CTRL2_TYPE1_QUANT_E;

	if (slices[0].flags &  V4L2_H264_SLICE_FLAG_FIELD_PIC)
		reg |= G1_REG_DEC_CTRL2_FIELDPIC_FLAG_E;
	vdpu_write_relaxed(vpu, reg, G1_REG_DEC_CTRL2);

	/* Decoder control register 3. */
	reg = G1_REG_DEC_CTRL3_START_CODE_E |
	      G1_REG_DEC_CTRL3_INIT_QP(pps->pic_init_qp_minus26 + 26) |
	      G1_REG_DEC_CTRL3_STREAM_LEN(vb2_get_plane_payload(&src_buf->vb2_buf, 0));
	vdpu_write_relaxed(vpu, reg, G1_REG_DEC_CTRL3);

	/* Decoder control register 4. */
	reg = G1_REG_DEC_CTRL4_FRAMENUM_LEN(sps->log2_max_frame_num_minus4 + 4) |
	      G1_REG_DEC_CTRL4_FRAMENUM(slices[0].frame_num) |
	      G1_REG_DEC_CTRL4_WEIGHT_BIPR_IDC(pps->weighted_bipred_idc);
	if (pps->flags & V4L2_H264_PPS_FLAG_ENTROPY_CODING_MODE)
		reg |= G1_REG_DEC_CTRL4_CABAC_E;
	if (sps->flags & V4L2_H264_SPS_FLAG_DIRECT_8X8_INFERENCE)
		reg |= G1_REG_DEC_CTRL4_DIR_8X8_INFER_E;
	if (sps->chroma_format_idc == 0)
		reg |= G1_REG_DEC_CTRL4_BLACKWHITE_E;
	if (pps->flags & V4L2_H264_PPS_FLAG_WEIGHTED_PRED)
		reg |= G1_REG_DEC_CTRL4_WEIGHT_PRED_E;
	vdpu_write_relaxed(vpu, reg, G1_REG_DEC_CTRL4);

	/* Decoder control register 5. */
	reg = G1_REG_DEC_CTRL5_REFPIC_MK_LEN(slices[0].dec_ref_pic_marking_bit_size) |
	      G1_REG_DEC_CTRL5_IDR_PIC_ID(slices[0].idr_pic_id);
	if (pps->flags & V4L2_H264_PPS_FLAG_CONSTRAINED_INTRA_PRED)
		reg |= G1_REG_DEC_CTRL5_CONST_INTRA_E;
	if (pps->flags & V4L2_H264_PPS_FLAG_DEBLOCKING_FILTER_CONTROL_PRESENT)
		reg |= G1_REG_DEC_CTRL5_FILT_CTRL_PRES;
	if (pps->flags & V4L2_H264_PPS_FLAG_REDUNDANT_PIC_CNT_PRESENT)
		reg |= G1_REG_DEC_CTRL5_RDPIC_CNT_PRES;
	if (pps->flags & V4L2_H264_PPS_FLAG_TRANSFORM_8X8_MODE)
		reg |= G1_REG_DEC_CTRL5_8X8TRANS_FLAG_E;
	if (dec_param->flags & V4L2_H264_DECODE_PARAM_FLAG_IDR_PIC)
		reg |= G1_REG_DEC_CTRL5_IDR_PIC_E;
	vdpu_write_relaxed(vpu, reg, G1_REG_DEC_CTRL5);

	/* Decoder control register 6. */
	reg = G1_REG_DEC_CTRL6_PPS_ID(slices[0].pic_parameter_set_id) |
	      G1_REG_DEC_CTRL6_REFIDX0_ACTIVE(pps->num_ref_idx_l0_default_active_minus1 + 1) |
	      G1_REG_DEC_CTRL6_REFIDX1_ACTIVE(pps->num_ref_idx_l1_default_active_minus1 + 1) |
	      G1_REG_DEC_CTRL6_POC_LENGTH(slices[0].pic_order_cnt_bit_size);
	vdpu_write_relaxed(vpu, reg, G1_REG_DEC_CTRL6);

	/* Error concealment register. */
	vdpu_write_relaxed(vpu, 0, G1_REG_ERR_CONC);

	/* Prediction filter tap register. */
	vdpu_write_relaxed(vpu,
			   G1_REG_PRED_FLT_PRED_BC_TAP_0_0(1) |
			   G1_REG_PRED_FLT_PRED_BC_TAP_0_1(-5 & 0x3ff) |
			   G1_REG_PRED_FLT_PRED_BC_TAP_0_2(20),
			   G1_REG_PRED_FLT);

	/* Reference picture buffer control register. */
	vdpu_write_relaxed(vpu, 0, G1_REG_REF_BUF_CTRL);

	/* Reference picture buffer control register 2. */
	vdpu_write_relaxed(vpu, G1_REG_REF_BUF_CTRL2_APF_THRESHOLD(8),
			   G1_REG_REF_BUF_CTRL2);
}