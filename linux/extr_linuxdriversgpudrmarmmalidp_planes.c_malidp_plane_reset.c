#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  rotation; struct drm_plane* plane; } ;
struct malidp_plane_state {TYPE_1__ base; } ;
struct drm_plane {TYPE_1__* state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_ROTATE_0 ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __drm_atomic_helper_plane_destroy_state (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct malidp_plane_state*) ; 
 struct malidp_plane_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct malidp_plane_state* to_malidp_plane_state (TYPE_1__*) ; 

__attribute__((used)) static void malidp_plane_reset(struct drm_plane *plane)
{
	struct malidp_plane_state *state = to_malidp_plane_state(plane->state);

	if (state)
		__drm_atomic_helper_plane_destroy_state(&state->base);
	kfree(state);
	plane->state = NULL;
	state = kzalloc(sizeof(*state), GFP_KERNEL);
	if (state) {
		state->base.plane = plane;
		state->base.rotation = DRM_MODE_ROTATE_0;
		plane->state = &state->base;
	}
}