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
struct fimc_dev {int /*<<< orphan*/ * clock; } ;

/* Variables and functions */
 size_t CLK_BUS ; 
 size_t CLK_GATE ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fimc_clk_put (struct fimc_dev*) ; 
 int /*<<< orphan*/  fimc_unregister_capture_subdev (struct fimc_dev*) ; 
 struct fimc_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_status_suspended (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vb2_dma_contig_clear_max_seg_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fimc_remove(struct platform_device *pdev)
{
	struct fimc_dev *fimc = platform_get_drvdata(pdev);

	pm_runtime_disable(&pdev->dev);
	if (!pm_runtime_status_suspended(&pdev->dev))
		clk_disable(fimc->clock[CLK_GATE]);
	pm_runtime_set_suspended(&pdev->dev);

	fimc_unregister_capture_subdev(fimc);
	vb2_dma_contig_clear_max_seg_size(&pdev->dev);

	clk_disable(fimc->clock[CLK_BUS]);
	fimc_clk_put(fimc);

	dev_info(&pdev->dev, "driver unloaded\n");
	return 0;
}