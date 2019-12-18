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
struct mcde_dsi {scalar_t__ regs; TYPE_1__* mdsi; void* hs_freq; int /*<<< orphan*/  dev; int /*<<< orphan*/  hs_clk; void* lp_freq; int /*<<< orphan*/  lp_clk; } ;
struct drm_display_mode {int clock; int /*<<< orphan*/  vdisplay; int /*<<< orphan*/  hdisplay; } ;
struct drm_bridge {int dummy; } ;
struct TYPE_2__ {int mode_flags; long lp_rate; long hs_rate; } ;

/* Variables and functions */
 scalar_t__ DSI_CMD_MODE_CTL ; 
 int /*<<< orphan*/  DSI_CMD_MODE_CTL_IF1_ID_MASK ; 
 unsigned long DSI_DEFAULT_HS_FREQ_HZ ; 
 unsigned long DSI_DEFAULT_LP_FREQ_HZ ; 
 int MIPI_DSI_MODE_VIDEO ; 
 struct mcde_dsi* bridge_to_mcde_dsi (struct drm_bridge*) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 void* clk_round_rate (int /*<<< orphan*/ ,unsigned long) ; 
 int clk_set_rate (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,void*,...) ; 
 int /*<<< orphan*/  mcde_dsi_setup_video_mode (struct mcde_dsi*,struct drm_display_mode const*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mcde_dsi_bridge_mode_set(struct drm_bridge *bridge,
				     const struct drm_display_mode *mode,
				     const struct drm_display_mode *adj)
{
	struct mcde_dsi *d = bridge_to_mcde_dsi(bridge);
	unsigned long pixel_clock_hz = mode->clock * 1000;
	unsigned long hs_freq, lp_freq;
	u32 val;
	int ret;

	if (!d->mdsi) {
		dev_err(d->dev, "no DSI device attached to encoder!\n");
		return;
	}

	dev_info(d->dev, "set DSI master to %dx%d %lu Hz %s mode\n",
		 mode->hdisplay, mode->vdisplay, pixel_clock_hz,
		 (d->mdsi->mode_flags & MIPI_DSI_MODE_VIDEO) ? "VIDEO" : "CMD"
		);

	/* Copy maximum clock frequencies */
	if (d->mdsi->lp_rate)
		lp_freq = d->mdsi->lp_rate;
	else
		lp_freq = DSI_DEFAULT_LP_FREQ_HZ;
	if (d->mdsi->hs_rate)
		hs_freq = d->mdsi->hs_rate;
	else
		hs_freq = DSI_DEFAULT_HS_FREQ_HZ;

	/* Enable LP (Low Power, Energy Save, ES) and HS (High Speed) clocks */
	d->lp_freq = clk_round_rate(d->lp_clk, lp_freq);
	ret = clk_set_rate(d->lp_clk, d->lp_freq);
	if (ret)
		dev_err(d->dev, "failed to set LP clock rate %lu Hz\n",
			d->lp_freq);

	d->hs_freq = clk_round_rate(d->hs_clk, hs_freq);
	ret = clk_set_rate(d->hs_clk, d->hs_freq);
	if (ret)
		dev_err(d->dev, "failed to set HS clock rate %lu Hz\n",
			d->hs_freq);

	/* Start clocks */
	ret = clk_prepare_enable(d->lp_clk);
	if (ret)
		dev_err(d->dev, "failed to enable LP clock\n");
	else
		dev_info(d->dev, "DSI LP clock rate %lu Hz\n",
			 d->lp_freq);
	ret = clk_prepare_enable(d->hs_clk);
	if (ret)
		dev_err(d->dev, "failed to enable HS clock\n");
	else
		dev_info(d->dev, "DSI HS clock rate %lu Hz\n",
			 d->hs_freq);

	if (d->mdsi->mode_flags & MIPI_DSI_MODE_VIDEO) {
		mcde_dsi_setup_video_mode(d, mode);
	} else {
		/* Command mode, clear IF1 ID */
		val = readl(d->regs + DSI_CMD_MODE_CTL);
		/*
		 * If we enable low-power mode here with
		 * val |= DSI_CMD_MODE_CTL_IF1_LP_EN
		 * the display updates become really slow.
		 */
		val &= ~DSI_CMD_MODE_CTL_IF1_ID_MASK;
		writel(val, d->regs + DSI_CMD_MODE_CTL);
	}
}