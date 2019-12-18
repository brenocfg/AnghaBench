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
struct pl111_drm_dev_private {int /*<<< orphan*/  clk; scalar_t__ ctrl; scalar_t__ regs; int /*<<< orphan*/  (* variant_display_disable ) (struct drm_device*) ;TYPE_1__* variant; } ;
struct drm_crtc {struct drm_device* dev; } ;
struct drm_simple_display_pipe {struct drm_crtc crtc; } ;
struct drm_device {struct pl111_drm_dev_private* dev_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  broken_vblank; } ;

/* Variables and functions */
 int CNTL_LCDPWR ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_crtc_vblank_off (struct drm_crtc*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct drm_device*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void pl111_display_disable(struct drm_simple_display_pipe *pipe)
{
	struct drm_crtc *crtc = &pipe->crtc;
	struct drm_device *drm = crtc->dev;
	struct pl111_drm_dev_private *priv = drm->dev_private;
	u32 cntl;

	if (!priv->variant->broken_vblank)
		drm_crtc_vblank_off(crtc);

	/* Power Down */
	cntl = readl(priv->regs + priv->ctrl);
	if (cntl & CNTL_LCDPWR) {
		cntl &= ~CNTL_LCDPWR;
		writel(cntl, priv->regs + priv->ctrl);
	}

	/*
	 * We expect this delay to stabilize the contrast voltage Vee as
	 * stipulated by the manual
	 */
	msleep(20);

	if (priv->variant_display_disable)
		priv->variant_display_disable(drm);

	/* Disable */
	writel(0, priv->regs + priv->ctrl);

	clk_disable_unprepare(priv->clk);
}