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
struct exynos_drm_plane_config {int capabilities; int /*<<< orphan*/  zpos; int /*<<< orphan*/  type; int /*<<< orphan*/  num_pixel_formats; int /*<<< orphan*/  pixel_formats; } ;
struct exynos_drm_plane {unsigned int index; int /*<<< orphan*/  base; struct exynos_drm_plane_config const* config; } ;
struct TYPE_2__ {int num_crtc; } ;
struct drm_device {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EXYNOS_DRM_PLANE_CAP_ZPOS ; 
 int /*<<< orphan*/  drm_plane_helper_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int drm_universal_plane_init (struct drm_device*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exynos_plane_attach_zpos_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  exynos_plane_funcs ; 
 int /*<<< orphan*/  plane_helper_funcs ; 

int exynos_plane_init(struct drm_device *dev,
		      struct exynos_drm_plane *exynos_plane, unsigned int index,
		      const struct exynos_drm_plane_config *config)
{
	int err;

	err = drm_universal_plane_init(dev, &exynos_plane->base,
				       1 << dev->mode_config.num_crtc,
				       &exynos_plane_funcs,
				       config->pixel_formats,
				       config->num_pixel_formats,
				       NULL, config->type, NULL);
	if (err) {
		DRM_ERROR("failed to initialize plane\n");
		return err;
	}

	drm_plane_helper_add(&exynos_plane->base, &plane_helper_funcs);

	exynos_plane->index = index;
	exynos_plane->config = config;

	exynos_plane_attach_zpos_property(&exynos_plane->base, config->zpos,
			   !(config->capabilities & EXYNOS_DRM_PLANE_CAP_ZPOS));

	return 0;
}