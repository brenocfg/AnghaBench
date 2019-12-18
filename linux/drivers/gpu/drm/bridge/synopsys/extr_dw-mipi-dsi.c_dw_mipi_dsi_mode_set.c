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
struct dw_mipi_dsi_phy_ops {int (* get_lane_mbps ) (void*,struct drm_display_mode const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int (* init ) (void*) ;} ;
struct dw_mipi_dsi {int /*<<< orphan*/  dev; int /*<<< orphan*/  lane_mbps; int /*<<< orphan*/  format; int /*<<< orphan*/  mode_flags; int /*<<< orphan*/  pclk; TYPE_1__* plat_data; } ;
struct drm_display_mode {int dummy; } ;
struct TYPE_2__ {void* priv_data; struct dw_mipi_dsi_phy_ops* phy_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_mipi_dsi_clear_err (struct dw_mipi_dsi*) ; 
 int /*<<< orphan*/  dw_mipi_dsi_command_mode_config (struct dw_mipi_dsi*) ; 
 int /*<<< orphan*/  dw_mipi_dsi_dphy_enable (struct dw_mipi_dsi*) ; 
 int /*<<< orphan*/  dw_mipi_dsi_dphy_init (struct dw_mipi_dsi*) ; 
 int /*<<< orphan*/  dw_mipi_dsi_dphy_interface_config (struct dw_mipi_dsi*) ; 
 int /*<<< orphan*/  dw_mipi_dsi_dphy_timing_config (struct dw_mipi_dsi*) ; 
 int /*<<< orphan*/  dw_mipi_dsi_dpi_config (struct dw_mipi_dsi*,struct drm_display_mode const*) ; 
 int /*<<< orphan*/  dw_mipi_dsi_get_lanes (struct dw_mipi_dsi*) ; 
 int /*<<< orphan*/  dw_mipi_dsi_init (struct dw_mipi_dsi*) ; 
 int /*<<< orphan*/  dw_mipi_dsi_line_timer_config (struct dw_mipi_dsi*,struct drm_display_mode const*) ; 
 int /*<<< orphan*/  dw_mipi_dsi_packet_handler_config (struct dw_mipi_dsi*) ; 
 int /*<<< orphan*/  dw_mipi_dsi_set_mode (struct dw_mipi_dsi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_mipi_dsi_vertical_timing_config (struct dw_mipi_dsi*,struct drm_display_mode const*) ; 
 int /*<<< orphan*/  dw_mipi_dsi_video_mode_config (struct dw_mipi_dsi*) ; 
 int /*<<< orphan*/  dw_mipi_dsi_video_packet_config (struct dw_mipi_dsi*,struct drm_display_mode const*) ; 
 int /*<<< orphan*/  dw_mipi_dsi_wait_for_two_frames (struct drm_display_mode const*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int stub1 (void*,struct drm_display_mode const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub2 (void*) ; 

__attribute__((used)) static void dw_mipi_dsi_mode_set(struct dw_mipi_dsi *dsi,
				 const struct drm_display_mode *adjusted_mode)
{
	const struct dw_mipi_dsi_phy_ops *phy_ops = dsi->plat_data->phy_ops;
	void *priv_data = dsi->plat_data->priv_data;
	int ret;
	u32 lanes = dw_mipi_dsi_get_lanes(dsi);

	clk_prepare_enable(dsi->pclk);

	ret = phy_ops->get_lane_mbps(priv_data, adjusted_mode, dsi->mode_flags,
				     lanes, dsi->format, &dsi->lane_mbps);
	if (ret)
		DRM_DEBUG_DRIVER("Phy get_lane_mbps() failed\n");

	pm_runtime_get_sync(dsi->dev);
	dw_mipi_dsi_init(dsi);
	dw_mipi_dsi_dpi_config(dsi, adjusted_mode);
	dw_mipi_dsi_packet_handler_config(dsi);
	dw_mipi_dsi_video_mode_config(dsi);
	dw_mipi_dsi_video_packet_config(dsi, adjusted_mode);
	dw_mipi_dsi_command_mode_config(dsi);
	dw_mipi_dsi_line_timer_config(dsi, adjusted_mode);
	dw_mipi_dsi_vertical_timing_config(dsi, adjusted_mode);

	dw_mipi_dsi_dphy_init(dsi);
	dw_mipi_dsi_dphy_timing_config(dsi);
	dw_mipi_dsi_dphy_interface_config(dsi);

	dw_mipi_dsi_clear_err(dsi);

	ret = phy_ops->init(priv_data);
	if (ret)
		DRM_DEBUG_DRIVER("Phy init() failed\n");

	dw_mipi_dsi_dphy_enable(dsi);

	dw_mipi_dsi_wait_for_two_frames(adjusted_mode);

	/* Switch to cmd mode for panel-bridge pre_enable & panel prepare */
	dw_mipi_dsi_set_mode(dsi, 0);
}