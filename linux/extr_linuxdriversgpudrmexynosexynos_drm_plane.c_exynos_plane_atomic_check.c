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
struct exynos_drm_plane_state {int dummy; } ;
struct exynos_drm_plane {int /*<<< orphan*/  config; } ;
struct drm_plane_state {int /*<<< orphan*/  fb; int /*<<< orphan*/  crtc; } ;
struct drm_plane {int dummy; } ;

/* Variables and functions */
 int exynos_drm_plane_check_format (int /*<<< orphan*/ ,struct exynos_drm_plane_state*) ; 
 int exynos_drm_plane_check_size (int /*<<< orphan*/ ,struct exynos_drm_plane_state*) ; 
 int /*<<< orphan*/  exynos_plane_mode_set (struct exynos_drm_plane_state*) ; 
 struct exynos_drm_plane* to_exynos_plane (struct drm_plane*) ; 
 struct exynos_drm_plane_state* to_exynos_plane_state (struct drm_plane_state*) ; 

__attribute__((used)) static int exynos_plane_atomic_check(struct drm_plane *plane,
				     struct drm_plane_state *state)
{
	struct exynos_drm_plane *exynos_plane = to_exynos_plane(plane);
	struct exynos_drm_plane_state *exynos_state =
						to_exynos_plane_state(state);
	int ret = 0;

	if (!state->crtc || !state->fb)
		return 0;

	/* translate state into exynos_state */
	exynos_plane_mode_set(exynos_state);

	ret = exynos_drm_plane_check_format(exynos_plane->config, exynos_state);
	if (ret)
		return ret;

	ret = exynos_drm_plane_check_size(exynos_plane->config, exynos_state);
	return ret;
}