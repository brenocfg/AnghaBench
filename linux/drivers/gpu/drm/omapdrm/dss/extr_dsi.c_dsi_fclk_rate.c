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
struct dsi_data {int /*<<< orphan*/  dss_clk; int /*<<< orphan*/  module_id; int /*<<< orphan*/  dss; } ;
typedef  enum dss_clk_source { ____Placeholder_dss_clk_source } dss_clk_source ;

/* Variables and functions */
 int DSS_CLK_SRC_FCK ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 unsigned long dsi_get_pll_hsdiv_dsi_rate (struct dsi_data*) ; 
 int dss_get_dsi_clk_source (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long dsi_fclk_rate(struct dsi_data *dsi)
{
	unsigned long r;
	enum dss_clk_source source;

	source = dss_get_dsi_clk_source(dsi->dss, dsi->module_id);
	if (source == DSS_CLK_SRC_FCK) {
		/* DSI FCLK source is DSS_CLK_FCK */
		r = clk_get_rate(dsi->dss_clk);
	} else {
		/* DSI FCLK source is dsi_pll_hsdiv_dsi_clk */
		r = dsi_get_pll_hsdiv_dsi_rate(dsi);
	}

	return r;
}