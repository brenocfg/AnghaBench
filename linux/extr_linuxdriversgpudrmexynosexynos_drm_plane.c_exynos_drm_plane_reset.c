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
struct TYPE_4__ {int /*<<< orphan*/  zpos; struct drm_plane* plane; scalar_t__ fb; } ;
struct exynos_drm_plane_state {TYPE_2__ base; } ;
struct exynos_drm_plane {TYPE_1__* config; } ;
struct drm_plane {TYPE_2__* state; } ;
struct TYPE_3__ {int /*<<< orphan*/  zpos; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_framebuffer_put (scalar_t__) ; 
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
		if (exynos_state->base.fb)
			drm_framebuffer_put(exynos_state->base.fb);
		kfree(exynos_state);
		plane->state = NULL;
	}

	exynos_state = kzalloc(sizeof(*exynos_state), GFP_KERNEL);
	if (exynos_state) {
		plane->state = &exynos_state->base;
		plane->state->plane = plane;
		plane->state->zpos = exynos_plane->config->zpos;
	}
}