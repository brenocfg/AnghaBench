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
struct dw_mipi_dsi_rockchip {scalar_t__ devcnt; int /*<<< orphan*/  dmd; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  component_del (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dw_mipi_dsi_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_mipi_dsi_rockchip_ops ; 
 struct dw_mipi_dsi_rockchip* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int dw_mipi_dsi_rockchip_remove(struct platform_device *pdev)
{
	struct dw_mipi_dsi_rockchip *dsi = platform_get_drvdata(pdev);

	if (dsi->devcnt == 0)
		component_del(dsi->dev, &dw_mipi_dsi_rockchip_ops);

	dw_mipi_dsi_remove(dsi->dmd);

	return 0;
}