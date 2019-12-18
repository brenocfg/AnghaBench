#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct sun4i_layer {struct sun4i_backend* backend; } ;
struct sun4i_backend {int /*<<< orphan*/  frontend; } ;
struct drm_plane_state {TYPE_2__* fb; int /*<<< orphan*/  plane; } ;
struct TYPE_4__ {int /*<<< orphan*/  modifier; TYPE_1__* format; } ;
struct TYPE_3__ {int /*<<< orphan*/  format; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 struct sun4i_layer* plane_to_sun4i_layer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sun4i_backend_format_is_supported (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sun4i_backend_plane_uses_scaler (struct drm_plane_state*) ; 
 int /*<<< orphan*/  sun4i_frontend_format_is_supported (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool sun4i_backend_plane_uses_frontend(struct drm_plane_state *state)
{
	struct sun4i_layer *layer = plane_to_sun4i_layer(state->plane);
	struct sun4i_backend *backend = layer->backend;
	uint32_t format = state->fb->format->format;
	uint64_t modifier = state->fb->modifier;

	if (IS_ERR(backend->frontend))
		return false;

	if (!sun4i_frontend_format_is_supported(format, modifier))
		return false;

	if (!sun4i_backend_format_is_supported(format, modifier))
		return true;

	/*
	 * TODO: The backend alone allows 2x and 4x integer scaling, including
	 * support for an alpha component (which the frontend doesn't support).
	 * Use the backend directly instead of the frontend in this case, with
	 * another test to return false.
	 */

	if (sun4i_backend_plane_uses_scaler(state))
		return true;

	/*
	 * Here the format is supported by both the frontend and the backend
	 * and no frontend scaling is required, so use the backend directly.
	 */
	return false;
}