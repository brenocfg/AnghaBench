#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ w; scalar_t__ h; } ;
struct TYPE_3__ {scalar_t__ w; scalar_t__ h; } ;
struct exynos_drm_plane_state {int h_ratio; int v_ratio; TYPE_2__ crtc; TYPE_1__ src; } ;
struct exynos_drm_plane_config {int capabilities; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int ENOTSUPP ; 
 int EXYNOS_DRM_PLANE_CAP_DOUBLE ; 
 int EXYNOS_DRM_PLANE_CAP_SCALE ; 

__attribute__((used)) static int
exynos_drm_plane_check_size(const struct exynos_drm_plane_config *config,
			    struct exynos_drm_plane_state *state)
{
	bool width_ok = false, height_ok = false;

	if (config->capabilities & EXYNOS_DRM_PLANE_CAP_SCALE)
		return 0;

	if (state->src.w == state->crtc.w)
		width_ok = true;

	if (state->src.h == state->crtc.h)
		height_ok = true;

	if ((config->capabilities & EXYNOS_DRM_PLANE_CAP_DOUBLE) &&
	    state->h_ratio == (1 << 15))
		width_ok = true;

	if ((config->capabilities & EXYNOS_DRM_PLANE_CAP_DOUBLE) &&
	    state->v_ratio == (1 << 15))
		height_ok = true;

	if (width_ok && height_ok)
		return 0;

	DRM_DEBUG_KMS("scaling mode is not supported");
	return -ENOTSUPP;
}