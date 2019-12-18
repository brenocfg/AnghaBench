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
struct omap_overlay_manager {int /*<<< orphan*/  id; } ;
struct omap_dss_device {int dummy; } ;
struct TYPE_2__ {struct omap_overlay_manager* manager; } ;
struct dpi_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  vdds_dsi_reg; scalar_t__ pll; TYPE_1__ output; } ;

/* Variables and functions */
 int /*<<< orphan*/  FEAT_DPI_USES_VDDS_DSI ; 
 int /*<<< orphan*/  OMAP_DSS_CLK_SRC_FCK ; 
 int /*<<< orphan*/  dispc_runtime_put () ; 
 struct dpi_data* dpi_get_data_from_dssdev (struct omap_dss_device*) ; 
 scalar_t__ dss_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dss_mgr_disable (struct omap_overlay_manager*) ; 
 int /*<<< orphan*/  dss_pll_disable (scalar_t__) ; 
 int /*<<< orphan*/  dss_select_lcd_clk_source (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dpi_display_disable(struct omap_dss_device *dssdev)
{
	struct dpi_data *dpi = dpi_get_data_from_dssdev(dssdev);
	struct omap_overlay_manager *mgr = dpi->output.manager;

	mutex_lock(&dpi->lock);

	dss_mgr_disable(mgr);

	if (dpi->pll) {
		dss_select_lcd_clk_source(mgr->id, OMAP_DSS_CLK_SRC_FCK);
		dss_pll_disable(dpi->pll);
	}

	dispc_runtime_put();

	if (dss_has_feature(FEAT_DPI_USES_VDDS_DSI))
		regulator_disable(dpi->vdds_dsi_reg);

	mutex_unlock(&dpi->lock);
}