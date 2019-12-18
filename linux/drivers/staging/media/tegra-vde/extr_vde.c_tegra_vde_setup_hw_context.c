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
struct video_frame {int flags; int aux_addr; } ;
struct tegra_vde_h264_decoder_ctx {int pic_width_in_mbs; int pic_height_in_mbs; int level_idc; int log2_max_pic_order_cnt_lsb; int pic_order_cnt_type; int log2_max_frame_num; int pic_init_qp; int chroma_qp_index_offset; int num_ref_idx_l0_active_minus1; int num_ref_idx_l1_active_minus1; int /*<<< orphan*/  baseline_profile; scalar_t__ dpb_frames_nb; int /*<<< orphan*/  direct_8x8_inference_flag; int /*<<< orphan*/  constrained_intra_pred_flag; int /*<<< orphan*/  pic_order_present_flag; int /*<<< orphan*/  deblocking_filter_control_present_flag; int /*<<< orphan*/  dpb_ref_frames_with_earlier_poc_nb; } ;
struct TYPE_2__ {struct device* parent; } ;
struct tegra_vde {int iram_lists_addr; int /*<<< orphan*/  mbe; int /*<<< orphan*/  sxe; int /*<<< orphan*/  bsev; scalar_t__ iram; int /*<<< orphan*/  mce; int /*<<< orphan*/  tfe; int /*<<< orphan*/  frameid; int /*<<< orphan*/  vdma; int /*<<< orphan*/  ppe; TYPE_1__ miscdev; } ;
struct device {int dummy; } ;
typedef  size_t dma_addr_t ;

/* Variables and functions */
 int BSE_CONFIG ; 
 int BSE_INT_ENB ; 
 int CMDQUE_CONTROL ; 
 int FLAG_B_FRAME ; 
 int FLAG_REFERENCE ; 
 size_t GENMASK (int,int) ; 
 int INTR_STATUS ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  tegra_setup_frameidx (struct tegra_vde*,struct video_frame*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  tegra_vde_mbe_set_0xa_reg (struct tegra_vde*,int,int) ; 
 int tegra_vde_push_to_bsev_icmdqueue (struct tegra_vde*,int,int) ; 
 int /*<<< orphan*/  tegra_vde_set_bits (struct tegra_vde*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tegra_vde_setup_iram_tables (struct tegra_vde*,struct video_frame*,scalar_t__,int /*<<< orphan*/ ) ; 
 int tegra_vde_setup_mbe_frame_idx (struct tegra_vde*,scalar_t__,int) ; 
 int tegra_vde_wait_bsev (struct tegra_vde*,int) ; 
 int tegra_vde_wait_mbe (struct tegra_vde*) ; 
 int /*<<< orphan*/  tegra_vde_writel (struct tegra_vde*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int tegra_vde_setup_hw_context(struct tegra_vde *vde,
				      struct tegra_vde_h264_decoder_ctx *ctx,
				      struct video_frame *dpb_frames,
				      dma_addr_t bitstream_data_addr,
				      size_t bitstream_data_size,
				      unsigned int macroblocks_nb)
{
	struct device *dev = vde->miscdev.parent;
	u32 value;
	int err;

	tegra_vde_set_bits(vde, 0x000A, vde->sxe, 0xF0);
	tegra_vde_set_bits(vde, 0x000B, vde->bsev, CMDQUE_CONTROL);
	tegra_vde_set_bits(vde, 0x8002, vde->mbe, 0x50);
	tegra_vde_set_bits(vde, 0x000A, vde->mbe, 0xA0);
	tegra_vde_set_bits(vde, 0x000A, vde->ppe, 0x14);
	tegra_vde_set_bits(vde, 0x000A, vde->ppe, 0x28);
	tegra_vde_set_bits(vde, 0x0A00, vde->mce, 0x08);
	tegra_vde_set_bits(vde, 0x000A, vde->tfe, 0x00);
	tegra_vde_set_bits(vde, 0x0005, vde->vdma, 0x04);

	tegra_vde_writel(vde, 0x00000000, vde->vdma, 0x1C);
	tegra_vde_writel(vde, 0x00000000, vde->vdma, 0x00);
	tegra_vde_writel(vde, 0x00000007, vde->vdma, 0x04);
	tegra_vde_writel(vde, 0x00000007, vde->frameid, 0x200);
	tegra_vde_writel(vde, 0x00000005, vde->tfe, 0x04);
	tegra_vde_writel(vde, 0x00000000, vde->mbe, 0x84);
	tegra_vde_writel(vde, 0x00000010, vde->sxe, 0x08);
	tegra_vde_writel(vde, 0x00000150, vde->sxe, 0x54);
	tegra_vde_writel(vde, 0x0000054C, vde->sxe, 0x58);
	tegra_vde_writel(vde, 0x00000E34, vde->sxe, 0x5C);
	tegra_vde_writel(vde, 0x063C063C, vde->mce, 0x10);
	tegra_vde_writel(vde, 0x0003FC00, vde->bsev, INTR_STATUS);
	tegra_vde_writel(vde, 0x0000150D, vde->bsev, BSE_CONFIG);
	tegra_vde_writel(vde, 0x00000100, vde->bsev, BSE_INT_ENB);
	tegra_vde_writel(vde, 0x00000000, vde->bsev, 0x98);
	tegra_vde_writel(vde, 0x00000060, vde->bsev, 0x9C);

	memset(vde->iram + 128, 0, macroblocks_nb / 2);

	tegra_setup_frameidx(vde, dpb_frames, ctx->dpb_frames_nb,
			     ctx->pic_width_in_mbs, ctx->pic_height_in_mbs);

	tegra_vde_setup_iram_tables(vde, dpb_frames,
				    ctx->dpb_frames_nb - 1,
				    ctx->dpb_ref_frames_with_earlier_poc_nb);

	/*
	 * The IRAM mapping is write-combine, ensure that CPU buffers have
	 * been flushed at this point.
	 */
	wmb();

	tegra_vde_writel(vde, 0x00000000, vde->bsev, 0x8C);
	tegra_vde_writel(vde, bitstream_data_addr + bitstream_data_size,
			 vde->bsev, 0x54);

	value = ctx->pic_width_in_mbs << 11 | ctx->pic_height_in_mbs << 3;

	tegra_vde_writel(vde, value, vde->bsev, 0x88);

	err = tegra_vde_wait_bsev(vde, false);
	if (err)
		return err;

	err = tegra_vde_push_to_bsev_icmdqueue(vde, 0x800003FC, false);
	if (err)
		return err;

	value = 0x01500000;
	value |= ((vde->iram_lists_addr + 512) >> 2) & 0xFFFF;

	err = tegra_vde_push_to_bsev_icmdqueue(vde, value, true);
	if (err)
		return err;

	err = tegra_vde_push_to_bsev_icmdqueue(vde, 0x840F054C, false);
	if (err)
		return err;

	err = tegra_vde_push_to_bsev_icmdqueue(vde, 0x80000080, false);
	if (err)
		return err;

	value = 0x0E340000 | ((vde->iram_lists_addr >> 2) & 0xFFFF);

	err = tegra_vde_push_to_bsev_icmdqueue(vde, value, true);
	if (err)
		return err;

	value = 0x00800005;
	value |= ctx->pic_width_in_mbs << 11;
	value |= ctx->pic_height_in_mbs << 3;

	tegra_vde_writel(vde, value, vde->sxe, 0x10);

	value = !ctx->baseline_profile << 17;
	value |= ctx->level_idc << 13;
	value |= ctx->log2_max_pic_order_cnt_lsb << 7;
	value |= ctx->pic_order_cnt_type << 5;
	value |= ctx->log2_max_frame_num;

	tegra_vde_writel(vde, value, vde->sxe, 0x40);

	value = ctx->pic_init_qp << 25;
	value |= !!(ctx->deblocking_filter_control_present_flag) << 2;
	value |= !!ctx->pic_order_present_flag;

	tegra_vde_writel(vde, value, vde->sxe, 0x44);

	value = ctx->chroma_qp_index_offset;
	value |= ctx->num_ref_idx_l0_active_minus1 << 5;
	value |= ctx->num_ref_idx_l1_active_minus1 << 10;
	value |= !!ctx->constrained_intra_pred_flag << 15;

	tegra_vde_writel(vde, value, vde->sxe, 0x48);

	value = 0x0C000000;
	value |= !!(dpb_frames[0].flags & FLAG_B_FRAME) << 24;

	tegra_vde_writel(vde, value, vde->sxe, 0x4C);

	value = 0x03800000;
	value |= bitstream_data_size & GENMASK(19, 15);

	tegra_vde_writel(vde, value, vde->sxe, 0x68);

	tegra_vde_writel(vde, bitstream_data_addr, vde->sxe, 0x6C);

	value = 0x10000005;
	value |= ctx->pic_width_in_mbs << 11;
	value |= ctx->pic_height_in_mbs << 3;

	tegra_vde_writel(vde, value, vde->mbe, 0x80);

	value = 0x26800000;
	value |= ctx->level_idc << 4;
	value |= !ctx->baseline_profile << 1;
	value |= !!ctx->direct_8x8_inference_flag;

	tegra_vde_writel(vde, value, vde->mbe, 0x80);

	tegra_vde_writel(vde, 0xF4000001, vde->mbe, 0x80);
	tegra_vde_writel(vde, 0x20000000, vde->mbe, 0x80);
	tegra_vde_writel(vde, 0xF4000101, vde->mbe, 0x80);

	value = 0x20000000;
	value |= ctx->chroma_qp_index_offset << 8;

	tegra_vde_writel(vde, value, vde->mbe, 0x80);

	err = tegra_vde_setup_mbe_frame_idx(vde,
					    ctx->dpb_frames_nb - 1,
					    ctx->pic_order_cnt_type == 0);
	if (err) {
		dev_err(dev, "MBE frames setup failed %d\n", err);
		return err;
	}

	tegra_vde_mbe_set_0xa_reg(vde, 0, 0x000009FC);
	tegra_vde_mbe_set_0xa_reg(vde, 2, 0x61DEAD00);
	tegra_vde_mbe_set_0xa_reg(vde, 4, 0x62DEAD00);
	tegra_vde_mbe_set_0xa_reg(vde, 6, 0x63DEAD00);
	tegra_vde_mbe_set_0xa_reg(vde, 8, dpb_frames[0].aux_addr);

	value = 0xFC000000;
	value |= !!(dpb_frames[0].flags & FLAG_B_FRAME) << 2;

	if (!ctx->baseline_profile)
		value |= !!(dpb_frames[0].flags & FLAG_REFERENCE) << 1;

	tegra_vde_writel(vde, value, vde->mbe, 0x80);

	err = tegra_vde_wait_mbe(vde);
	if (err) {
		dev_err(dev, "MBE programming failed %d\n", err);
		return err;
	}

	return 0;
}