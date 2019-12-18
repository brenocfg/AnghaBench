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
struct rspi_data {int /*<<< orphan*/  ctlr; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct rspi_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rspi_release_dma (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rspi_remove(struct platform_device *pdev)
{
	struct rspi_data *rspi = platform_get_drvdata(pdev);

	rspi_release_dma(rspi->ctlr);
	pm_runtime_disable(&pdev->dev);

	return 0;
}