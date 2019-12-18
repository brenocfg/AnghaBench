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
struct s5p_mfc_regs {scalar_t__ e_h264_fmo_num_slice_grp_minus1; scalar_t__ e_h264_fmo_slice_grp_map_type; scalar_t__ e_h264_fmo_slice_grp_change_rate_minus1; scalar_t__ e_h264_fmo_slice_grp_change_dir; int /*<<< orphan*/  e_h264_fmo_run_length_minus1_0; scalar_t__ e_h264_frame_packing_sei_info; scalar_t__ e_h264_options; scalar_t__ e_h264_num_t_layer; scalar_t__ e_h264_hierarchical_qp_layer0; scalar_t__ e_h264_i_period; scalar_t__ e_extended_sar; scalar_t__ e_aspect_ratio; scalar_t__ e_mb_rc_config; scalar_t__ e_h264_lf_beta_offset; scalar_t__ e_h264_lf_alpha_offset; scalar_t__ e_cropped_frame_height; scalar_t__ e_frame_height; scalar_t__ e_vbv_init_delay; scalar_t__ e_vbv_buffer_size; scalar_t__ e_rc_frame_rate; scalar_t__ e_fixed_picture_qp; scalar_t__ e_rc_qp_bound; scalar_t__ e_rc_config; scalar_t__ e_picture_profile; scalar_t__ e_gop_config; } ;
struct s5p_mfc_h264_enc_params {int level; int profile; int rc_frame_qp; int rc_max_qp; int rc_min_qp; int rc_b_frame_qp; int rc_p_frame_qp; int cpb_size; int interlace; int loop_filter_mode; int loop_filter_alpha; int loop_filter_beta; int entropy_mode; int num_ref_pic_4p; int _8x8_transform; int rc_mb_dark; int rc_mb_smooth; int rc_mb_static; int rc_mb_activity; int vui_sar; int vui_sar_idc; int vui_ext_sar_width; int vui_ext_sar_height; int open_gop; int open_gop_size; int aso; int hier_qp_layer; int hier_qp_type; int* hier_qp_layer_qp; int sei_frame_packing; int sei_fp_curr_frame_0; int sei_fp_arrangement_type; int fmo_map_type; int fmo_slice_grp; int fmo_chg_dir; int fmo_chg_rate; int /*<<< orphan*/ * fmo_run_len; scalar_t__ fmo; scalar_t__ hier_qp; } ;
struct TYPE_2__ {struct s5p_mfc_h264_enc_params h264; } ;
struct s5p_mfc_enc_params {int num_b_frame; int rc_mb; int rc_framerate_num; int rc_framerate_denom; scalar_t__ frame_skip_mode; int vbv_delay; scalar_t__ rc_frame; TYPE_1__ codec; } ;
struct s5p_mfc_dev {struct s5p_mfc_regs* mfc_regs; } ;
struct s5p_mfc_ctx {int img_height; struct s5p_mfc_enc_params enc_params; struct s5p_mfc_dev* dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 scalar_t__ V4L2_MPEG_MFC51_VIDEO_FRAME_SKIP_MODE_BUF_LIMIT ; 
#define  V4L2_MPEG_VIDEO_H264_FMO_MAP_TYPE_INTERLEAVED_SLICES 131 
#define  V4L2_MPEG_VIDEO_H264_FMO_MAP_TYPE_RASTER_SCAN 130 
#define  V4L2_MPEG_VIDEO_H264_FMO_MAP_TYPE_SCATTERED_SLICES 129 
#define  V4L2_MPEG_VIDEO_H264_FMO_MAP_TYPE_WIPE_SCAN 128 
 int /*<<< orphan*/  mfc_debug_enter () ; 
 int /*<<< orphan*/  mfc_debug_leave () ; 
 int /*<<< orphan*/  mfc_err (char*,int) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  s5p_mfc_set_enc_params (struct s5p_mfc_ctx*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int s5p_mfc_set_enc_params_h264(struct s5p_mfc_ctx *ctx)
{
	struct s5p_mfc_dev *dev = ctx->dev;
	const struct s5p_mfc_regs *mfc_regs = dev->mfc_regs;
	struct s5p_mfc_enc_params *p = &ctx->enc_params;
	struct s5p_mfc_h264_enc_params *p_h264 = &p->codec.h264;
	unsigned int reg = 0;
	int i;

	mfc_debug_enter();

	s5p_mfc_set_enc_params(ctx);

	/* pictype : number of B */
	reg = readl(mfc_regs->e_gop_config);
	reg &= ~(0x3 << 16);
	reg |= ((p->num_b_frame & 0x3) << 16);
	writel(reg, mfc_regs->e_gop_config);

	/* profile & level */
	reg = 0;
	/** level */
	reg |= ((p_h264->level & 0xFF) << 8);
	/** profile - 0 ~ 3 */
	reg |= p_h264->profile & 0x3F;
	writel(reg, mfc_regs->e_picture_profile);

	/* rate control config. */
	reg = readl(mfc_regs->e_rc_config);
	/** macroblock level rate control */
	reg &= ~(0x1 << 8);
	reg |= ((p->rc_mb & 0x1) << 8);
	writel(reg, mfc_regs->e_rc_config);

	/** frame QP */
	reg &= ~(0x3F);
	reg |= p_h264->rc_frame_qp & 0x3F;
	writel(reg, mfc_regs->e_rc_config);

	/* max & min value of QP */
	reg = 0;
	/** max QP */
	reg |= ((p_h264->rc_max_qp & 0x3F) << 8);
	/** min QP */
	reg |= p_h264->rc_min_qp & 0x3F;
	writel(reg, mfc_regs->e_rc_qp_bound);

	/* other QPs */
	writel(0x0, mfc_regs->e_fixed_picture_qp);
	if (!p->rc_frame && !p->rc_mb) {
		reg = 0;
		reg |= ((p_h264->rc_b_frame_qp & 0x3F) << 16);
		reg |= ((p_h264->rc_p_frame_qp & 0x3F) << 8);
		reg |= p_h264->rc_frame_qp & 0x3F;
		writel(reg, mfc_regs->e_fixed_picture_qp);
	}

	/* frame rate */
	if (p->rc_frame && p->rc_framerate_num && p->rc_framerate_denom) {
		reg = 0;
		reg |= ((p->rc_framerate_num & 0xFFFF) << 16);
		reg |= p->rc_framerate_denom & 0xFFFF;
		writel(reg, mfc_regs->e_rc_frame_rate);
	}

	/* vbv buffer size */
	if (p->frame_skip_mode ==
			V4L2_MPEG_MFC51_VIDEO_FRAME_SKIP_MODE_BUF_LIMIT) {
		writel(p_h264->cpb_size & 0xFFFF,
				mfc_regs->e_vbv_buffer_size);

		if (p->rc_frame)
			writel(p->vbv_delay, mfc_regs->e_vbv_init_delay);
	}

	/* interlace */
	reg = 0;
	reg |= ((p_h264->interlace & 0x1) << 3);
	writel(reg, mfc_regs->e_h264_options);

	/* height */
	if (p_h264->interlace) {
		writel(ctx->img_height >> 1,
				mfc_regs->e_frame_height); /* 32 align */
		/* cropped height */
		writel(ctx->img_height >> 1,
				mfc_regs->e_cropped_frame_height);
	}

	/* loop filter ctrl */
	reg = readl(mfc_regs->e_h264_options);
	reg &= ~(0x3 << 1);
	reg |= ((p_h264->loop_filter_mode & 0x3) << 1);
	writel(reg, mfc_regs->e_h264_options);

	/* loopfilter alpha offset */
	if (p_h264->loop_filter_alpha < 0) {
		reg = 0x10;
		reg |= (0xFF - p_h264->loop_filter_alpha) + 1;
	} else {
		reg = 0x00;
		reg |= (p_h264->loop_filter_alpha & 0xF);
	}
	writel(reg, mfc_regs->e_h264_lf_alpha_offset);

	/* loopfilter beta offset */
	if (p_h264->loop_filter_beta < 0) {
		reg = 0x10;
		reg |= (0xFF - p_h264->loop_filter_beta) + 1;
	} else {
		reg = 0x00;
		reg |= (p_h264->loop_filter_beta & 0xF);
	}
	writel(reg, mfc_regs->e_h264_lf_beta_offset);

	/* entropy coding mode */
	reg = readl(mfc_regs->e_h264_options);
	reg &= ~(0x1);
	reg |= p_h264->entropy_mode & 0x1;
	writel(reg, mfc_regs->e_h264_options);

	/* number of ref. picture */
	reg = readl(mfc_regs->e_h264_options);
	reg &= ~(0x1 << 7);
	reg |= (((p_h264->num_ref_pic_4p - 1) & 0x1) << 7);
	writel(reg, mfc_regs->e_h264_options);

	/* 8x8 transform enable */
	reg = readl(mfc_regs->e_h264_options);
	reg &= ~(0x3 << 12);
	reg |= ((p_h264->_8x8_transform & 0x3) << 12);
	writel(reg, mfc_regs->e_h264_options);

	/* macroblock adaptive scaling features */
	writel(0x0, mfc_regs->e_mb_rc_config);
	if (p->rc_mb) {
		reg = 0;
		/** dark region */
		reg |= ((p_h264->rc_mb_dark & 0x1) << 3);
		/** smooth region */
		reg |= ((p_h264->rc_mb_smooth & 0x1) << 2);
		/** static region */
		reg |= ((p_h264->rc_mb_static & 0x1) << 1);
		/** high activity region */
		reg |= p_h264->rc_mb_activity & 0x1;
		writel(reg, mfc_regs->e_mb_rc_config);
	}

	/* aspect ratio VUI */
	readl(mfc_regs->e_h264_options);
	reg &= ~(0x1 << 5);
	reg |= ((p_h264->vui_sar & 0x1) << 5);
	writel(reg, mfc_regs->e_h264_options);

	writel(0x0, mfc_regs->e_aspect_ratio);
	writel(0x0, mfc_regs->e_extended_sar);
	if (p_h264->vui_sar) {
		/* aspect ration IDC */
		reg = 0;
		reg |= p_h264->vui_sar_idc & 0xFF;
		writel(reg, mfc_regs->e_aspect_ratio);
		if (p_h264->vui_sar_idc == 0xFF) {
			/* extended SAR */
			reg = 0;
			reg |= (p_h264->vui_ext_sar_width & 0xFFFF) << 16;
			reg |= p_h264->vui_ext_sar_height & 0xFFFF;
			writel(reg, mfc_regs->e_extended_sar);
		}
	}

	/* intra picture period for H.264 open GOP */
	/* control */
	readl(mfc_regs->e_h264_options);
	reg &= ~(0x1 << 4);
	reg |= ((p_h264->open_gop & 0x1) << 4);
	writel(reg, mfc_regs->e_h264_options);

	/* value */
	writel(0x0, mfc_regs->e_h264_i_period);
	if (p_h264->open_gop) {
		reg = 0;
		reg |= p_h264->open_gop_size & 0xFFFF;
		writel(reg, mfc_regs->e_h264_i_period);
	}

	/* 'WEIGHTED_BI_PREDICTION' for B is disable */
	readl(mfc_regs->e_h264_options);
	reg &= ~(0x3 << 9);
	writel(reg, mfc_regs->e_h264_options);

	/* 'CONSTRAINED_INTRA_PRED_ENABLE' is disable */
	readl(mfc_regs->e_h264_options);
	reg &= ~(0x1 << 14);
	writel(reg, mfc_regs->e_h264_options);

	/* ASO */
	readl(mfc_regs->e_h264_options);
	reg &= ~(0x1 << 6);
	reg |= ((p_h264->aso & 0x1) << 6);
	writel(reg, mfc_regs->e_h264_options);

	/* hier qp enable */
	readl(mfc_regs->e_h264_options);
	reg &= ~(0x1 << 8);
	reg |= ((p_h264->open_gop & 0x1) << 8);
	writel(reg, mfc_regs->e_h264_options);
	reg = 0;
	if (p_h264->hier_qp && p_h264->hier_qp_layer) {
		reg |= (p_h264->hier_qp_type & 0x1) << 0x3;
		reg |= p_h264->hier_qp_layer & 0x7;
		writel(reg, mfc_regs->e_h264_num_t_layer);
		/* QP value for each layer */
		for (i = 0; i < p_h264->hier_qp_layer &&
				i < ARRAY_SIZE(p_h264->hier_qp_layer_qp); i++) {
			writel(p_h264->hier_qp_layer_qp[i],
				mfc_regs->e_h264_hierarchical_qp_layer0
				+ i * 4);
		}
	}
	/* number of coding layer should be zero when hierarchical is disable */
	writel(reg, mfc_regs->e_h264_num_t_layer);

	/* frame packing SEI generation */
	readl(mfc_regs->e_h264_options);
	reg &= ~(0x1 << 25);
	reg |= ((p_h264->sei_frame_packing & 0x1) << 25);
	writel(reg, mfc_regs->e_h264_options);
	if (p_h264->sei_frame_packing) {
		reg = 0;
		/** current frame0 flag */
		reg |= ((p_h264->sei_fp_curr_frame_0 & 0x1) << 2);
		/** arrangement type */
		reg |= p_h264->sei_fp_arrangement_type & 0x3;
		writel(reg, mfc_regs->e_h264_frame_packing_sei_info);
	}

	if (p_h264->fmo) {
		switch (p_h264->fmo_map_type) {
		case V4L2_MPEG_VIDEO_H264_FMO_MAP_TYPE_INTERLEAVED_SLICES:
			if (p_h264->fmo_slice_grp > 4)
				p_h264->fmo_slice_grp = 4;
			for (i = 0; i < (p_h264->fmo_slice_grp & 0xF); i++)
				writel(p_h264->fmo_run_len[i] - 1,
					mfc_regs->e_h264_fmo_run_length_minus1_0
					+ i * 4);
			break;
		case V4L2_MPEG_VIDEO_H264_FMO_MAP_TYPE_SCATTERED_SLICES:
			if (p_h264->fmo_slice_grp > 4)
				p_h264->fmo_slice_grp = 4;
			break;
		case V4L2_MPEG_VIDEO_H264_FMO_MAP_TYPE_RASTER_SCAN:
		case V4L2_MPEG_VIDEO_H264_FMO_MAP_TYPE_WIPE_SCAN:
			if (p_h264->fmo_slice_grp > 2)
				p_h264->fmo_slice_grp = 2;
			writel(p_h264->fmo_chg_dir & 0x1,
				mfc_regs->e_h264_fmo_slice_grp_change_dir);
			/* the valid range is 0 ~ number of macroblocks -1 */
			writel(p_h264->fmo_chg_rate,
			mfc_regs->e_h264_fmo_slice_grp_change_rate_minus1);
			break;
		default:
			mfc_err("Unsupported map type for FMO: %d\n",
					p_h264->fmo_map_type);
			p_h264->fmo_map_type = 0;
			p_h264->fmo_slice_grp = 1;
			break;
		}

		writel(p_h264->fmo_map_type,
				mfc_regs->e_h264_fmo_slice_grp_map_type);
		writel(p_h264->fmo_slice_grp - 1,
				mfc_regs->e_h264_fmo_num_slice_grp_minus1);
	} else {
		writel(0, mfc_regs->e_h264_fmo_num_slice_grp_minus1);
	}

	mfc_debug_leave();

	return 0;
}