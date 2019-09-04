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
struct dw_mipi_dsi {int /*<<< orphan*/  dev; int /*<<< orphan*/  pclk; TYPE_2__* panel_bridge; } ;
struct drm_bridge {int dummy; } ;
struct TYPE_4__ {TYPE_1__* funcs; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* post_disable ) (TYPE_2__*) ;} ;

/* Variables and functions */
 struct dw_mipi_dsi* bridge_to_dsi (struct drm_bridge*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_mipi_dsi_disable (struct dw_mipi_dsi*) ; 
 int /*<<< orphan*/  dw_mipi_dsi_set_mode (struct dw_mipi_dsi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void dw_mipi_dsi_bridge_post_disable(struct drm_bridge *bridge)
{
	struct dw_mipi_dsi *dsi = bridge_to_dsi(bridge);

	/*
	 * Switch to command mode before panel-bridge post_disable &
	 * panel unprepare.
	 * Note: panel-bridge disable & panel disable has been called
	 * before by the drm framework.
	 */
	dw_mipi_dsi_set_mode(dsi, 0);

	/*
	 * TODO Only way found to call panel-bridge post_disable &
	 * panel unprepare before the dsi "final" disable...
	 * This needs to be fixed in the drm_bridge framework and the API
	 * needs to be updated to manage our own call chains...
	 */
	dsi->panel_bridge->funcs->post_disable(dsi->panel_bridge);

	dw_mipi_dsi_disable(dsi);
	clk_disable_unprepare(dsi->pclk);
	pm_runtime_put(dsi->dev);
}