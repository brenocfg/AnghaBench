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
struct sun6i_dsi {int /*<<< orphan*/  mod_clk; int /*<<< orphan*/  host; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_rate_exclusive_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  component_del (struct device*,int /*<<< orphan*/ *) ; 
 struct sun6i_dsi* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mipi_dsi_host_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  sun6i_dsi_ops ; 

__attribute__((used)) static int sun6i_dsi_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct sun6i_dsi *dsi = dev_get_drvdata(dev);

	component_del(&pdev->dev, &sun6i_dsi_ops);
	mipi_dsi_host_unregister(&dsi->host);
	pm_runtime_disable(dev);
	clk_rate_exclusive_put(dsi->mod_clk);

	return 0;
}