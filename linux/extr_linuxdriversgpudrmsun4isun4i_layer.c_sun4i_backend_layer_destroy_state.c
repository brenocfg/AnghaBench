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
struct sun4i_layer_state {int dummy; } ;
struct drm_plane_state {int dummy; } ;
struct drm_plane {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __drm_atomic_helper_plane_destroy_state (struct drm_plane_state*) ; 
 int /*<<< orphan*/  kfree (struct sun4i_layer_state*) ; 
 struct sun4i_layer_state* state_to_sun4i_layer_state (struct drm_plane_state*) ; 

__attribute__((used)) static void sun4i_backend_layer_destroy_state(struct drm_plane *plane,
					      struct drm_plane_state *state)
{
	struct sun4i_layer_state *s_state = state_to_sun4i_layer_state(state);

	__drm_atomic_helper_plane_destroy_state(state);

	kfree(s_state);
}