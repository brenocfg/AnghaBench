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
typedef  int u32 ;
struct decon_context {int out_type; scalar_t__ addr; int /*<<< orphan*/  vblank_lock; scalar_t__ frame_id; } ;

/* Variables and functions */
 int CMU_CLKGAGE_MODE_MEM_F ; 
 int CMU_CLKGAGE_MODE_SFR_F ; 
 int CRCCTRL_CRCCLKEN ; 
 int CRCCTRL_CRCEN ; 
 int CRCCTRL_CRCSTART_F ; 
 int /*<<< orphan*/  DECON_CMU ; 
 scalar_t__ DECON_CRCCTRL ; 
 scalar_t__ DECON_VIDCON0 ; 
 scalar_t__ DECON_VIDCON1 ; 
 int IFTYPE_HDMI ; 
 int VIDCON0_CLKVALUP ; 
 int VIDCON0_STOP_STATUS ; 
 int VIDCON0_SWRESET ; 
 int VIDCON0_VLCKFREE ; 
 int VIDCON1_VCLK_RUN_VDEN_DISABLE ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  decon_set_bits (struct decon_context*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int readl_poll_timeout (scalar_t__,int,int,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void decon_swreset(struct decon_context *ctx)
{
	unsigned long flags;
	u32 val;
	int ret;

	writel(0, ctx->addr + DECON_VIDCON0);
	readl_poll_timeout(ctx->addr + DECON_VIDCON0, val,
			   ~val & VIDCON0_STOP_STATUS, 12, 20000);

	writel(VIDCON0_SWRESET, ctx->addr + DECON_VIDCON0);
	ret = readl_poll_timeout(ctx->addr + DECON_VIDCON0, val,
				 ~val & VIDCON0_SWRESET, 12, 20000);

	WARN(ret < 0, "failed to software reset DECON\n");

	spin_lock_irqsave(&ctx->vblank_lock, flags);
	ctx->frame_id = 0;
	spin_unlock_irqrestore(&ctx->vblank_lock, flags);

	if (!(ctx->out_type & IFTYPE_HDMI))
		return;

	writel(VIDCON0_CLKVALUP | VIDCON0_VLCKFREE, ctx->addr + DECON_VIDCON0);
	decon_set_bits(ctx, DECON_CMU,
		       CMU_CLKGAGE_MODE_SFR_F | CMU_CLKGAGE_MODE_MEM_F, ~0);
	writel(VIDCON1_VCLK_RUN_VDEN_DISABLE, ctx->addr + DECON_VIDCON1);
	writel(CRCCTRL_CRCEN | CRCCTRL_CRCSTART_F | CRCCTRL_CRCCLKEN,
	       ctx->addr + DECON_CRCCTRL);
}