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
struct dsi_data {int /*<<< orphan*/  module_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_CLK_CTRL ; 
 int /*<<< orphan*/  DSI_COMPLEXIO_POWER_OFF ; 
 int /*<<< orphan*/  REG_FLD_MOD (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dsi_cio_power (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_disable_scp_clk (struct platform_device*) ; 
 struct dsi_data* dsi_get_dsidrv_data (struct platform_device*) ; 
 int /*<<< orphan*/  dsi_get_lane_mask (struct platform_device*) ; 
 int /*<<< orphan*/  dss_dsi_disable_pads (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dsi_cio_uninit(struct platform_device *dsidev)
{
	struct dsi_data *dsi = dsi_get_dsidrv_data(dsidev);

	/* DDR_CLK_ALWAYS_ON */
	REG_FLD_MOD(dsidev, DSI_CLK_CTRL, 0, 13, 13);

	dsi_cio_power(dsidev, DSI_COMPLEXIO_POWER_OFF);
	dsi_disable_scp_clk(dsidev);
	dss_dsi_disable_pads(dsi->module_id, dsi_get_lane_mask(dsidev));
}