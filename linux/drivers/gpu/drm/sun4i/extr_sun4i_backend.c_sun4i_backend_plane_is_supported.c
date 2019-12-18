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
struct drm_plane_state {int dummy; } ;

/* Variables and functions */
 scalar_t__ sun4i_backend_plane_uses_frontend (struct drm_plane_state*) ; 
 scalar_t__ sun4i_backend_plane_uses_scaler (struct drm_plane_state*) ; 

__attribute__((used)) static bool sun4i_backend_plane_is_supported(struct drm_plane_state *state,
					     bool *uses_frontend)
{
	if (sun4i_backend_plane_uses_frontend(state)) {
		*uses_frontend = true;
		return true;
	}

	*uses_frontend = false;

	/* Scaling is not supported without the frontend. */
	if (sun4i_backend_plane_uses_scaler(state))
		return false;

	return true;
}