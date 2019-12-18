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
struct sun4i_layer_state {int /*<<< orphan*/  state; } ;
struct sun4i_layer {int /*<<< orphan*/  id; } ;
struct drm_plane {TYPE_1__* state; } ;
struct TYPE_2__ {int /*<<< orphan*/  zpos; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __drm_atomic_helper_plane_destroy_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __drm_atomic_helper_plane_reset (struct drm_plane*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct sun4i_layer_state*) ; 
 struct sun4i_layer_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct sun4i_layer* plane_to_sun4i_layer (struct drm_plane*) ; 
 struct sun4i_layer_state* state_to_sun4i_layer_state (TYPE_1__*) ; 

__attribute__((used)) static void sun4i_backend_layer_reset(struct drm_plane *plane)
{
	struct sun4i_layer *layer = plane_to_sun4i_layer(plane);
	struct sun4i_layer_state *state;

	if (plane->state) {
		state = state_to_sun4i_layer_state(plane->state);

		__drm_atomic_helper_plane_destroy_state(&state->state);

		kfree(state);
		plane->state = NULL;
	}

	state = kzalloc(sizeof(*state), GFP_KERNEL);
	if (state) {
		__drm_atomic_helper_plane_reset(plane, &state->state);
		plane->state->zpos = layer->id;
	}
}