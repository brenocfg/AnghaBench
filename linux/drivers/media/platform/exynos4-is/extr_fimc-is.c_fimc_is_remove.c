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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  f_w; } ;
struct fimc_is {TYPE_1__ fw; int /*<<< orphan*/  pmu_regs; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 struct fimc_is* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  fimc_is_debugfs_remove (struct fimc_is*) ; 
 int /*<<< orphan*/  fimc_is_free_cpu_memory (struct fimc_is*) ; 
 int /*<<< orphan*/  fimc_is_put_clocks (struct fimc_is*) ; 
 int /*<<< orphan*/  fimc_is_runtime_suspend (struct device*) ; 
 int /*<<< orphan*/  fimc_is_unregister_subdevs (struct fimc_is*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct fimc_is*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_status_suspended (struct device*) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_dma_contig_clear_max_seg_size (struct device*) ; 

__attribute__((used)) static int fimc_is_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct fimc_is *is = dev_get_drvdata(dev);

	pm_runtime_disable(dev);
	pm_runtime_set_suspended(dev);
	if (!pm_runtime_status_suspended(dev))
		fimc_is_runtime_suspend(dev);
	free_irq(is->irq, is);
	fimc_is_unregister_subdevs(is);
	vb2_dma_contig_clear_max_seg_size(dev);
	fimc_is_put_clocks(is);
	iounmap(is->pmu_regs);
	fimc_is_debugfs_remove(is);
	release_firmware(is->fw.f_w);
	fimc_is_free_cpu_memory(is);

	return 0;
}