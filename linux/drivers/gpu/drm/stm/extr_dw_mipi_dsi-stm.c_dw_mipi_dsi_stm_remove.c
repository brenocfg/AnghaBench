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
struct dw_mipi_dsi_stm {int /*<<< orphan*/  vdd_supply; int /*<<< orphan*/  pllref_clk; int /*<<< orphan*/  dsi; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_mipi_dsi_remove (int /*<<< orphan*/ ) ; 
 struct dw_mipi_dsi_stm* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dw_mipi_dsi_stm_remove(struct platform_device *pdev)
{
	struct dw_mipi_dsi_stm *dsi = platform_get_drvdata(pdev);

	dw_mipi_dsi_remove(dsi->dsi);
	clk_disable_unprepare(dsi->pllref_clk);
	regulator_disable(dsi->vdd_supply);

	return 0;
}