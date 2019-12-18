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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct cdns_dsi {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  mipi_dsi_host_unregister (int /*<<< orphan*/ *) ; 
 struct cdns_dsi* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cdns_dsi_drm_remove(struct platform_device *pdev)
{
	struct cdns_dsi *dsi = platform_get_drvdata(pdev);

	mipi_dsi_host_unregister(&dsi->base);
	pm_runtime_disable(&pdev->dev);

	return 0;
}