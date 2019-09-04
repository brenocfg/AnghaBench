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
struct s5p_mfc_regs {int /*<<< orphan*/  instance_id; int /*<<< orphan*/  d_slice_if_enable; int /*<<< orphan*/  d_available_dpb_flag_lower; } ;
struct s5p_mfc_dev {int /*<<< orphan*/  mfc_cmds; struct s5p_mfc_regs* mfc_regs; } ;
struct s5p_mfc_ctx {int dec_dst_flag; int slice_interface; int inst_no; struct s5p_mfc_dev* dev; } ;
typedef  enum s5p_mfc_decode_arg { ____Placeholder_s5p_mfc_decode_arg } s5p_mfc_decode_arg ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  S5P_FIMV_CH_FRAME_START_V6 ; 
 int /*<<< orphan*/  S5P_FIMV_CH_LAST_FRAME_V6 ; 
 int /*<<< orphan*/  cmd_host2risc ; 
 int /*<<< orphan*/  mfc_debug (int,char*) ; 
 int /*<<< orphan*/  mfc_err (char*) ; 
 int /*<<< orphan*/  s5p_mfc_hw_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct s5p_mfc_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5p_mfc_decode_one_frame_v6(struct s5p_mfc_ctx *ctx,
			enum s5p_mfc_decode_arg last_frame)
{
	struct s5p_mfc_dev *dev = ctx->dev;
	const struct s5p_mfc_regs *mfc_regs = dev->mfc_regs;

	writel(ctx->dec_dst_flag, mfc_regs->d_available_dpb_flag_lower);
	writel(ctx->slice_interface & 0x1, mfc_regs->d_slice_if_enable);

	writel(ctx->inst_no, mfc_regs->instance_id);
	/* Issue different commands to instance basing on whether it
	 * is the last frame or not. */
	switch (last_frame) {
	case 0:
		s5p_mfc_hw_call(dev->mfc_cmds, cmd_host2risc, dev,
				S5P_FIMV_CH_FRAME_START_V6, NULL);
		break;
	case 1:
		s5p_mfc_hw_call(dev->mfc_cmds, cmd_host2risc, dev,
				S5P_FIMV_CH_LAST_FRAME_V6, NULL);
		break;
	default:
		mfc_err("Unsupported last frame arg.\n");
		return -EINVAL;
	}

	mfc_debug(2, "Decoding a usual frame.\n");
	return 0;
}