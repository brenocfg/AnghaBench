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
struct platform_device {int dummy; } ;
struct panfrost_device {int /*<<< orphan*/  dev; struct drm_device* ddev; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_dev_put (struct drm_device*) ; 
 int /*<<< orphan*/  drm_dev_unregister (struct drm_device*) ; 
 int /*<<< orphan*/  panfrost_devfreq_fini (struct panfrost_device*) ; 
 int /*<<< orphan*/  panfrost_device_fini (struct panfrost_device*) ; 
 int /*<<< orphan*/  panfrost_gem_shrinker_cleanup (struct drm_device*) ; 
 struct panfrost_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync_suspend (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int panfrost_remove(struct platform_device *pdev)
{
	struct panfrost_device *pfdev = platform_get_drvdata(pdev);
	struct drm_device *ddev = pfdev->ddev;

	drm_dev_unregister(ddev);
	panfrost_gem_shrinker_cleanup(ddev);

	pm_runtime_get_sync(pfdev->dev);
	panfrost_devfreq_fini(pfdev);
	panfrost_device_fini(pfdev);
	pm_runtime_put_sync_suspend(pfdev->dev);
	pm_runtime_disable(pfdev->dev);

	drm_dev_put(ddev);
	return 0;
}