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
struct tegra_drm {int /*<<< orphan*/  fbdev; } ;
struct drm_device {struct tegra_drm* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  tegra_fbdev_free (int /*<<< orphan*/ ) ; 

void tegra_drm_fb_free(struct drm_device *drm)
{
#ifdef CONFIG_DRM_FBDEV_EMULATION
	struct tegra_drm *tegra = drm->dev_private;

	tegra_fbdev_free(tegra->fbdev);
#endif
}