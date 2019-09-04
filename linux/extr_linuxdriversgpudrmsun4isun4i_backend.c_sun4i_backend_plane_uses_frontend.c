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
struct sun4i_layer {struct sun4i_backend* backend; } ;
struct sun4i_backend {int /*<<< orphan*/  frontend; } ;
struct drm_plane_state {int /*<<< orphan*/  plane; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 struct sun4i_layer* plane_to_sun4i_layer (int /*<<< orphan*/ ) ; 
 int sun4i_backend_plane_uses_scaler (struct drm_plane_state*) ; 

__attribute__((used)) static bool sun4i_backend_plane_uses_frontend(struct drm_plane_state *state)
{
	struct sun4i_layer *layer = plane_to_sun4i_layer(state->plane);
	struct sun4i_backend *backend = layer->backend;

	if (IS_ERR(backend->frontend))
		return false;

	return sun4i_backend_plane_uses_scaler(state);
}