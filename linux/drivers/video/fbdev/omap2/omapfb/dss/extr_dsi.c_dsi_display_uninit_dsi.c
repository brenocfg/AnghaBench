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
struct platform_device {int dummy; } ;
struct dsi_data {int /*<<< orphan*/  module_id; int /*<<< orphan*/  ulps_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP_DSS_CLK_SRC_FCK ; 
 int /*<<< orphan*/  dsi_cio_uninit (struct platform_device*) ; 
 int /*<<< orphan*/  dsi_enter_ulps (struct platform_device*) ; 
 struct dsi_data* dsi_get_dsidrv_data (struct platform_device*) ; 
 int /*<<< orphan*/  dsi_if_enable (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_pll_uninit (struct platform_device*,int) ; 
 int /*<<< orphan*/  dsi_vc_enable (struct platform_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dss_select_dsi_clk_source (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dsi_display_uninit_dsi(struct platform_device *dsidev,
		bool disconnect_lanes, bool enter_ulps)
{
	struct dsi_data *dsi = dsi_get_dsidrv_data(dsidev);

	if (enter_ulps && !dsi->ulps_enabled)
		dsi_enter_ulps(dsidev);

	/* disable interface */
	dsi_if_enable(dsidev, 0);
	dsi_vc_enable(dsidev, 0, 0);
	dsi_vc_enable(dsidev, 1, 0);
	dsi_vc_enable(dsidev, 2, 0);
	dsi_vc_enable(dsidev, 3, 0);

	dss_select_dsi_clk_source(dsi->module_id, OMAP_DSS_CLK_SRC_FCK);
	dsi_cio_uninit(dsidev);
	dsi_pll_uninit(dsidev, disconnect_lanes);
}