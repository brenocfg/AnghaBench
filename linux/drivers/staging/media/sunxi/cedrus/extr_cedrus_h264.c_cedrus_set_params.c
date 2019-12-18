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
typedef  int u32 ;
struct vb2_buffer {int dummy; } ;
struct v4l2_ctrl_h264_sps {int chroma_format_idc; int pic_width_in_mbs_minus1; int pic_height_in_map_units_minus1; int flags; } ;
struct v4l2_ctrl_h264_slice_params {int header_bit_size; int size; int slice_type; int num_ref_idx_l0_active_minus1; int num_ref_idx_l1_active_minus1; int cabac_init_idc; int flags; int disable_deblocking_filter_idc; int slice_alpha_c0_offset_div2; int slice_beta_offset_div2; int slice_qp_delta; } ;
struct v4l2_ctrl_h264_pps {int flags; int weighted_bipred_idc; int second_chroma_qp_index_offset; int chroma_qp_index_offset; int pic_init_qp_minus26; } ;
struct v4l2_ctrl_h264_decode_params {scalar_t__ nal_ref_idc; } ;
struct TYPE_3__ {struct v4l2_ctrl_h264_sps* sps; struct v4l2_ctrl_h264_pps* pps; struct v4l2_ctrl_h264_slice_params* slice_params; struct v4l2_ctrl_h264_decode_params* decode_params; } ;
struct cedrus_run {TYPE_2__* src; TYPE_1__ h264; } ;
struct cedrus_dev {int dummy; } ;
struct cedrus_ctx {struct cedrus_dev* dev; } ;
typedef  int dma_addr_t ;
struct TYPE_4__ {struct vb2_buffer vb2_buf; } ;

/* Variables and functions */
 int BIT (int) ; 
 int V4L2_H264_PPS_FLAG_CONSTRAINED_INTRA_PRED ; 
 int V4L2_H264_PPS_FLAG_ENTROPY_CODING_MODE ; 
 int V4L2_H264_PPS_FLAG_TRANSFORM_8X8_MODE ; 
 int V4L2_H264_PPS_FLAG_WEIGHTED_PRED ; 
 int V4L2_H264_SLICE_FLAG_BOTTOM_FIELD ; 
 int V4L2_H264_SLICE_FLAG_DIRECT_SPATIAL_MV_PRED ; 
 int V4L2_H264_SLICE_FLAG_FIELD_PIC ; 
 int V4L2_H264_SLICE_TYPE_B ; 
 int V4L2_H264_SLICE_TYPE_P ; 
 int V4L2_H264_SLICE_TYPE_SP ; 
 int V4L2_H264_SPS_FLAG_DIRECT_8X8_INFERENCE ; 
 int V4L2_H264_SPS_FLAG_FRAME_MBS_ONLY ; 
 int V4L2_H264_SPS_FLAG_MB_ADAPTIVE_FRAME_FIELD ; 
 int /*<<< orphan*/  VE_H264_CTRL ; 
 int VE_H264_CTRL_DECODE_ERR_INT ; 
 int VE_H264_CTRL_SLICE_DECODE_INT ; 
 int VE_H264_CTRL_VLD_DATA_REQ_INT ; 
 int /*<<< orphan*/  VE_H264_PPS ; 
 int VE_H264_PPS_CONSTRAINED_INTRA_PRED ; 
 int VE_H264_PPS_ENTROPY_CODING_MODE ; 
 int VE_H264_PPS_TRANSFORM_8X8_MODE ; 
 int VE_H264_PPS_WEIGHTED_PRED ; 
 int /*<<< orphan*/  VE_H264_SHS ; 
 int /*<<< orphan*/  VE_H264_SHS2 ; 
 int VE_H264_SHS2_NUM_REF_IDX_ACTIVE_OVRD ; 
 int VE_H264_SHS_BOTTOM_FIELD ; 
 int VE_H264_SHS_DIRECT_SPATIAL_MV_PRED ; 
 int VE_H264_SHS_FIELD_PIC ; 
 int VE_H264_SHS_FIRST_SLICE_IN_PIC ; 
 int /*<<< orphan*/  VE_H264_SHS_QP ; 
 int /*<<< orphan*/  VE_H264_SPS ; 
 int VE_H264_SPS_DIRECT_8X8_INFERENCE ; 
 int VE_H264_SPS_MBS_ONLY ; 
 int VE_H264_SPS_MB_ADAPTIVE_FRAME_FIELD ; 
 int /*<<< orphan*/  VE_H264_STATUS ; 
 int /*<<< orphan*/  VE_H264_TRIGGER_TYPE ; 
 int VE_H264_TRIGGER_TYPE_INIT_SWDEC ; 
 int /*<<< orphan*/  VE_H264_VLD_ADDR ; 
 int VE_H264_VLD_ADDR_FIRST ; 
 int VE_H264_VLD_ADDR_LAST ; 
 int VE_H264_VLD_ADDR_VAL (int) ; 
 int VE_H264_VLD_ADDR_VALID ; 
 int /*<<< orphan*/  VE_H264_VLD_END ; 
 int /*<<< orphan*/  VE_H264_VLD_LEN ; 
 int /*<<< orphan*/  VE_H264_VLD_OFFSET ; 
 int cedrus_read (struct cedrus_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cedrus_write (struct cedrus_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cedrus_write_pred_weight_table (struct cedrus_ctx*,struct cedrus_run*) ; 
 int /*<<< orphan*/  cedrus_write_ref_list0 (struct cedrus_ctx*,struct cedrus_run*) ; 
 int /*<<< orphan*/  cedrus_write_ref_list1 (struct cedrus_ctx*,struct cedrus_run*) ; 
 int vb2_dma_contig_plane_dma_addr (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 int vb2_get_plane_payload (struct vb2_buffer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cedrus_set_params(struct cedrus_ctx *ctx,
			      struct cedrus_run *run)
{
	const struct v4l2_ctrl_h264_decode_params *decode = run->h264.decode_params;
	const struct v4l2_ctrl_h264_slice_params *slice = run->h264.slice_params;
	const struct v4l2_ctrl_h264_pps *pps = run->h264.pps;
	const struct v4l2_ctrl_h264_sps *sps = run->h264.sps;
	struct vb2_buffer *src_buf = &run->src->vb2_buf;
	struct cedrus_dev *dev = ctx->dev;
	dma_addr_t src_buf_addr;
	u32 offset = slice->header_bit_size;
	u32 len = (slice->size * 8) - offset;
	u32 reg;

	cedrus_write(dev, VE_H264_VLD_LEN, len);
	cedrus_write(dev, VE_H264_VLD_OFFSET, offset);

	src_buf_addr = vb2_dma_contig_plane_dma_addr(src_buf, 0);
	cedrus_write(dev, VE_H264_VLD_END,
		     src_buf_addr + vb2_get_plane_payload(src_buf, 0));
	cedrus_write(dev, VE_H264_VLD_ADDR,
		     VE_H264_VLD_ADDR_VAL(src_buf_addr) |
		     VE_H264_VLD_ADDR_FIRST | VE_H264_VLD_ADDR_VALID |
		     VE_H264_VLD_ADDR_LAST);

	/*
	 * FIXME: Since the bitstream parsing is done in software, and
	 * in userspace, this shouldn't be needed anymore. But it
	 * turns out that removing it breaks the decoding process,
	 * without any clear indication why.
	 */
	cedrus_write(dev, VE_H264_TRIGGER_TYPE,
		     VE_H264_TRIGGER_TYPE_INIT_SWDEC);

	if (((pps->flags & V4L2_H264_PPS_FLAG_WEIGHTED_PRED) &&
	     (slice->slice_type == V4L2_H264_SLICE_TYPE_P ||
	      slice->slice_type == V4L2_H264_SLICE_TYPE_SP)) ||
	    (pps->weighted_bipred_idc == 1 &&
	     slice->slice_type == V4L2_H264_SLICE_TYPE_B))
		cedrus_write_pred_weight_table(ctx, run);

	if ((slice->slice_type == V4L2_H264_SLICE_TYPE_P) ||
	    (slice->slice_type == V4L2_H264_SLICE_TYPE_SP) ||
	    (slice->slice_type == V4L2_H264_SLICE_TYPE_B))
		cedrus_write_ref_list0(ctx, run);

	if (slice->slice_type == V4L2_H264_SLICE_TYPE_B)
		cedrus_write_ref_list1(ctx, run);

	// picture parameters
	reg = 0;
	/*
	 * FIXME: the kernel headers are allowing the default value to
	 * be passed, but the libva doesn't give us that.
	 */
	reg |= (slice->num_ref_idx_l0_active_minus1 & 0x1f) << 10;
	reg |= (slice->num_ref_idx_l1_active_minus1 & 0x1f) << 5;
	reg |= (pps->weighted_bipred_idc & 0x3) << 2;
	if (pps->flags & V4L2_H264_PPS_FLAG_ENTROPY_CODING_MODE)
		reg |= VE_H264_PPS_ENTROPY_CODING_MODE;
	if (pps->flags & V4L2_H264_PPS_FLAG_WEIGHTED_PRED)
		reg |= VE_H264_PPS_WEIGHTED_PRED;
	if (pps->flags & V4L2_H264_PPS_FLAG_CONSTRAINED_INTRA_PRED)
		reg |= VE_H264_PPS_CONSTRAINED_INTRA_PRED;
	if (pps->flags & V4L2_H264_PPS_FLAG_TRANSFORM_8X8_MODE)
		reg |= VE_H264_PPS_TRANSFORM_8X8_MODE;
	cedrus_write(dev, VE_H264_PPS, reg);

	// sequence parameters
	reg = 0;
	reg |= (sps->chroma_format_idc & 0x7) << 19;
	reg |= (sps->pic_width_in_mbs_minus1 & 0xff) << 8;
	reg |= sps->pic_height_in_map_units_minus1 & 0xff;
	if (sps->flags & V4L2_H264_SPS_FLAG_FRAME_MBS_ONLY)
		reg |= VE_H264_SPS_MBS_ONLY;
	if (sps->flags & V4L2_H264_SPS_FLAG_MB_ADAPTIVE_FRAME_FIELD)
		reg |= VE_H264_SPS_MB_ADAPTIVE_FRAME_FIELD;
	if (sps->flags & V4L2_H264_SPS_FLAG_DIRECT_8X8_INFERENCE)
		reg |= VE_H264_SPS_DIRECT_8X8_INFERENCE;
	cedrus_write(dev, VE_H264_SPS, reg);

	// slice parameters
	reg = 0;
	reg |= decode->nal_ref_idc ? BIT(12) : 0;
	reg |= (slice->slice_type & 0xf) << 8;
	reg |= slice->cabac_init_idc & 0x3;
	reg |= VE_H264_SHS_FIRST_SLICE_IN_PIC;
	if (slice->flags & V4L2_H264_SLICE_FLAG_FIELD_PIC)
		reg |= VE_H264_SHS_FIELD_PIC;
	if (slice->flags & V4L2_H264_SLICE_FLAG_BOTTOM_FIELD)
		reg |= VE_H264_SHS_BOTTOM_FIELD;
	if (slice->flags & V4L2_H264_SLICE_FLAG_DIRECT_SPATIAL_MV_PRED)
		reg |= VE_H264_SHS_DIRECT_SPATIAL_MV_PRED;
	cedrus_write(dev, VE_H264_SHS, reg);

	reg = 0;
	reg |= VE_H264_SHS2_NUM_REF_IDX_ACTIVE_OVRD;
	reg |= (slice->num_ref_idx_l0_active_minus1 & 0x1f) << 24;
	reg |= (slice->num_ref_idx_l1_active_minus1 & 0x1f) << 16;
	reg |= (slice->disable_deblocking_filter_idc & 0x3) << 8;
	reg |= (slice->slice_alpha_c0_offset_div2 & 0xf) << 4;
	reg |= slice->slice_beta_offset_div2 & 0xf;
	cedrus_write(dev, VE_H264_SHS2, reg);

	reg = 0;
	reg |= (pps->second_chroma_qp_index_offset & 0x3f) << 16;
	reg |= (pps->chroma_qp_index_offset & 0x3f) << 8;
	reg |= (pps->pic_init_qp_minus26 + 26 + slice->slice_qp_delta) & 0x3f;
	cedrus_write(dev, VE_H264_SHS_QP, reg);

	// clear status flags
	cedrus_write(dev, VE_H264_STATUS, cedrus_read(dev, VE_H264_STATUS));

	// enable int
	cedrus_write(dev, VE_H264_CTRL,
		     VE_H264_CTRL_SLICE_DECODE_INT |
		     VE_H264_CTRL_DECODE_ERR_INT |
		     VE_H264_CTRL_VLD_DATA_REQ_INT);
}