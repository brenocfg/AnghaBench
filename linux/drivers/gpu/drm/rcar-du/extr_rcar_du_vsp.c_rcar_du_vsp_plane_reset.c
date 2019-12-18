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
struct TYPE_2__ {int zpos; } ;
struct rcar_du_vsp_plane_state {TYPE_1__ state; } ;
struct drm_plane {scalar_t__ type; int /*<<< orphan*/ * state; } ;

/* Variables and functions */
 scalar_t__ DRM_PLANE_TYPE_PRIMARY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __drm_atomic_helper_plane_reset (struct drm_plane*,TYPE_1__*) ; 
 struct rcar_du_vsp_plane_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_du_vsp_plane_atomic_destroy_state (struct drm_plane*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rcar_du_vsp_plane_reset(struct drm_plane *plane)
{
	struct rcar_du_vsp_plane_state *state;

	if (plane->state) {
		rcar_du_vsp_plane_atomic_destroy_state(plane, plane->state);
		plane->state = NULL;
	}

	state = kzalloc(sizeof(*state), GFP_KERNEL);
	if (state == NULL)
		return;

	__drm_atomic_helper_plane_reset(plane, &state->state);
	state->state.zpos = plane->type == DRM_PLANE_TYPE_PRIMARY ? 0 : 1;
}