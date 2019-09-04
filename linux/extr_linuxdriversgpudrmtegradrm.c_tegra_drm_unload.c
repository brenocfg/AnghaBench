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
struct TYPE_2__ {int /*<<< orphan*/  domain; } ;
struct tegra_drm {scalar_t__ domain; TYPE_1__ carveout; int /*<<< orphan*/  mm; int /*<<< orphan*/  mm_lock; } ;
struct host1x_device {int dummy; } ;
struct drm_device {struct tegra_drm* dev_private; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_atomic_helper_shutdown (struct drm_device*) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_fini (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mm_takedown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (struct drm_device*) ; 
 int host1x_device_exit (struct host1x_device*) ; 
 int /*<<< orphan*/  iommu_domain_free (scalar_t__) ; 
 int /*<<< orphan*/  iova_cache_put () ; 
 int /*<<< orphan*/  kfree (struct tegra_drm*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_iova_domain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tegra_drm_fb_exit (struct drm_device*) ; 
 struct host1x_device* to_host1x_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_drm_unload(struct drm_device *drm)
{
	struct host1x_device *device = to_host1x_device(drm->dev);
	struct tegra_drm *tegra = drm->dev_private;
	int err;

	drm_kms_helper_poll_fini(drm);
	tegra_drm_fb_exit(drm);
	drm_atomic_helper_shutdown(drm);
	drm_mode_config_cleanup(drm);

	err = host1x_device_exit(device);
	if (err < 0)
		return;

	if (tegra->domain) {
		mutex_destroy(&tegra->mm_lock);
		drm_mm_takedown(&tegra->mm);
		put_iova_domain(&tegra->carveout.domain);
		iova_cache_put();
		iommu_domain_free(tegra->domain);
	}

	kfree(tegra);
}