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
struct omap_plane {int /*<<< orphan*/  id; } ;
struct drm_plane {scalar_t__ type; TYPE_1__* state; } ;
struct TYPE_2__ {int /*<<< orphan*/  zpos; } ;

/* Variables and functions */
 scalar_t__ DRM_PLANE_TYPE_PRIMARY ; 
 int /*<<< orphan*/  drm_atomic_helper_plane_reset (struct drm_plane*) ; 
 struct omap_plane* to_omap_plane (struct drm_plane*) ; 

__attribute__((used)) static void omap_plane_reset(struct drm_plane *plane)
{
	struct omap_plane *omap_plane = to_omap_plane(plane);

	drm_atomic_helper_plane_reset(plane);
	if (!plane->state)
		return;

	/*
	 * Set the zpos default depending on whether we are a primary or overlay
	 * plane.
	 */
	plane->state->zpos = plane->type == DRM_PLANE_TYPE_PRIMARY
			   ? 0 : omap_plane->id;
}