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
struct sun4i_layer_state {scalar_t__ uses_frontend; } ;
struct sun4i_layer {int /*<<< orphan*/  id; struct sun4i_backend* backend; } ;
struct sun4i_backend {int frontend_teardown; int /*<<< orphan*/  frontend_lock; } ;
struct drm_plane_state {int dummy; } ;
struct drm_plane {int dummy; } ;

/* Variables and functions */
 struct sun4i_layer* plane_to_sun4i_layer (struct drm_plane*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct sun4i_layer_state* state_to_sun4i_layer_state (struct drm_plane_state*) ; 
 int /*<<< orphan*/  sun4i_backend_layer_enable (struct sun4i_backend*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sun4i_backend_layer_atomic_disable(struct drm_plane *plane,
					       struct drm_plane_state *old_state)
{
	struct sun4i_layer_state *layer_state = state_to_sun4i_layer_state(old_state);
	struct sun4i_layer *layer = plane_to_sun4i_layer(plane);
	struct sun4i_backend *backend = layer->backend;

	sun4i_backend_layer_enable(backend, layer->id, false);

	if (layer_state->uses_frontend) {
		unsigned long flags;

		spin_lock_irqsave(&backend->frontend_lock, flags);
		backend->frontend_teardown = true;
		spin_unlock_irqrestore(&backend->frontend_lock, flags);
	}
}