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
struct drm_plane {int dummy; } ;
struct exynos_drm_plane {unsigned int index; struct drm_plane base; struct exynos_drm_plane_config const* config; } ;
struct TYPE_2__ {int num_crtc; } ;
struct drm_device {int /*<<< orphan*/  dev; TYPE_1__ mode_config; } ;

/* Variables and functions */
 unsigned int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DRM_MODE_BLEND_COVERAGE ; 
 int /*<<< orphan*/  DRM_MODE_BLEND_PIXEL_NONE ; 
 int /*<<< orphan*/  DRM_MODE_BLEND_PREMULTI ; 
 int EXYNOS_DRM_PLANE_CAP_PIX_BLEND ; 
 int EXYNOS_DRM_PLANE_CAP_WIN_BLEND ; 
 int EXYNOS_DRM_PLANE_CAP_ZPOS ; 
 int /*<<< orphan*/  drm_plane_create_alpha_property (struct drm_plane*) ; 
 int /*<<< orphan*/  drm_plane_create_blend_mode_property (struct drm_plane*,unsigned int) ; 
 int /*<<< orphan*/  drm_plane_helper_add (struct drm_plane*,int /*<<< orphan*/ *) ; 
 int drm_universal_plane_init (struct drm_device*,struct drm_plane*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exynos_plane_attach_zpos_property (struct drm_plane*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  exynos_plane_funcs ; 
 int /*<<< orphan*/  plane_helper_funcs ; 

int exynos_plane_init(struct drm_device *dev,
		      struct exynos_drm_plane *exynos_plane, unsigned int index,
		      const struct exynos_drm_plane_config *config)
{
	int err;
	unsigned int supported_modes = BIT(DRM_MODE_BLEND_PIXEL_NONE) |
				       BIT(DRM_MODE_BLEND_PREMULTI) |
				       BIT(DRM_MODE_BLEND_COVERAGE);
	struct drm_plane *plane = &exynos_plane->base;

	err = drm_universal_plane_init(dev, &exynos_plane->base,
				       1 << dev->mode_config.num_crtc,
				       &exynos_plane_funcs,
				       config->pixel_formats,
				       config->num_pixel_formats,
				       NULL, config->type, NULL);
	if (err) {
		DRM_DEV_ERROR(dev->dev, "failed to initialize plane\n");
		return err;
	}

	drm_plane_helper_add(&exynos_plane->base, &plane_helper_funcs);

	exynos_plane->index = index;
	exynos_plane->config = config;

	exynos_plane_attach_zpos_property(&exynos_plane->base, config->zpos,
			   !(config->capabilities & EXYNOS_DRM_PLANE_CAP_ZPOS));

	if (config->capabilities & EXYNOS_DRM_PLANE_CAP_PIX_BLEND)
		drm_plane_create_blend_mode_property(plane, supported_modes);

	if (config->capabilities & EXYNOS_DRM_PLANE_CAP_WIN_BLEND)
		drm_plane_create_alpha_property(plane);

	return 0;
}