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
struct s5p_mfc_h264_enc_params {int level; unsigned int profile; unsigned int interlace; unsigned int loop_filter_mode; int loop_filter_alpha; int loop_filter_beta; scalar_t__ entropy_mode; int num_ref_pic_4p; unsigned int max_ref_pic; unsigned int _8x8_transform; unsigned int rc_frame_qp; int rc_max_qp; unsigned int rc_min_qp; int rc_mb_dark; int rc_mb_smooth; int rc_mb_static; unsigned int rc_mb_activity; int rc_b_frame_qp; int rc_p_frame_qp; int vui_sar; unsigned int vui_sar_idc; int vui_ext_sar_width; unsigned int vui_ext_sar_height; int open_gop; unsigned int open_gop_size; int cpb_size; } ;
struct TYPE_2__ {struct s5p_mfc_h264_enc_params h264; } ;
struct s5p_mfc_enc_params {int num_b_frame; int rc_mb; int rc_framerate_denom; int rc_framerate_num; scalar_t__ frame_skip_mode; scalar_t__ rc_frame; TYPE_1__ codec; } ;
struct s5p_mfc_dev {int dummy; } ;
struct s5p_mfc_ctx {int img_height; struct s5p_mfc_enc_params enc_params; struct s5p_mfc_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXTENDED_SAR ; 
 int /*<<< orphan*/  EXT_ENC_CONTROL ; 
 int /*<<< orphan*/  H264_I_PERIOD ; 
 int /*<<< orphan*/  P_B_FRAME_QP ; 
 int /*<<< orphan*/  S5P_FIMV_ENC_ALPHA_OFF ; 
 int /*<<< orphan*/  S5P_FIMV_ENC_BETA_OFF ; 
 int /*<<< orphan*/  S5P_FIMV_ENC_H264_ENTROPY_MODE ; 
 int /*<<< orphan*/  S5P_FIMV_ENC_H264_NUM_OF_REF ; 
 int /*<<< orphan*/  S5P_FIMV_ENC_H264_TRANS_FLAG ; 
 int /*<<< orphan*/  S5P_FIMV_ENC_LF_CTRL ; 
 int /*<<< orphan*/  S5P_FIMV_ENC_PIC_STRUCT ; 
 int /*<<< orphan*/  S5P_FIMV_ENC_PIC_TYPE_CTRL ; 
 int /*<<< orphan*/  S5P_FIMV_ENC_PROFILE ; 
 int /*<<< orphan*/  S5P_FIMV_ENC_RC_CONFIG ; 
 int /*<<< orphan*/  S5P_FIMV_ENC_RC_FRAME_RATE ; 
 int /*<<< orphan*/  S5P_FIMV_ENC_RC_MB_CTRL ; 
 int /*<<< orphan*/  S5P_FIMV_ENC_RC_QBOUND ; 
 int /*<<< orphan*/  S5P_FIMV_ENC_VSIZE_PX ; 
 int /*<<< orphan*/  SAMPLE_ASPECT_RATIO_IDC ; 
 scalar_t__ V4L2_MPEG_MFC51_VIDEO_FRAME_SKIP_MODE_BUF_LIMIT ; 
 scalar_t__ V4L2_MPEG_VIDEO_H264_ENTROPY_MODE_CABAC ; 
 unsigned int mfc_read (struct s5p_mfc_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfc_write (struct s5p_mfc_dev*,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int s5p_mfc_read_info_v5 (struct s5p_mfc_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5p_mfc_set_enc_params (struct s5p_mfc_ctx*) ; 
 int /*<<< orphan*/  s5p_mfc_write_info_v5 (struct s5p_mfc_ctx*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5p_mfc_set_enc_params_h264(struct s5p_mfc_ctx *ctx)
{
	struct s5p_mfc_dev *dev = ctx->dev;
	struct s5p_mfc_enc_params *p = &ctx->enc_params;
	struct s5p_mfc_h264_enc_params *p_264 = &p->codec.h264;
	unsigned int reg;
	unsigned int shm;

	s5p_mfc_set_enc_params(ctx);
	/* pictype : number of B */
	reg = mfc_read(dev, S5P_FIMV_ENC_PIC_TYPE_CTRL);
	/* num_b_frame - 0 ~ 2 */
	reg &= ~(0x3 << 16);
	reg |= (p->num_b_frame << 16);
	mfc_write(dev, reg, S5P_FIMV_ENC_PIC_TYPE_CTRL);
	/* profile & level */
	reg = mfc_read(dev, S5P_FIMV_ENC_PROFILE);
	/* level */
	reg &= ~(0xFF << 8);
	reg |= (p_264->level << 8);
	/* profile - 0 ~ 2 */
	reg &= ~(0x3F);
	reg |= p_264->profile;
	mfc_write(dev, reg, S5P_FIMV_ENC_PROFILE);
	/* interlace  */
	mfc_write(dev, p_264->interlace, S5P_FIMV_ENC_PIC_STRUCT);
	/* height */
	if (p_264->interlace)
		mfc_write(dev, ctx->img_height >> 1, S5P_FIMV_ENC_VSIZE_PX);
	/* loopfilter ctrl */
	mfc_write(dev, p_264->loop_filter_mode, S5P_FIMV_ENC_LF_CTRL);
	/* loopfilter alpha offset */
	if (p_264->loop_filter_alpha < 0) {
		reg = 0x10;
		reg |= (0xFF - p_264->loop_filter_alpha) + 1;
	} else {
		reg = 0x00;
		reg |= (p_264->loop_filter_alpha & 0xF);
	}
	mfc_write(dev, reg, S5P_FIMV_ENC_ALPHA_OFF);
	/* loopfilter beta offset */
	if (p_264->loop_filter_beta < 0) {
		reg = 0x10;
		reg |= (0xFF - p_264->loop_filter_beta) + 1;
	} else {
		reg = 0x00;
		reg |= (p_264->loop_filter_beta & 0xF);
	}
	mfc_write(dev, reg, S5P_FIMV_ENC_BETA_OFF);
	/* entropy coding mode */
	if (p_264->entropy_mode == V4L2_MPEG_VIDEO_H264_ENTROPY_MODE_CABAC)
		mfc_write(dev, 1, S5P_FIMV_ENC_H264_ENTROPY_MODE);
	else
		mfc_write(dev, 0, S5P_FIMV_ENC_H264_ENTROPY_MODE);
	/* number of ref. picture */
	reg = mfc_read(dev, S5P_FIMV_ENC_H264_NUM_OF_REF);
	/* num of ref. pictures of P */
	reg &= ~(0x3 << 5);
	reg |= (p_264->num_ref_pic_4p << 5);
	/* max number of ref. pictures */
	reg &= ~(0x1F);
	reg |= p_264->max_ref_pic;
	mfc_write(dev, reg, S5P_FIMV_ENC_H264_NUM_OF_REF);
	/* 8x8 transform enable */
	mfc_write(dev, p_264->_8x8_transform, S5P_FIMV_ENC_H264_TRANS_FLAG);
	/* rate control config. */
	reg = mfc_read(dev, S5P_FIMV_ENC_RC_CONFIG);
	/* macroblock level rate control */
	reg &= ~(0x1 << 8);
	reg |= (p->rc_mb << 8);
	/* frame QP */
	reg &= ~(0x3F);
	reg |= p_264->rc_frame_qp;
	mfc_write(dev, reg, S5P_FIMV_ENC_RC_CONFIG);
	/* frame rate */
	if (p->rc_frame && p->rc_framerate_denom)
		mfc_write(dev, p->rc_framerate_num * 1000
			/ p->rc_framerate_denom, S5P_FIMV_ENC_RC_FRAME_RATE);
	else
		mfc_write(dev, 0, S5P_FIMV_ENC_RC_FRAME_RATE);
	/* max & min value of QP */
	reg = mfc_read(dev, S5P_FIMV_ENC_RC_QBOUND);
	/* max QP */
	reg &= ~(0x3F << 8);
	reg |= (p_264->rc_max_qp << 8);
	/* min QP */
	reg &= ~(0x3F);
	reg |= p_264->rc_min_qp;
	mfc_write(dev, reg, S5P_FIMV_ENC_RC_QBOUND);
	/* macroblock adaptive scaling features */
	if (p->rc_mb) {
		reg = mfc_read(dev, S5P_FIMV_ENC_RC_MB_CTRL);
		/* dark region */
		reg &= ~(0x1 << 3);
		reg |= (p_264->rc_mb_dark << 3);
		/* smooth region */
		reg &= ~(0x1 << 2);
		reg |= (p_264->rc_mb_smooth << 2);
		/* static region */
		reg &= ~(0x1 << 1);
		reg |= (p_264->rc_mb_static << 1);
		/* high activity region */
		reg &= ~(0x1);
		reg |= p_264->rc_mb_activity;
		mfc_write(dev, reg, S5P_FIMV_ENC_RC_MB_CTRL);
	}
	if (!p->rc_frame && !p->rc_mb) {
		shm = s5p_mfc_read_info_v5(ctx, P_B_FRAME_QP);
		shm &= ~(0xFFF);
		shm |= ((p_264->rc_b_frame_qp & 0x3F) << 6);
		shm |= (p_264->rc_p_frame_qp & 0x3F);
		s5p_mfc_write_info_v5(ctx, shm, P_B_FRAME_QP);
	}
	/* extended encoder ctrl */
	shm = s5p_mfc_read_info_v5(ctx, EXT_ENC_CONTROL);
	/* AR VUI control */
	shm &= ~(0x1 << 15);
	shm |= (p_264->vui_sar << 1);
	s5p_mfc_write_info_v5(ctx, shm, EXT_ENC_CONTROL);
	if (p_264->vui_sar) {
		/* aspect ration IDC */
		shm = s5p_mfc_read_info_v5(ctx, SAMPLE_ASPECT_RATIO_IDC);
		shm &= ~(0xFF);
		shm |= p_264->vui_sar_idc;
		s5p_mfc_write_info_v5(ctx, shm, SAMPLE_ASPECT_RATIO_IDC);
		if (p_264->vui_sar_idc == 0xFF) {
			/* sample  AR info */
			shm = s5p_mfc_read_info_v5(ctx, EXTENDED_SAR);
			shm &= ~(0xFFFFFFFF);
			shm |= p_264->vui_ext_sar_width << 16;
			shm |= p_264->vui_ext_sar_height;
			s5p_mfc_write_info_v5(ctx, shm, EXTENDED_SAR);
		}
	}
	/* intra picture period for H.264 */
	shm = s5p_mfc_read_info_v5(ctx, H264_I_PERIOD);
	/* control */
	shm &= ~(0x1 << 16);
	shm |= (p_264->open_gop << 16);
	/* value */
	if (p_264->open_gop) {
		shm &= ~(0xFFFF);
		shm |= p_264->open_gop_size;
	}
	s5p_mfc_write_info_v5(ctx, shm, H264_I_PERIOD);
	/* extended encoder ctrl */
	shm = s5p_mfc_read_info_v5(ctx, EXT_ENC_CONTROL);
	/* vbv buffer size */
	if (p->frame_skip_mode ==
			V4L2_MPEG_MFC51_VIDEO_FRAME_SKIP_MODE_BUF_LIMIT) {
		shm &= ~(0xFFFF << 16);
		shm |= (p_264->cpb_size << 16);
	}
	s5p_mfc_write_info_v5(ctx, shm, EXT_ENC_CONTROL);
	return 0;
}