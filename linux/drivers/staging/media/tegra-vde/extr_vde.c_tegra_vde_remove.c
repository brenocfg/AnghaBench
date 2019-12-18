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
struct tegra_vde {int /*<<< orphan*/  iram_pool; scalar_t__ iram; int /*<<< orphan*/  miscdev; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  gen_pool_free (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_pool_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 struct tegra_vde* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_dont_use_autosuspend (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enabled (struct device*) ; 
 int /*<<< orphan*/  tegra_vde_dmabuf_cache_unmap_all (struct tegra_vde*) ; 
 int /*<<< orphan*/  tegra_vde_iommu_deinit (struct tegra_vde*) ; 
 int tegra_vde_runtime_suspend (struct device*) ; 

__attribute__((used)) static int tegra_vde_remove(struct platform_device *pdev)
{
	struct tegra_vde *vde = platform_get_drvdata(pdev);
	struct device *dev = &pdev->dev;
	int err;

	if (!pm_runtime_enabled(dev)) {
		err = tegra_vde_runtime_suspend(dev);
		if (err)
			return err;
	}

	pm_runtime_dont_use_autosuspend(dev);
	pm_runtime_disable(dev);

	misc_deregister(&vde->miscdev);

	tegra_vde_dmabuf_cache_unmap_all(vde);
	tegra_vde_iommu_deinit(vde);

	gen_pool_free(vde->iram_pool, (unsigned long)vde->iram,
		      gen_pool_size(vde->iram_pool));

	return 0;
}