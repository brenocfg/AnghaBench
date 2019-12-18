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
struct tegra_drm {int /*<<< orphan*/  fbdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_connector; int /*<<< orphan*/  num_crtc; } ;
struct drm_device {TYPE_1__ mode_config; struct tegra_drm* dev_private; } ;

/* Variables and functions */
 int tegra_fbdev_init (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int tegra_drm_fb_init(struct drm_device *drm)
{
#ifdef CONFIG_DRM_FBDEV_EMULATION
	struct tegra_drm *tegra = drm->dev_private;
	int err;

	err = tegra_fbdev_init(tegra->fbdev, 32, drm->mode_config.num_crtc,
			       drm->mode_config.num_connector);
	if (err < 0)
		return err;
#endif

	return 0;
}