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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct fimc_lite {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  fimc_lite_clk_put (struct fimc_lite*) ; 
 int /*<<< orphan*/  fimc_lite_unregister_capture_subdev (struct fimc_lite*) ; 
 struct fimc_lite* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (struct device*) ; 
 int /*<<< orphan*/  vb2_dma_contig_clear_max_seg_size (struct device*) ; 

__attribute__((used)) static int fimc_lite_remove(struct platform_device *pdev)
{
	struct fimc_lite *fimc = platform_get_drvdata(pdev);
	struct device *dev = &pdev->dev;

	pm_runtime_disable(dev);
	pm_runtime_set_suspended(dev);
	fimc_lite_unregister_capture_subdev(fimc);
	vb2_dma_contig_clear_max_seg_size(dev);
	fimc_lite_clk_put(fimc);

	dev_info(dev, "Driver unloaded\n");
	return 0;
}