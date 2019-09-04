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
struct omap_dss_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dispc_channel; } ;
struct dpi_data {int /*<<< orphan*/  lock; scalar_t__ vdds_dsi_reg; TYPE_1__* dss; scalar_t__ pll; TYPE_2__ output; } ;
struct TYPE_3__ {int /*<<< orphan*/  dispc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSS_CLK_SRC_FCK ; 
 int /*<<< orphan*/  dispc_runtime_put (int /*<<< orphan*/ ) ; 
 struct dpi_data* dpi_get_data_from_dssdev (struct omap_dss_device*) ; 
 int /*<<< orphan*/  dss_mgr_disable (TYPE_2__*) ; 
 int /*<<< orphan*/  dss_pll_disable (scalar_t__) ; 
 int /*<<< orphan*/  dss_select_lcd_clk_source (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_disable (scalar_t__) ; 

__attribute__((used)) static void dpi_display_disable(struct omap_dss_device *dssdev)
{
	struct dpi_data *dpi = dpi_get_data_from_dssdev(dssdev);

	mutex_lock(&dpi->lock);

	dss_mgr_disable(&dpi->output);

	if (dpi->pll) {
		dss_select_lcd_clk_source(dpi->dss, dpi->output.dispc_channel,
					  DSS_CLK_SRC_FCK);
		dss_pll_disable(dpi->pll);
	}

	dispc_runtime_put(dpi->dss->dispc);

	if (dpi->vdds_dsi_reg)
		regulator_disable(dpi->vdds_dsi_reg);

	mutex_unlock(&dpi->lock);
}