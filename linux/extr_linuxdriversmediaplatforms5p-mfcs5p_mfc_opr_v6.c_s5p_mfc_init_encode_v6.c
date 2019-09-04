#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct s5p_mfc_regs {int /*<<< orphan*/  instance_id; int /*<<< orphan*/  e_source_second_plane_stride; int /*<<< orphan*/  e_source_first_plane_stride; } ;
struct s5p_mfc_dev {int /*<<< orphan*/  mfc_cmds; struct s5p_mfc_regs* mfc_regs; } ;
struct s5p_mfc_ctx {scalar_t__ codec_mode; int /*<<< orphan*/  inst_no; int /*<<< orphan*/  img_width; struct s5p_mfc_dev* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_MFCV7_PLUS (struct s5p_mfc_dev*) ; 
 int /*<<< orphan*/  S5P_FIMV_CH_SEQ_HEADER_V6 ; 
 scalar_t__ S5P_FIMV_CODEC_HEVC_ENC ; 
 scalar_t__ S5P_MFC_CODEC_H263_ENC ; 
 scalar_t__ S5P_MFC_CODEC_H264_ENC ; 
 scalar_t__ S5P_MFC_CODEC_MPEG4_ENC ; 
 scalar_t__ S5P_MFC_CODEC_VP8_ENC ; 
 int /*<<< orphan*/  cmd_host2risc ; 
 int /*<<< orphan*/  mfc_err (char*,scalar_t__) ; 
 int /*<<< orphan*/  s5p_mfc_hw_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct s5p_mfc_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s5p_mfc_set_enc_params_h263 (struct s5p_mfc_ctx*) ; 
 int /*<<< orphan*/  s5p_mfc_set_enc_params_h264 (struct s5p_mfc_ctx*) ; 
 int /*<<< orphan*/  s5p_mfc_set_enc_params_hevc (struct s5p_mfc_ctx*) ; 
 int /*<<< orphan*/  s5p_mfc_set_enc_params_mpeg4 (struct s5p_mfc_ctx*) ; 
 int /*<<< orphan*/  s5p_mfc_set_enc_params_vp8 (struct s5p_mfc_ctx*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5p_mfc_init_encode_v6(struct s5p_mfc_ctx *ctx)
{
	struct s5p_mfc_dev *dev = ctx->dev;
	const struct s5p_mfc_regs *mfc_regs = dev->mfc_regs;

	if (ctx->codec_mode == S5P_MFC_CODEC_H264_ENC)
		s5p_mfc_set_enc_params_h264(ctx);
	else if (ctx->codec_mode == S5P_MFC_CODEC_MPEG4_ENC)
		s5p_mfc_set_enc_params_mpeg4(ctx);
	else if (ctx->codec_mode == S5P_MFC_CODEC_H263_ENC)
		s5p_mfc_set_enc_params_h263(ctx);
	else if (ctx->codec_mode == S5P_MFC_CODEC_VP8_ENC)
		s5p_mfc_set_enc_params_vp8(ctx);
	else if (ctx->codec_mode == S5P_FIMV_CODEC_HEVC_ENC)
		s5p_mfc_set_enc_params_hevc(ctx);
	else {
		mfc_err("Unknown codec for encoding (%x).\n",
			ctx->codec_mode);
		return -EINVAL;
	}

	/* Set stride lengths for v7 & above */
	if (IS_MFCV7_PLUS(dev)) {
		writel(ctx->img_width, mfc_regs->e_source_first_plane_stride);
		writel(ctx->img_width, mfc_regs->e_source_second_plane_stride);
	}

	writel(ctx->inst_no, mfc_regs->instance_id);
	s5p_mfc_hw_call(dev->mfc_cmds, cmd_host2risc, dev,
			S5P_FIMV_CH_SEQ_HEADER_V6, NULL);

	return 0;
}