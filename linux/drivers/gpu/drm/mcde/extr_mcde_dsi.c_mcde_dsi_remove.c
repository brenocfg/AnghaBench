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
struct mcde_dsi {int /*<<< orphan*/  dsi_host; } ;

/* Variables and functions */
 int /*<<< orphan*/  component_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mcde_dsi_component_ops ; 
 int /*<<< orphan*/  mipi_dsi_host_unregister (int /*<<< orphan*/ *) ; 
 struct mcde_dsi* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int mcde_dsi_remove(struct platform_device *pdev)
{
	struct mcde_dsi *d = platform_get_drvdata(pdev);

	component_del(&pdev->dev, &mcde_dsi_component_ops);
	mipi_dsi_host_unregister(&d->dsi_host);

	return 0;
}