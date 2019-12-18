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
struct s5p_mfc_regs {int /*<<< orphan*/  e_metadata_buffer_size; int /*<<< orphan*/  e_metadata_buffer_addr; int /*<<< orphan*/  e_min_bit_count; int /*<<< orphan*/  e_max_bit_count; int /*<<< orphan*/  e_bit_count_enable; int /*<<< orphan*/  e_picture_tag; int /*<<< orphan*/  e_rc_roi_ctrl; int /*<<< orphan*/  e_param_change; int /*<<< orphan*/  e_roi_buffer_addr; int /*<<< orphan*/  e_frame_insertion; int /*<<< orphan*/  e_mv_ver_range; int /*<<< orphan*/  e_mv_hor_range; int /*<<< orphan*/  e_rc_config; int /*<<< orphan*/  e_enc_options; int /*<<< orphan*/  e_rc_mode; int /*<<< orphan*/  e_rc_bit_rate; int /*<<< orphan*/  e_padding_ctrl; int /*<<< orphan*/  pixel_format; int /*<<< orphan*/  e_ir_size; int /*<<< orphan*/  e_gop_config; int /*<<< orphan*/  e_frame_crop_offset; int /*<<< orphan*/  e_cropped_frame_height; int /*<<< orphan*/  e_cropped_frame_width; int /*<<< orphan*/  e_frame_height; int /*<<< orphan*/  e_frame_width; } ;
struct s5p_mfc_enc_params {int gop_size; scalar_t__ slice_mode; int intra_refresh_mb; int pad_cr; int pad_cb; int pad_luma; int rc_frame; int rc_bitrate; scalar_t__ rc_reaction_coeff; int seq_hdr_mode; int frame_skip_mode; unsigned int mv_h_range; unsigned int mv_v_range; scalar_t__ pad; int /*<<< orphan*/  slice_bit; int /*<<< orphan*/  slice_mb; } ;
struct s5p_mfc_dev {struct s5p_mfc_regs* mfc_regs; } ;
struct TYPE_3__ {int /*<<< orphan*/  bits; int /*<<< orphan*/  mb; } ;
struct s5p_mfc_ctx {int img_width; int img_height; scalar_t__ slice_mode; TYPE_2__* src_fmt; TYPE_1__ slice_size; struct s5p_mfc_enc_params enc_params; struct s5p_mfc_dev* dev; } ;
struct TYPE_4__ {scalar_t__ fourcc; } ;

/* Variables and functions */
 unsigned int S5P_FIMV_E_MV_RANGE_V6_MASK ; 
 scalar_t__ TIGHT_CBR_MAX ; 
 scalar_t__ V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_MAX_BYTES ; 
 scalar_t__ V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_MAX_MB ; 
 scalar_t__ V4L2_PIX_FMT_NV12M ; 
 scalar_t__ V4L2_PIX_FMT_NV12MT_16X16 ; 
 scalar_t__ V4L2_PIX_FMT_NV21M ; 
 int /*<<< orphan*/  mfc_debug_enter () ; 
 int /*<<< orphan*/  mfc_debug_leave () ; 
 unsigned int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5p_mfc_set_slice_mode (struct s5p_mfc_ctx*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5p_mfc_set_enc_params(struct s5p_mfc_ctx *ctx)
{
	struct s5p_mfc_dev *dev = ctx->dev;
	const struct s5p_mfc_regs *mfc_regs = dev->mfc_regs;
	struct s5p_mfc_enc_params *p = &ctx->enc_params;
	unsigned int reg = 0;

	mfc_debug_enter();

	/* width */
	writel(ctx->img_width, mfc_regs->e_frame_width); /* 16 align */
	/* height */
	writel(ctx->img_height, mfc_regs->e_frame_height); /* 16 align */

	/* cropped width */
	writel(ctx->img_width, mfc_regs->e_cropped_frame_width);
	/* cropped height */
	writel(ctx->img_height, mfc_regs->e_cropped_frame_height);
	/* cropped offset */
	writel(0x0, mfc_regs->e_frame_crop_offset);

	/* pictype : IDR period */
	reg = 0;
	reg |= p->gop_size & 0xFFFF;
	writel(reg, mfc_regs->e_gop_config);

	/* multi-slice control */
	/* multi-slice MB number or bit size */
	ctx->slice_mode = p->slice_mode;
	reg = 0;
	if (p->slice_mode == V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_MAX_MB) {
		reg |= (0x1 << 3);
		writel(reg, mfc_regs->e_enc_options);
		ctx->slice_size.mb = p->slice_mb;
	} else if (p->slice_mode == V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_MAX_BYTES) {
		reg |= (0x1 << 3);
		writel(reg, mfc_regs->e_enc_options);
		ctx->slice_size.bits = p->slice_bit;
	} else {
		reg &= ~(0x1 << 3);
		writel(reg, mfc_regs->e_enc_options);
	}

	s5p_mfc_set_slice_mode(ctx);

	/* cyclic intra refresh */
	writel(p->intra_refresh_mb, mfc_regs->e_ir_size);
	reg = readl(mfc_regs->e_enc_options);
	if (p->intra_refresh_mb == 0)
		reg &= ~(0x1 << 4);
	else
		reg |= (0x1 << 4);
	writel(reg, mfc_regs->e_enc_options);

	/* 'NON_REFERENCE_STORE_ENABLE' for debugging */
	reg = readl(mfc_regs->e_enc_options);
	reg &= ~(0x1 << 9);
	writel(reg, mfc_regs->e_enc_options);

	/* memory structure cur. frame */
	if (ctx->src_fmt->fourcc == V4L2_PIX_FMT_NV12M) {
		/* 0: Linear, 1: 2D tiled*/
		reg = readl(mfc_regs->e_enc_options);
		reg &= ~(0x1 << 7);
		writel(reg, mfc_regs->e_enc_options);
		/* 0: NV12(CbCr), 1: NV21(CrCb) */
		writel(0x0, mfc_regs->pixel_format);
	} else if (ctx->src_fmt->fourcc == V4L2_PIX_FMT_NV21M) {
		/* 0: Linear, 1: 2D tiled*/
		reg = readl(mfc_regs->e_enc_options);
		reg &= ~(0x1 << 7);
		writel(reg, mfc_regs->e_enc_options);
		/* 0: NV12(CbCr), 1: NV21(CrCb) */
		writel(0x1, mfc_regs->pixel_format);
	} else if (ctx->src_fmt->fourcc == V4L2_PIX_FMT_NV12MT_16X16) {
		/* 0: Linear, 1: 2D tiled*/
		reg = readl(mfc_regs->e_enc_options);
		reg |= (0x1 << 7);
		writel(reg, mfc_regs->e_enc_options);
		/* 0: NV12(CbCr), 1: NV21(CrCb) */
		writel(0x0, mfc_regs->pixel_format);
	}

	/* memory structure recon. frame */
	/* 0: Linear, 1: 2D tiled */
	reg = readl(mfc_regs->e_enc_options);
	reg |= (0x1 << 8);
	writel(reg, mfc_regs->e_enc_options);

	/* padding control & value */
	writel(0x0, mfc_regs->e_padding_ctrl);
	if (p->pad) {
		reg = 0;
		/** enable */
		reg |= (1UL << 31);
		/** cr value */
		reg |= ((p->pad_cr & 0xFF) << 16);
		/** cb value */
		reg |= ((p->pad_cb & 0xFF) << 8);
		/** y value */
		reg |= p->pad_luma & 0xFF;
		writel(reg, mfc_regs->e_padding_ctrl);
	}

	/* rate control config. */
	reg = 0;
	/* frame-level rate control */
	reg |= ((p->rc_frame & 0x1) << 9);
	writel(reg, mfc_regs->e_rc_config);

	/* bit rate */
	if (p->rc_frame)
		writel(p->rc_bitrate,
			mfc_regs->e_rc_bit_rate);
	else
		writel(1, mfc_regs->e_rc_bit_rate);

	/* reaction coefficient */
	if (p->rc_frame) {
		if (p->rc_reaction_coeff < TIGHT_CBR_MAX) /* tight CBR */
			writel(1, mfc_regs->e_rc_mode);
		else					  /* loose CBR */
			writel(2, mfc_regs->e_rc_mode);
	}

	/* seq header ctrl */
	reg = readl(mfc_regs->e_enc_options);
	reg &= ~(0x1 << 2);
	reg |= ((p->seq_hdr_mode & 0x1) << 2);

	/* frame skip mode */
	reg &= ~(0x3);
	reg |= (p->frame_skip_mode & 0x3);
	writel(reg, mfc_regs->e_enc_options);

	/* 'DROP_CONTROL_ENABLE', disable */
	reg = readl(mfc_regs->e_rc_config);
	reg &= ~(0x1 << 10);
	writel(reg, mfc_regs->e_rc_config);

	/* setting for MV range [16, 256] */
	reg = (p->mv_h_range & S5P_FIMV_E_MV_RANGE_V6_MASK);
	writel(reg, mfc_regs->e_mv_hor_range);

	reg = (p->mv_v_range & S5P_FIMV_E_MV_RANGE_V6_MASK);
	writel(reg, mfc_regs->e_mv_ver_range);

	writel(0x0, mfc_regs->e_frame_insertion);
	writel(0x0, mfc_regs->e_roi_buffer_addr);
	writel(0x0, mfc_regs->e_param_change);
	writel(0x0, mfc_regs->e_rc_roi_ctrl);
	writel(0x0, mfc_regs->e_picture_tag);

	writel(0x0, mfc_regs->e_bit_count_enable);
	writel(0x0, mfc_regs->e_max_bit_count);
	writel(0x0, mfc_regs->e_min_bit_count);

	writel(0x0, mfc_regs->e_metadata_buffer_addr);
	writel(0x0, mfc_regs->e_metadata_buffer_size);

	mfc_debug_leave();

	return 0;
}