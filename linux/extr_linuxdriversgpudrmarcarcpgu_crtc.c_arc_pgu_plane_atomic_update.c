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
struct drm_plane_state {int dummy; } ;
struct drm_plane {TYPE_1__* state; } ;
struct drm_gem_cma_object {int /*<<< orphan*/  paddr; } ;
struct arcpgu_drm_private {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  fb; int /*<<< orphan*/  crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCPGU_REG_BUF0_ADDR ; 
 int /*<<< orphan*/  arc_pgu_write (struct arcpgu_drm_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct arcpgu_drm_private* crtc_to_arcpgu_priv (int /*<<< orphan*/ ) ; 
 struct drm_gem_cma_object* drm_fb_cma_get_gem_obj (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void arc_pgu_plane_atomic_update(struct drm_plane *plane,
					struct drm_plane_state *state)
{
	struct arcpgu_drm_private *arcpgu;
	struct drm_gem_cma_object *gem;

	if (!plane->state->crtc || !plane->state->fb)
		return;

	arcpgu = crtc_to_arcpgu_priv(plane->state->crtc);
	gem = drm_fb_cma_get_gem_obj(plane->state->fb, 0);
	arc_pgu_write(arcpgu, ARCPGU_REG_BUF0_ADDR, gem->paddr);
}