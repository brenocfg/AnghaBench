#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct dw_mipi_dsi_plat_data {int grf_dsi0_mode; int dsi0_en_bit; scalar_t__ grf_switch_reg; scalar_t__ grf_dsi0_mode_reg; } ;
struct dw_mipi_dsi {scalar_t__ dpms_mode; int /*<<< orphan*/  grf_clk; TYPE_3__* dev; int /*<<< orphan*/  grf_regmap; int /*<<< orphan*/  pclk; int /*<<< orphan*/  panel; struct dw_mipi_dsi_plat_data* pdata; } ;
struct drm_encoder {TYPE_2__* crtc; } ;
struct drm_display_mode {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_7__ {TYPE_1__* state; } ;
struct TYPE_6__ {struct drm_display_mode adjusted_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG (TYPE_3__*,char*,char*) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (TYPE_3__*,char*,...) ; 
 scalar_t__ DRM_MODE_DPMS_ON ; 
 int /*<<< orphan*/  DW_MIPI_DSI_CMD_MODE ; 
 int /*<<< orphan*/  DW_MIPI_DSI_VID_MODE ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int drm_of_encoder_active_endpoint_id (int /*<<< orphan*/ ,struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_panel_enable (int /*<<< orphan*/ ) ; 
 scalar_t__ drm_panel_prepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_mipi_dsi_clear_err (struct dw_mipi_dsi*) ; 
 int /*<<< orphan*/  dw_mipi_dsi_command_mode_config (struct dw_mipi_dsi*) ; 
 int /*<<< orphan*/  dw_mipi_dsi_dphy_interface_config (struct dw_mipi_dsi*) ; 
 int /*<<< orphan*/  dw_mipi_dsi_dphy_timing_config (struct dw_mipi_dsi*) ; 
 int /*<<< orphan*/  dw_mipi_dsi_dpi_config (struct dw_mipi_dsi*,struct drm_display_mode*) ; 
 int dw_mipi_dsi_get_lane_bps (struct dw_mipi_dsi*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  dw_mipi_dsi_init (struct dw_mipi_dsi*) ; 
 int /*<<< orphan*/  dw_mipi_dsi_line_timer_config (struct dw_mipi_dsi*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  dw_mipi_dsi_packet_handler_config (struct dw_mipi_dsi*) ; 
 int /*<<< orphan*/  dw_mipi_dsi_phy_init (struct dw_mipi_dsi*) ; 
 int /*<<< orphan*/  dw_mipi_dsi_set_mode (struct dw_mipi_dsi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_mipi_dsi_vertical_timing_config (struct dw_mipi_dsi*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  dw_mipi_dsi_video_mode_config (struct dw_mipi_dsi*) ; 
 int /*<<< orphan*/  dw_mipi_dsi_video_packet_config (struct dw_mipi_dsi*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  dw_mipi_dsi_wait_for_two_frames (struct drm_display_mode*) ; 
 struct dw_mipi_dsi* encoder_to_dsi (struct drm_encoder*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (TYPE_3__*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void dw_mipi_dsi_encoder_enable(struct drm_encoder *encoder)
{
	struct dw_mipi_dsi *dsi = encoder_to_dsi(encoder);
	struct drm_display_mode *mode = &encoder->crtc->state->adjusted_mode;
	const struct dw_mipi_dsi_plat_data *pdata = dsi->pdata;
	int mux = drm_of_encoder_active_endpoint_id(dsi->dev->of_node, encoder);
	u32 val;
	int ret;

	ret = dw_mipi_dsi_get_lane_bps(dsi, mode);
	if (ret < 0)
		return;

	if (dsi->dpms_mode == DRM_MODE_DPMS_ON)
		return;

	if (clk_prepare_enable(dsi->pclk)) {
		DRM_DEV_ERROR(dsi->dev, "Failed to enable pclk\n");
		return;
	}

	pm_runtime_get_sync(dsi->dev);
	dw_mipi_dsi_init(dsi);
	dw_mipi_dsi_dpi_config(dsi, mode);
	dw_mipi_dsi_packet_handler_config(dsi);
	dw_mipi_dsi_video_mode_config(dsi);
	dw_mipi_dsi_video_packet_config(dsi, mode);
	dw_mipi_dsi_command_mode_config(dsi);
	dw_mipi_dsi_line_timer_config(dsi, mode);
	dw_mipi_dsi_vertical_timing_config(dsi, mode);
	dw_mipi_dsi_dphy_timing_config(dsi);
	dw_mipi_dsi_dphy_interface_config(dsi);
	dw_mipi_dsi_clear_err(dsi);

	/*
	 * For the RK3399, the clk of grf must be enabled before writing grf
	 * register. And for RK3288 or other soc, this grf_clk must be NULL,
	 * the clk_prepare_enable return true directly.
	 */
	ret = clk_prepare_enable(dsi->grf_clk);
	if (ret) {
		DRM_DEV_ERROR(dsi->dev, "Failed to enable grf_clk: %d\n", ret);
		return;
	}

	if (pdata->grf_dsi0_mode_reg)
		regmap_write(dsi->grf_regmap, pdata->grf_dsi0_mode_reg,
			     pdata->grf_dsi0_mode);

	dw_mipi_dsi_phy_init(dsi);
	dw_mipi_dsi_wait_for_two_frames(mode);

	dw_mipi_dsi_set_mode(dsi, DW_MIPI_DSI_CMD_MODE);
	if (drm_panel_prepare(dsi->panel))
		DRM_DEV_ERROR(dsi->dev, "failed to prepare panel\n");

	dw_mipi_dsi_set_mode(dsi, DW_MIPI_DSI_VID_MODE);
	drm_panel_enable(dsi->panel);

	clk_disable_unprepare(dsi->pclk);

	if (mux)
		val = pdata->dsi0_en_bit | (pdata->dsi0_en_bit << 16);
	else
		val = pdata->dsi0_en_bit << 16;

	regmap_write(dsi->grf_regmap, pdata->grf_switch_reg, val);
	DRM_DEV_DEBUG(dsi->dev,
		      "vop %s output to dsi0\n", (mux) ? "LIT" : "BIG");
	dsi->dpms_mode = DRM_MODE_DPMS_ON;

	clk_disable_unprepare(dsi->grf_clk);
}