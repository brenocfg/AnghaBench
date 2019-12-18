#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct phy_configure_opts_mipi_dphy {int dummy; } ;
union phy_configure_opts {struct phy_configure_opts_mipi_dphy mipi_dphy; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  u16 ;
struct sun6i_dsi {int /*<<< orphan*/  panel; int /*<<< orphan*/  dphy; int /*<<< orphan*/  regs; int /*<<< orphan*/  dev; struct mipi_dsi_device* device; } ;
struct mipi_dsi_device {int /*<<< orphan*/  lanes; int /*<<< orphan*/  format; } ;
struct drm_encoder {TYPE_2__* crtc; } ;
struct drm_display_mode {int clock; } ;
struct TYPE_4__ {TYPE_1__* state; } ;
struct TYPE_3__ {struct drm_display_mode adjusted_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  DSI_START_HSC ; 
 int /*<<< orphan*/  DSI_START_HSD ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_MODE_MIPI_DPHY ; 
 int /*<<< orphan*/  SUN6I_DSI_BASIC_CTL1_REG ; 
 int SUN6I_DSI_BASIC_CTL1_VIDEO_FILL ; 
 int SUN6I_DSI_BASIC_CTL1_VIDEO_MODE ; 
 int SUN6I_DSI_BASIC_CTL1_VIDEO_PRECISION ; 
 int SUN6I_DSI_BASIC_CTL1_VIDEO_ST_DELAY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_panel_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_panel_prepare (int /*<<< orphan*/ ) ; 
 struct sun6i_dsi* encoder_to_sun6i_dsi (struct drm_encoder*) ; 
 int /*<<< orphan*/  mipi_dsi_pixel_format_to_bpp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_configure (int /*<<< orphan*/ ,union phy_configure_opts*) ; 
 int /*<<< orphan*/  phy_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_mipi_dphy_get_default_config (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct phy_configure_opts_mipi_dphy*) ; 
 int /*<<< orphan*/  phy_power_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_set_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sun6i_dsi_get_video_start_delay (struct sun6i_dsi*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  sun6i_dsi_setup_burst (struct sun6i_dsi*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  sun6i_dsi_setup_format (struct sun6i_dsi*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  sun6i_dsi_setup_inst_loop (struct sun6i_dsi*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  sun6i_dsi_setup_timings (struct sun6i_dsi*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  sun6i_dsi_start (struct sun6i_dsi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void sun6i_dsi_encoder_enable(struct drm_encoder *encoder)
{
	struct drm_display_mode *mode = &encoder->crtc->state->adjusted_mode;
	struct sun6i_dsi *dsi = encoder_to_sun6i_dsi(encoder);
	struct mipi_dsi_device *device = dsi->device;
	union phy_configure_opts opts = { 0 };
	struct phy_configure_opts_mipi_dphy *cfg = &opts.mipi_dphy;
	u16 delay;

	DRM_DEBUG_DRIVER("Enabling DSI output\n");

	pm_runtime_get_sync(dsi->dev);

	delay = sun6i_dsi_get_video_start_delay(dsi, mode);
	regmap_write(dsi->regs, SUN6I_DSI_BASIC_CTL1_REG,
		     SUN6I_DSI_BASIC_CTL1_VIDEO_ST_DELAY(delay) |
		     SUN6I_DSI_BASIC_CTL1_VIDEO_FILL |
		     SUN6I_DSI_BASIC_CTL1_VIDEO_PRECISION |
		     SUN6I_DSI_BASIC_CTL1_VIDEO_MODE);

	sun6i_dsi_setup_burst(dsi, mode);
	sun6i_dsi_setup_inst_loop(dsi, mode);
	sun6i_dsi_setup_format(dsi, mode);
	sun6i_dsi_setup_timings(dsi, mode);

	phy_init(dsi->dphy);

	phy_mipi_dphy_get_default_config(mode->clock * 1000,
					 mipi_dsi_pixel_format_to_bpp(device->format),
					 device->lanes, cfg);

	phy_set_mode(dsi->dphy, PHY_MODE_MIPI_DPHY);
	phy_configure(dsi->dphy, &opts);
	phy_power_on(dsi->dphy);

	if (!IS_ERR(dsi->panel))
		drm_panel_prepare(dsi->panel);

	/*
	 * FIXME: This should be moved after the switch to HS mode.
	 *
	 * Unfortunately, once in HS mode, it seems like we're not
	 * able to send DCS commands anymore, which would prevent any
	 * panel to send any DCS command as part as their enable
	 * method, which is quite common.
	 *
	 * I haven't seen any artifact due to that sub-optimal
	 * ordering on the panels I've tested it with, so I guess this
	 * will do for now, until that IP is better understood.
	 */
	if (!IS_ERR(dsi->panel))
		drm_panel_enable(dsi->panel);

	sun6i_dsi_start(dsi, DSI_START_HSC);

	udelay(1000);

	sun6i_dsi_start(dsi, DSI_START_HSD);
}