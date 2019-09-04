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
struct dw_mipi_dsi {scalar_t__ dpms_mode; int /*<<< orphan*/  pclk; int /*<<< orphan*/  dev; int /*<<< orphan*/  panel; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ DRM_MODE_DPMS_OFF ; 
 scalar_t__ DRM_MODE_DPMS_ON ; 
 int /*<<< orphan*/  DW_MIPI_DSI_CMD_MODE ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 scalar_t__ clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_panel_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_panel_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_mipi_dsi_disable (struct dw_mipi_dsi*) ; 
 int /*<<< orphan*/  dw_mipi_dsi_set_mode (struct dw_mipi_dsi*,int /*<<< orphan*/ ) ; 
 struct dw_mipi_dsi* encoder_to_dsi (struct drm_encoder*) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dw_mipi_dsi_encoder_disable(struct drm_encoder *encoder)
{
	struct dw_mipi_dsi *dsi = encoder_to_dsi(encoder);

	if (dsi->dpms_mode != DRM_MODE_DPMS_ON)
		return;

	if (clk_prepare_enable(dsi->pclk)) {
		DRM_DEV_ERROR(dsi->dev, "Failed to enable pclk\n");
		return;
	}

	drm_panel_disable(dsi->panel);

	dw_mipi_dsi_set_mode(dsi, DW_MIPI_DSI_CMD_MODE);
	drm_panel_unprepare(dsi->panel);

	dw_mipi_dsi_disable(dsi);
	pm_runtime_put(dsi->dev);
	clk_disable_unprepare(dsi->pclk);
	dsi->dpms_mode = DRM_MODE_DPMS_OFF;
}