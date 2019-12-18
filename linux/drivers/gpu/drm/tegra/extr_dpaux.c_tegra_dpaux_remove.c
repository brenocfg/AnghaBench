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
struct tegra_dpaux {int /*<<< orphan*/  list; int /*<<< orphan*/  aux; int /*<<< orphan*/  work; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dpaux_lock ; 
 int /*<<< orphan*/  drm_dp_aux_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct tegra_dpaux* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tegra_dpaux_pad_power_down (struct tegra_dpaux*) ; 

__attribute__((used)) static int tegra_dpaux_remove(struct platform_device *pdev)
{
	struct tegra_dpaux *dpaux = platform_get_drvdata(pdev);

	cancel_work_sync(&dpaux->work);

	/* make sure pads are powered down when not in use */
	tegra_dpaux_pad_power_down(dpaux);

	pm_runtime_put(&pdev->dev);
	pm_runtime_disable(&pdev->dev);

	drm_dp_aux_unregister(&dpaux->aux);

	mutex_lock(&dpaux_lock);
	list_del(&dpaux->list);
	mutex_unlock(&dpaux_lock);

	return 0;
}