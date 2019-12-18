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
struct drm_plane_state {int dummy; } ;
struct drm_plane {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __drm_atomic_helper_plane_destroy_state (struct drm_plane_state*) ; 
 int /*<<< orphan*/  kfree (struct exynos_drm_plane_state*) ; 
 struct exynos_drm_plane_state* to_exynos_plane_state (struct drm_plane_state*) ; 

__attribute__((used)) static void exynos_drm_plane_destroy_state(struct drm_plane *plane,
					   struct drm_plane_state *old_state)
{
	struct exynos_drm_plane_state *old_exynos_state =
					to_exynos_plane_state(old_state);
	__drm_atomic_helper_plane_destroy_state(old_state);
	kfree(old_exynos_state);
}