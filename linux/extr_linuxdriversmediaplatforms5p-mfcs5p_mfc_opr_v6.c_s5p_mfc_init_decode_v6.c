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
struct s5p_mfc_regs {int /*<<< orphan*/  instance_id; int /*<<< orphan*/  d_sei_enable; int /*<<< orphan*/  pixel_format; int /*<<< orphan*/  d_dec_options; int /*<<< orphan*/  d_init_buffer_options; int /*<<< orphan*/  d_display_delay; int /*<<< orphan*/  d_cpb_buffer_addr; } ;
struct s5p_mfc_dev {int /*<<< orphan*/  mfc_cmds; struct s5p_mfc_regs* mfc_regs; } ;
struct s5p_mfc_ctx {int inst_no; int display_delay; scalar_t__ codec_mode; unsigned int loop_filter_mpeg4; int sei_fp_parse; TYPE_1__* dst_fmt; scalar_t__ display_delay_enable; struct s5p_mfc_dev* dev; } ;
struct TYPE_2__ {scalar_t__ fourcc; } ;

/* Variables and functions */
 scalar_t__ IS_MFCV6_V2 (struct s5p_mfc_dev*) ; 
 scalar_t__ IS_MFCV7_PLUS (struct s5p_mfc_dev*) ; 
 int /*<<< orphan*/  S5P_FIMV_CH_SEQ_HEADER_V6 ; 
 int S5P_FIMV_D_OPT_DDELAY_EN_SHIFT_V6 ; 
 int S5P_FIMV_D_OPT_FMO_ASO_CTRL_MASK_V6 ; 
 unsigned int S5P_FIMV_D_OPT_LF_CTRL_SHIFT_V6 ; 
 int S5P_FIMV_D_OPT_TILE_MODE_SHIFT_V6 ; 
 scalar_t__ S5P_MFC_CODEC_MPEG4_DEC ; 
 scalar_t__ V4L2_PIX_FMT_NV12MT_16X16 ; 
 scalar_t__ V4L2_PIX_FMT_NV21M ; 
 int /*<<< orphan*/  cmd_host2risc ; 
 int /*<<< orphan*/  mfc_debug (int,char*,unsigned int,...) ; 
 int /*<<< orphan*/  mfc_debug_enter () ; 
 int /*<<< orphan*/  mfc_debug_leave () ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5p_mfc_hw_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct s5p_mfc_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5p_mfc_init_decode_v6(struct s5p_mfc_ctx *ctx)
{
	struct s5p_mfc_dev *dev = ctx->dev;
	const struct s5p_mfc_regs *mfc_regs = dev->mfc_regs;
	unsigned int reg = 0;
	int fmo_aso_ctrl = 0;

	mfc_debug_enter();
	mfc_debug(2, "InstNo: %d/%d\n", ctx->inst_no,
			S5P_FIMV_CH_SEQ_HEADER_V6);
	mfc_debug(2, "BUFs: %08x %08x %08x\n",
		  readl(mfc_regs->d_cpb_buffer_addr),
		  readl(mfc_regs->d_cpb_buffer_addr),
		  readl(mfc_regs->d_cpb_buffer_addr));

	/* FMO_ASO_CTRL - 0: Enable, 1: Disable */
	reg |= (fmo_aso_ctrl << S5P_FIMV_D_OPT_FMO_ASO_CTRL_MASK_V6);

	if (ctx->display_delay_enable) {
		reg |= (0x1 << S5P_FIMV_D_OPT_DDELAY_EN_SHIFT_V6);
		writel(ctx->display_delay, mfc_regs->d_display_delay);
	}

	if (IS_MFCV7_PLUS(dev) || IS_MFCV6_V2(dev)) {
		writel(reg, mfc_regs->d_dec_options);
		reg = 0;
	}

	/* Setup loop filter, for decoding this is only valid for MPEG4 */
	if (ctx->codec_mode == S5P_MFC_CODEC_MPEG4_DEC) {
		mfc_debug(2, "Set loop filter to: %d\n",
				ctx->loop_filter_mpeg4);
		reg |= (ctx->loop_filter_mpeg4 <<
				S5P_FIMV_D_OPT_LF_CTRL_SHIFT_V6);
	}
	if (ctx->dst_fmt->fourcc == V4L2_PIX_FMT_NV12MT_16X16)
		reg |= (0x1 << S5P_FIMV_D_OPT_TILE_MODE_SHIFT_V6);

	if (IS_MFCV7_PLUS(dev) || IS_MFCV6_V2(dev))
		writel(reg, mfc_regs->d_init_buffer_options);
	else
		writel(reg, mfc_regs->d_dec_options);

	/* 0: NV12(CbCr), 1: NV21(CrCb) */
	if (ctx->dst_fmt->fourcc == V4L2_PIX_FMT_NV21M)
		writel(0x1, mfc_regs->pixel_format);
	else
		writel(0x0, mfc_regs->pixel_format);


	/* sei parse */
	writel(ctx->sei_fp_parse & 0x1, mfc_regs->d_sei_enable);

	writel(ctx->inst_no, mfc_regs->instance_id);
	s5p_mfc_hw_call(dev->mfc_cmds, cmd_host2risc, dev,
			S5P_FIMV_CH_SEQ_HEADER_V6, NULL);

	mfc_debug_leave();
	return 0;
}