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
struct drm_plane_state {int /*<<< orphan*/  pixel_blend_mode; int /*<<< orphan*/  alpha; int /*<<< orphan*/  rotation; struct drm_plane* plane; } ;
struct drm_plane {struct drm_plane_state* state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_BLEND_ALPHA_OPAQUE ; 
 int /*<<< orphan*/  DRM_MODE_BLEND_PREMULTI ; 
 int /*<<< orphan*/  DRM_MODE_ROTATE_0 ; 

void __drm_atomic_helper_plane_reset(struct drm_plane *plane,
				     struct drm_plane_state *state)
{
	state->plane = plane;
	state->rotation = DRM_MODE_ROTATE_0;

	state->alpha = DRM_BLEND_ALPHA_OPAQUE;
	state->pixel_blend_mode = DRM_MODE_BLEND_PREMULTI;

	plane->state = state;
}