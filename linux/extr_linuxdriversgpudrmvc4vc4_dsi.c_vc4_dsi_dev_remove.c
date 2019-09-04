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
struct vc4_dsi {int /*<<< orphan*/  dsi_host; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  component_del (struct device*,int /*<<< orphan*/ *) ; 
 struct vc4_dsi* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mipi_dsi_host_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc4_dsi_ops ; 

__attribute__((used)) static int vc4_dsi_dev_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct vc4_dsi *dsi = dev_get_drvdata(dev);

	component_del(&pdev->dev, &vc4_dsi_ops);
	mipi_dsi_host_unregister(&dsi->dsi_host);

	return 0;
}