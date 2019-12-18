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
struct s5p_mfc_regs {int /*<<< orphan*/  instance_id; } ;
struct s5p_mfc_dev {int /*<<< orphan*/  mfc_cmds; struct s5p_mfc_regs* mfc_regs; } ;
struct s5p_mfc_ctx {scalar_t__ codec_mode; scalar_t__ state; int /*<<< orphan*/  inst_no; struct s5p_mfc_dev* dev; } ;

/* Variables and functions */
 scalar_t__ MFCINST_FINISHING ; 
 int S5P_FIMV_CH_FRAME_START_V6 ; 
 int S5P_FIMV_CH_LAST_FRAME_V6 ; 
 scalar_t__ S5P_MFC_CODEC_H264_ENC ; 
 int /*<<< orphan*/  cmd_host2risc ; 
 int /*<<< orphan*/  mfc_debug (int,char*) ; 
 int /*<<< orphan*/  s5p_mfc_h264_set_aso_slice_order_v6 (struct s5p_mfc_ctx*) ; 
 int /*<<< orphan*/  s5p_mfc_hw_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct s5p_mfc_dev*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s5p_mfc_set_slice_mode (struct s5p_mfc_ctx*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5p_mfc_encode_one_frame_v6(struct s5p_mfc_ctx *ctx)
{
	struct s5p_mfc_dev *dev = ctx->dev;
	const struct s5p_mfc_regs *mfc_regs = dev->mfc_regs;
	int cmd;

	mfc_debug(2, "++\n");

	/* memory structure cur. frame */

	if (ctx->codec_mode == S5P_MFC_CODEC_H264_ENC)
		s5p_mfc_h264_set_aso_slice_order_v6(ctx);

	s5p_mfc_set_slice_mode(ctx);

	if (ctx->state != MFCINST_FINISHING)
		cmd = S5P_FIMV_CH_FRAME_START_V6;
	else
		cmd = S5P_FIMV_CH_LAST_FRAME_V6;

	writel(ctx->inst_no, mfc_regs->instance_id);
	s5p_mfc_hw_call(dev->mfc_cmds, cmd_host2risc, dev, cmd, NULL);

	mfc_debug(2, "--\n");

	return 0;
}