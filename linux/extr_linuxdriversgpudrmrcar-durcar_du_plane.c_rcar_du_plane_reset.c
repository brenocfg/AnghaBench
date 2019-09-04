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
struct TYPE_2__ {int zpos; struct drm_plane* plane; int /*<<< orphan*/  alpha; } ;
struct rcar_du_plane_state {int hwindex; TYPE_1__ state; int /*<<< orphan*/  colorkey; int /*<<< orphan*/  source; } ;
struct drm_plane {scalar_t__ type; TYPE_1__* state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_BLEND_ALPHA_OPAQUE ; 
 scalar_t__ DRM_PLANE_TYPE_PRIMARY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RCAR_DU_COLORKEY_NONE ; 
 int /*<<< orphan*/  RCAR_DU_PLANE_MEMORY ; 
 struct rcar_du_plane_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_du_plane_atomic_destroy_state (struct drm_plane*,TYPE_1__*) ; 

__attribute__((used)) static void rcar_du_plane_reset(struct drm_plane *plane)
{
	struct rcar_du_plane_state *state;

	if (plane->state) {
		rcar_du_plane_atomic_destroy_state(plane, plane->state);
		plane->state = NULL;
	}

	state = kzalloc(sizeof(*state), GFP_KERNEL);
	if (state == NULL)
		return;

	state->hwindex = -1;
	state->source = RCAR_DU_PLANE_MEMORY;
	state->colorkey = RCAR_DU_COLORKEY_NONE;
	state->state.zpos = plane->type == DRM_PLANE_TYPE_PRIMARY ? 0 : 1;

	plane->state = &state->state;
	plane->state->alpha = DRM_BLEND_ALPHA_OPAQUE;
	plane->state->plane = plane;
}