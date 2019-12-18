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
struct mixer_context {int /*<<< orphan*/  reg_slock; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MXR_BG_COLOR0 ; 
 int /*<<< orphan*/  MXR_BG_COLOR1 ; 
 int /*<<< orphan*/  MXR_BG_COLOR2 ; 
 int /*<<< orphan*/  MXR_BIT_VP_ENABLED ; 
 int /*<<< orphan*/  MXR_CFG ; 
 int /*<<< orphan*/  MXR_CFG_DST_HDMI ; 
 int /*<<< orphan*/  MXR_CFG_DST_MASK ; 
 int /*<<< orphan*/  MXR_CFG_GRP0_ENABLE ; 
 int /*<<< orphan*/  MXR_CFG_GRP1_ENABLE ; 
 int /*<<< orphan*/  MXR_CFG_OUT_MASK ; 
 int /*<<< orphan*/  MXR_CFG_OUT_RGB888 ; 
 int /*<<< orphan*/  MXR_CFG_VP_ENABLE ; 
 int /*<<< orphan*/  MXR_GRAPHIC_SXY (int) ; 
 int /*<<< orphan*/  MXR_LAYER_CFG ; 
 int /*<<< orphan*/  MXR_STATUS ; 
 int /*<<< orphan*/  MXR_STATUS_16_BURST ; 
 int /*<<< orphan*/  MXR_STATUS_BURST_MASK ; 
 int /*<<< orphan*/  MXR_YCBCR_VAL (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mixer_reg_write (struct mixer_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mixer_reg_writemask (struct mixer_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vp_default_filter (struct mixer_context*) ; 
 int /*<<< orphan*/  vp_win_reset (struct mixer_context*) ; 

__attribute__((used)) static void mixer_win_reset(struct mixer_context *ctx)
{
	unsigned long flags;

	spin_lock_irqsave(&ctx->reg_slock, flags);

	mixer_reg_writemask(ctx, MXR_CFG, MXR_CFG_DST_HDMI, MXR_CFG_DST_MASK);

	/* set output in RGB888 mode */
	mixer_reg_writemask(ctx, MXR_CFG, MXR_CFG_OUT_RGB888, MXR_CFG_OUT_MASK);

	/* 16 beat burst in DMA */
	mixer_reg_writemask(ctx, MXR_STATUS, MXR_STATUS_16_BURST,
		MXR_STATUS_BURST_MASK);

	/* reset default layer priority */
	mixer_reg_write(ctx, MXR_LAYER_CFG, 0);

	/* set all background colors to RGB (0,0,0) */
	mixer_reg_write(ctx, MXR_BG_COLOR0, MXR_YCBCR_VAL(0, 128, 128));
	mixer_reg_write(ctx, MXR_BG_COLOR1, MXR_YCBCR_VAL(0, 128, 128));
	mixer_reg_write(ctx, MXR_BG_COLOR2, MXR_YCBCR_VAL(0, 128, 128));

	if (test_bit(MXR_BIT_VP_ENABLED, &ctx->flags)) {
		/* configuration of Video Processor Registers */
		vp_win_reset(ctx);
		vp_default_filter(ctx);
	}

	/* disable all layers */
	mixer_reg_writemask(ctx, MXR_CFG, 0, MXR_CFG_GRP0_ENABLE);
	mixer_reg_writemask(ctx, MXR_CFG, 0, MXR_CFG_GRP1_ENABLE);
	if (test_bit(MXR_BIT_VP_ENABLED, &ctx->flags))
		mixer_reg_writemask(ctx, MXR_CFG, 0, MXR_CFG_VP_ENABLE);

	/* set all source image offsets to zero */
	mixer_reg_write(ctx, MXR_GRAPHIC_SXY(0), 0);
	mixer_reg_write(ctx, MXR_GRAPHIC_SXY(1), 0);

	spin_unlock_irqrestore(&ctx->reg_slock, flags);
}