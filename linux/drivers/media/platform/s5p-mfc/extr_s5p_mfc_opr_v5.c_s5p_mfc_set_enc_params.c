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
struct s5p_mfc_enc_params {unsigned int gop_size; unsigned int slice_mode; unsigned int slice_mb; unsigned int slice_bit; unsigned int intra_refresh_mb; int pad_cr; int pad_cb; unsigned int pad_luma; int rc_frame; unsigned int rc_bitrate; unsigned int rc_reaction_coeff; int seq_hdr_mode; int frame_skip_mode; unsigned int fixed_target_bit; scalar_t__ pad; } ;
struct s5p_mfc_dev {int dummy; } ;
struct s5p_mfc_ctx {unsigned int img_width; unsigned int img_height; TYPE_1__* src_fmt; struct s5p_mfc_enc_params enc_params; struct s5p_mfc_dev* dev; } ;
struct TYPE_2__ {scalar_t__ fourcc; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT_ENC_CONTROL ; 
 int /*<<< orphan*/  RC_CONTROL_CONFIG ; 
 int /*<<< orphan*/  S5P_FIMV_ENC_B_RECON_WRITE_ON ; 
 int /*<<< orphan*/  S5P_FIMV_ENC_CIR_CTRL ; 
 int /*<<< orphan*/  S5P_FIMV_ENC_HSIZE_PX ; 
 int /*<<< orphan*/  S5P_FIMV_ENC_MAP_FOR_CUR ; 
 int /*<<< orphan*/  S5P_FIMV_ENC_MSLICE_BIT ; 
 int /*<<< orphan*/  S5P_FIMV_ENC_MSLICE_CTRL ; 
 int /*<<< orphan*/  S5P_FIMV_ENC_MSLICE_MB ; 
 int /*<<< orphan*/  S5P_FIMV_ENC_PADDING_CTRL ; 
 int /*<<< orphan*/  S5P_FIMV_ENC_PIC_TYPE_CTRL ; 
 int /*<<< orphan*/  S5P_FIMV_ENC_RC_BIT_RATE ; 
 int /*<<< orphan*/  S5P_FIMV_ENC_RC_CONFIG ; 
 int /*<<< orphan*/  S5P_FIMV_ENC_RC_RPARA ; 
 int /*<<< orphan*/  S5P_FIMV_ENC_VSIZE_PX ; 
 unsigned int V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_MAX_BYTES ; 
 unsigned int V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_MAX_MB ; 
 scalar_t__ V4L2_PIX_FMT_NV12M ; 
 scalar_t__ V4L2_PIX_FMT_NV12MT ; 
 unsigned int mfc_read (struct s5p_mfc_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfc_write (struct s5p_mfc_dev*,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int s5p_mfc_read_info_v5 (struct s5p_mfc_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5p_mfc_write_info_v5 (struct s5p_mfc_ctx*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5p_mfc_set_enc_params(struct s5p_mfc_ctx *ctx)
{
	struct s5p_mfc_dev *dev = ctx->dev;
	struct s5p_mfc_enc_params *p = &ctx->enc_params;
	unsigned int reg;
	unsigned int shm;

	/* width */
	mfc_write(dev, ctx->img_width, S5P_FIMV_ENC_HSIZE_PX);
	/* height */
	mfc_write(dev, ctx->img_height, S5P_FIMV_ENC_VSIZE_PX);
	/* pictype : enable, IDR period */
	reg = mfc_read(dev, S5P_FIMV_ENC_PIC_TYPE_CTRL);
	reg |= (1 << 18);
	reg &= ~(0xFFFF);
	reg |= p->gop_size;
	mfc_write(dev, reg, S5P_FIMV_ENC_PIC_TYPE_CTRL);
	mfc_write(dev, 0, S5P_FIMV_ENC_B_RECON_WRITE_ON);
	/* multi-slice control */
	/* multi-slice MB number or bit size */
	mfc_write(dev, p->slice_mode, S5P_FIMV_ENC_MSLICE_CTRL);
	if (p->slice_mode == V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_MAX_MB) {
		mfc_write(dev, p->slice_mb, S5P_FIMV_ENC_MSLICE_MB);
	} else if (p->slice_mode == V4L2_MPEG_VIDEO_MULTI_SLICE_MODE_MAX_BYTES) {
		mfc_write(dev, p->slice_bit, S5P_FIMV_ENC_MSLICE_BIT);
	} else {
		mfc_write(dev, 0, S5P_FIMV_ENC_MSLICE_MB);
		mfc_write(dev, 0, S5P_FIMV_ENC_MSLICE_BIT);
	}
	/* cyclic intra refresh */
	mfc_write(dev, p->intra_refresh_mb, S5P_FIMV_ENC_CIR_CTRL);
	/* memory structure cur. frame */
	if (ctx->src_fmt->fourcc == V4L2_PIX_FMT_NV12M)
		mfc_write(dev, 0, S5P_FIMV_ENC_MAP_FOR_CUR);
	else if (ctx->src_fmt->fourcc == V4L2_PIX_FMT_NV12MT)
		mfc_write(dev, 3, S5P_FIMV_ENC_MAP_FOR_CUR);
	/* padding control & value */
	reg = mfc_read(dev, S5P_FIMV_ENC_PADDING_CTRL);
	if (p->pad) {
		/** enable */
		reg |= (1UL << 31);
		/** cr value */
		reg &= ~(0xFF << 16);
		reg |= (p->pad_cr << 16);
		/** cb value */
		reg &= ~(0xFF << 8);
		reg |= (p->pad_cb << 8);
		/** y value */
		reg &= ~(0xFF);
		reg |= (p->pad_luma);
	} else {
		/** disable & all value clear */
		reg = 0;
	}
	mfc_write(dev, reg, S5P_FIMV_ENC_PADDING_CTRL);
	/* rate control config. */
	reg = mfc_read(dev, S5P_FIMV_ENC_RC_CONFIG);
	/** frame-level rate control */
	reg &= ~(0x1 << 9);
	reg |= (p->rc_frame << 9);
	mfc_write(dev, reg, S5P_FIMV_ENC_RC_CONFIG);
	/* bit rate */
	if (p->rc_frame)
		mfc_write(dev, p->rc_bitrate,
			S5P_FIMV_ENC_RC_BIT_RATE);
	else
		mfc_write(dev, 0, S5P_FIMV_ENC_RC_BIT_RATE);
	/* reaction coefficient */
	if (p->rc_frame)
		mfc_write(dev, p->rc_reaction_coeff, S5P_FIMV_ENC_RC_RPARA);
	shm = s5p_mfc_read_info_v5(ctx, EXT_ENC_CONTROL);
	/* seq header ctrl */
	shm &= ~(0x1 << 3);
	shm |= (p->seq_hdr_mode << 3);
	/* frame skip mode */
	shm &= ~(0x3 << 1);
	shm |= (p->frame_skip_mode << 1);
	s5p_mfc_write_info_v5(ctx, shm, EXT_ENC_CONTROL);
	/* fixed target bit */
	s5p_mfc_write_info_v5(ctx, p->fixed_target_bit, RC_CONTROL_CONFIG);
	return 0;
}