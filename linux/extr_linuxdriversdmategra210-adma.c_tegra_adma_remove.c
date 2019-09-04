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
struct tegra_adma {int nr_channels; TYPE_1__* channels; int /*<<< orphan*/  dma_dev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_async_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_dispose_mapping (int /*<<< orphan*/ ) ; 
 struct tegra_adma* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_clk_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tegra_adma_remove(struct platform_device *pdev)
{
	struct tegra_adma *tdma = platform_get_drvdata(pdev);
	int i;

	dma_async_device_unregister(&tdma->dma_dev);

	for (i = 0; i < tdma->nr_channels; ++i)
		irq_dispose_mapping(tdma->channels[i].irq);

	pm_runtime_put_sync(&pdev->dev);
	pm_runtime_disable(&pdev->dev);
	pm_clk_destroy(&pdev->dev);

	return 0;
}