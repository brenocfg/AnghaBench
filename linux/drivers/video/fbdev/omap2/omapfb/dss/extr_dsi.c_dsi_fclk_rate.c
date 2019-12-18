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
struct dsi_data {int /*<<< orphan*/  dss_clk; int /*<<< orphan*/  module_id; } ;

/* Variables and functions */
 scalar_t__ OMAP_DSS_CLK_SRC_FCK ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 struct dsi_data* dsi_get_dsidrv_data (struct platform_device*) ; 
 unsigned long dsi_get_pll_hsdiv_dsi_rate (struct platform_device*) ; 
 scalar_t__ dss_get_dsi_clk_source (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long dsi_fclk_rate(struct platform_device *dsidev)
{
	unsigned long r;
	struct dsi_data *dsi = dsi_get_dsidrv_data(dsidev);

	if (dss_get_dsi_clk_source(dsi->module_id) == OMAP_DSS_CLK_SRC_FCK) {
		/* DSI FCLK source is DSS_CLK_FCK */
		r = clk_get_rate(dsi->dss_clk);
	} else {
		/* DSI FCLK source is dsi_pll_hsdiv_dsi_clk */
		r = dsi_get_pll_hsdiv_dsi_rate(dsidev);
	}

	return r;
}