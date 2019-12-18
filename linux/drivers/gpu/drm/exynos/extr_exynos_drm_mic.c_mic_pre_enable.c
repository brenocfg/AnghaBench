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
struct exynos_mic {int enabled; int /*<<< orphan*/  dev; int /*<<< orphan*/  i80_mode; } ;
struct drm_bridge {struct exynos_mic* driver_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mic_mutex ; 
 int /*<<< orphan*/  mic_set_img_size (struct exynos_mic*) ; 
 int /*<<< orphan*/  mic_set_output_timing (struct exynos_mic*) ; 
 int /*<<< orphan*/  mic_set_path (struct exynos_mic*,int) ; 
 int /*<<< orphan*/  mic_set_porch_timing (struct exynos_mic*) ; 
 int /*<<< orphan*/  mic_set_reg_on (struct exynos_mic*,int) ; 
 int mic_sw_reset (struct exynos_mic*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mic_pre_enable(struct drm_bridge *bridge)
{
	struct exynos_mic *mic = bridge->driver_private;
	int ret;

	mutex_lock(&mic_mutex);
	if (mic->enabled)
		goto unlock;

	ret = pm_runtime_get_sync(mic->dev);
	if (ret < 0)
		goto unlock;

	mic_set_path(mic, 1);

	ret = mic_sw_reset(mic);
	if (ret) {
		DRM_DEV_ERROR(mic->dev, "Failed to reset\n");
		goto turn_off;
	}

	if (!mic->i80_mode)
		mic_set_porch_timing(mic);
	mic_set_img_size(mic);
	mic_set_output_timing(mic);
	mic_set_reg_on(mic, 1);
	mic->enabled = 1;
	mutex_unlock(&mic_mutex);

	return;

turn_off:
	pm_runtime_put(mic->dev);
unlock:
	mutex_unlock(&mic_mutex);
}