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
struct TYPE_2__ {int /*<<< orphan*/  regs; } ;
struct sun4i_backend {TYPE_1__ engine; } ;
struct drm_plane_state {int /*<<< orphan*/  crtc_y; int /*<<< orphan*/  crtc_x; int /*<<< orphan*/  crtc_h; int /*<<< orphan*/  crtc_w; } ;
struct drm_plane {scalar_t__ type; struct drm_plane_state* state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int,...) ; 
 scalar_t__ DRM_PLANE_TYPE_PRIMARY ; 
 int /*<<< orphan*/  SUN4I_BACKEND_DISSIZE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUN4I_BACKEND_DISSIZE_REG ; 
 int /*<<< orphan*/  SUN4I_BACKEND_LAYCOOR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUN4I_BACKEND_LAYCOOR_REG (int) ; 
 int /*<<< orphan*/  SUN4I_BACKEND_LAYSIZE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUN4I_BACKEND_LAYSIZE_REG (int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int sun4i_backend_update_layer_coord(struct sun4i_backend *backend,
				     int layer, struct drm_plane *plane)
{
	struct drm_plane_state *state = plane->state;

	DRM_DEBUG_DRIVER("Updating layer %d\n", layer);

	if (plane->type == DRM_PLANE_TYPE_PRIMARY) {
		DRM_DEBUG_DRIVER("Primary layer, updating global size W: %u H: %u\n",
				 state->crtc_w, state->crtc_h);
		regmap_write(backend->engine.regs, SUN4I_BACKEND_DISSIZE_REG,
			     SUN4I_BACKEND_DISSIZE(state->crtc_w,
						   state->crtc_h));
	}

	/* Set height and width */
	DRM_DEBUG_DRIVER("Layer size W: %u H: %u\n",
			 state->crtc_w, state->crtc_h);
	regmap_write(backend->engine.regs, SUN4I_BACKEND_LAYSIZE_REG(layer),
		     SUN4I_BACKEND_LAYSIZE(state->crtc_w,
					   state->crtc_h));

	/* Set base coordinates */
	DRM_DEBUG_DRIVER("Layer coordinates X: %d Y: %d\n",
			 state->crtc_x, state->crtc_y);
	regmap_write(backend->engine.regs, SUN4I_BACKEND_LAYCOOR_REG(layer),
		     SUN4I_BACKEND_LAYCOOR(state->crtc_x,
					   state->crtc_y));

	return 0;
}