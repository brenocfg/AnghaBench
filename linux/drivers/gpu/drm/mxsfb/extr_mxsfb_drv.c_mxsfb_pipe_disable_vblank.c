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
struct mxsfb_drm_private {scalar_t__ base; } ;
struct drm_simple_display_pipe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL1_CUR_FRAME_DONE_IRQ ; 
 int /*<<< orphan*/  CTRL1_CUR_FRAME_DONE_IRQ_EN ; 
 scalar_t__ LCDC_CTRL1 ; 
 scalar_t__ REG_CLR ; 
 struct mxsfb_drm_private* drm_pipe_to_mxsfb_drm_private (struct drm_simple_display_pipe*) ; 
 int /*<<< orphan*/  mxsfb_disable_axi_clk (struct mxsfb_drm_private*) ; 
 int /*<<< orphan*/  mxsfb_enable_axi_clk (struct mxsfb_drm_private*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mxsfb_pipe_disable_vblank(struct drm_simple_display_pipe *pipe)
{
	struct mxsfb_drm_private *mxsfb = drm_pipe_to_mxsfb_drm_private(pipe);

	/* Disable and clear VBLANK IRQ */
	mxsfb_enable_axi_clk(mxsfb);
	writel(CTRL1_CUR_FRAME_DONE_IRQ_EN, mxsfb->base + LCDC_CTRL1 + REG_CLR);
	writel(CTRL1_CUR_FRAME_DONE_IRQ, mxsfb->base + LCDC_CTRL1 + REG_CLR);
	mxsfb_disable_axi_clk(mxsfb);
}