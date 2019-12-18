#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dw_mipi_dsi_rockchip {int /*<<< orphan*/  grf_clk; struct dw_mipi_dsi_rockchip* slave; TYPE_1__* dev; int /*<<< orphan*/  encoder; } ;
struct drm_encoder {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int drm_of_encoder_active_endpoint_id (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dw_mipi_dsi_rockchip_config (struct dw_mipi_dsi_rockchip*,int) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (TYPE_1__*) ; 
 struct dw_mipi_dsi_rockchip* to_dsi (struct drm_encoder*) ; 

__attribute__((used)) static void dw_mipi_dsi_encoder_enable(struct drm_encoder *encoder)
{
	struct dw_mipi_dsi_rockchip *dsi = to_dsi(encoder);
	int ret, mux;

	mux = drm_of_encoder_active_endpoint_id(dsi->dev->of_node,
						&dsi->encoder);
	if (mux < 0)
		return;

	pm_runtime_get_sync(dsi->dev);
	if (dsi->slave)
		pm_runtime_get_sync(dsi->slave->dev);

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

	dw_mipi_dsi_rockchip_config(dsi, mux);
	if (dsi->slave)
		dw_mipi_dsi_rockchip_config(dsi->slave, mux);

	clk_disable_unprepare(dsi->grf_clk);
}