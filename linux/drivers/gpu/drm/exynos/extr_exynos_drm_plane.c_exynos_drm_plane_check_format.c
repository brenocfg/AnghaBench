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
struct TYPE_2__ {struct drm_framebuffer* fb; } ;
struct exynos_drm_plane_state {TYPE_1__ base; } ;
struct exynos_drm_plane_config {int capabilities; } ;
struct drm_framebuffer {int modifier; struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*) ; 
#define  DRM_FORMAT_MOD_LINEAR 129 
#define  DRM_FORMAT_MOD_SAMSUNG_64_32_TILE 128 
 int ENOTSUPP ; 
 int EXYNOS_DRM_PLANE_CAP_TILE ; 

__attribute__((used)) static int
exynos_drm_plane_check_format(const struct exynos_drm_plane_config *config,
			      struct exynos_drm_plane_state *state)
{
	struct drm_framebuffer *fb = state->base.fb;
	struct drm_device *dev = fb->dev;

	switch (fb->modifier) {
	case DRM_FORMAT_MOD_SAMSUNG_64_32_TILE:
		if (!(config->capabilities & EXYNOS_DRM_PLANE_CAP_TILE))
			return -ENOTSUPP;
		break;

	case DRM_FORMAT_MOD_LINEAR:
		break;

	default:
		DRM_DEV_ERROR(dev->dev, "unsupported pixel format modifier");
		return -ENOTSUPP;
	}

	return 0;
}