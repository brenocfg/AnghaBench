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
typedef  int /*<<< orphan*/  u32 ;
struct mcde_dsi {int /*<<< orphan*/  lp_clk; int /*<<< orphan*/  hs_clk; scalar_t__ regs; TYPE_1__* mdsi; } ;
struct drm_bridge {int dummy; } ;
struct TYPE_2__ {int mode_flags; } ;

/* Variables and functions */
 scalar_t__ DSI_MCTL_MAIN_DATA_CTL ; 
 int /*<<< orphan*/  DSI_MCTL_MAIN_DATA_CTL_VID_EN ; 
 scalar_t__ DSI_VID_MODE_STS_CTL ; 
 int MIPI_DSI_MODE_VIDEO ; 
 struct mcde_dsi* bridge_to_mcde_dsi (struct drm_bridge*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcde_dsi_wait_for_command_mode_stop (struct mcde_dsi*) ; 
 int /*<<< orphan*/  mcde_dsi_wait_for_video_mode_stop (struct mcde_dsi*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mcde_dsi_bridge_disable(struct drm_bridge *bridge)
{
	struct mcde_dsi *d = bridge_to_mcde_dsi(bridge);
	u32 val;

	/* Disable all error interrupts */
	writel(0, d->regs + DSI_VID_MODE_STS_CTL);

	if (d->mdsi->mode_flags & MIPI_DSI_MODE_VIDEO) {
		/* Stop video mode */
		val = readl(d->regs + DSI_MCTL_MAIN_DATA_CTL);
		val &= ~DSI_MCTL_MAIN_DATA_CTL_VID_EN;
		writel(val, d->regs + DSI_MCTL_MAIN_DATA_CTL);
		mcde_dsi_wait_for_video_mode_stop(d);
	} else {
		/* Stop command mode */
		mcde_dsi_wait_for_command_mode_stop(d);
	}

	/* Stop clocks */
	clk_disable_unprepare(d->hs_clk);
	clk_disable_unprepare(d->lp_clk);
}