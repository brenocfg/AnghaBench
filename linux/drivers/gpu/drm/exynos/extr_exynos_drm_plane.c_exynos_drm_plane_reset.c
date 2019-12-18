#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct exynos_drm_plane_state {int /*<<< orphan*/  base; } ;
struct exynos_drm_plane {TYPE_1__* config; } ;
struct drm_plane {TYPE_2__* state; } ;
struct TYPE_5__ {int /*<<< orphan*/  zpos; } ;
struct TYPE_4__ {int /*<<< orphan*/  zpos; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __drm_atomic_helper_plane_destroy_state (TYPE_2__*) ; 
 int /*<<< orphan*/  __drm_atomic_helper_plane_reset (struct drm_plane*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct exynos_drm_plane_state*) ; 
 struct exynos_drm_plane_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct exynos_drm_plane* to_exynos_plane (struct drm_plane*) ; 
 struct exynos_drm_plane_state* to_exynos_plane_state (TYPE_2__*) ; 

__attribute__((used)) static void exynos_drm_plane_reset(struct drm_plane *plane)
{
	struct exynos_drm_plane *exynos_plane = to_exynos_plane(plane);
	struct exynos_drm_plane_state *exynos_state;

	if (plane->state) {
		exynos_state = to_exynos_plane_state(plane->state);
		__drm_atomic_helper_plane_destroy_state(plane->state);
		kfree(exynos_state);
		plane->state = NULL;
	}

	exynos_state = kzalloc(sizeof(*exynos_state), GFP_KERNEL);
	if (exynos_state) {
		__drm_atomic_helper_plane_reset(plane, &exynos_state->base);
		plane->state->zpos = exynos_plane->config->zpos;
	}
}