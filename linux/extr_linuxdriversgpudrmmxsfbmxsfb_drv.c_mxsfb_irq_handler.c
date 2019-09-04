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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  crtc; } ;
struct mxsfb_drm_private {scalar_t__ base; TYPE_1__ pipe; } ;
struct drm_device {struct mxsfb_drm_private* dev_private; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int CTRL1_CUR_FRAME_DONE_IRQ ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ LCDC_CTRL1 ; 
 scalar_t__ REG_CLR ; 
 int /*<<< orphan*/  drm_crtc_handle_vblank (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mxsfb_disable_axi_clk (struct mxsfb_drm_private*) ; 
 int /*<<< orphan*/  mxsfb_enable_axi_clk (struct mxsfb_drm_private*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t mxsfb_irq_handler(int irq, void *data)
{
	struct drm_device *drm = data;
	struct mxsfb_drm_private *mxsfb = drm->dev_private;
	u32 reg;

	mxsfb_enable_axi_clk(mxsfb);

	reg = readl(mxsfb->base + LCDC_CTRL1);

	if (reg & CTRL1_CUR_FRAME_DONE_IRQ)
		drm_crtc_handle_vblank(&mxsfb->pipe.crtc);

	writel(CTRL1_CUR_FRAME_DONE_IRQ, mxsfb->base + LCDC_CTRL1 + REG_CLR);

	mxsfb_disable_axi_clk(mxsfb);

	return IRQ_HANDLED;
}