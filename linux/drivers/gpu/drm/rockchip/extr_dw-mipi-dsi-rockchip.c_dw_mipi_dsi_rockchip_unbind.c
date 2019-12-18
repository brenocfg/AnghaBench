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
struct dw_mipi_dsi_rockchip {int /*<<< orphan*/  pllref_clk; int /*<<< orphan*/  dmd; scalar_t__ is_slave; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct dw_mipi_dsi_rockchip* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dw_mipi_dsi_unbind (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dw_mipi_dsi_rockchip_unbind(struct device *dev,
					struct device *master,
					void *data)
{
	struct dw_mipi_dsi_rockchip *dsi = dev_get_drvdata(dev);

	if (dsi->is_slave)
		return;

	dw_mipi_dsi_unbind(dsi->dmd);

	clk_disable_unprepare(dsi->pllref_clk);
}