#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_10__ {int /*<<< orphan*/  regs; } ;
struct sun4i_backend {TYPE_5__ engine; } ;
struct drm_plane_state {int alpha; TYPE_3__* crtc; struct drm_framebuffer* fb; } ;
struct drm_plane {struct drm_plane_state* state; } ;
struct drm_framebuffer {TYPE_4__* format; } ;
struct TYPE_9__ {int /*<<< orphan*/  format; scalar_t__ is_yuv; } ;
struct TYPE_8__ {TYPE_2__* state; } ;
struct TYPE_6__ {int flags; } ;
struct TYPE_7__ {TYPE_1__ adjusted_mode; } ;

/* Variables and functions */
 int DRM_BLEND_ALPHA_OPAQUE ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,...) ; 
 int DRM_MODE_FLAG_INTERLACE ; 
 int /*<<< orphan*/  SUN4I_BACKEND_ATTCTL_REG0 (int) ; 
 int SUN4I_BACKEND_ATTCTL_REG0_LAY_GLBALPHA (int) ; 
 int SUN4I_BACKEND_ATTCTL_REG0_LAY_GLBALPHA_EN ; 
 int SUN4I_BACKEND_ATTCTL_REG0_LAY_GLBALPHA_MASK ; 
 int SUN4I_BACKEND_ATTCTL_REG0_LAY_YUVEN ; 
 int /*<<< orphan*/  SUN4I_BACKEND_ATTCTL_REG1 (int) ; 
 int SUN4I_BACKEND_ATTCTL_REG1_LAY_FBFMT ; 
 int SUN4I_BACKEND_MODCTL_ITLMOD_EN ; 
 int /*<<< orphan*/  SUN4I_BACKEND_MODCTL_REG ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int sun4i_backend_drm_format_to_layer (int /*<<< orphan*/ ,int*) ; 
 int sun4i_backend_update_yuv_format (struct sun4i_backend*,int,struct drm_plane*) ; 

int sun4i_backend_update_layer_formats(struct sun4i_backend *backend,
				       int layer, struct drm_plane *plane)
{
	struct drm_plane_state *state = plane->state;
	struct drm_framebuffer *fb = state->fb;
	bool interlaced = false;
	u32 val;
	int ret;

	/* Clear the YUV mode */
	regmap_update_bits(backend->engine.regs, SUN4I_BACKEND_ATTCTL_REG0(layer),
			   SUN4I_BACKEND_ATTCTL_REG0_LAY_YUVEN, 0);

	if (plane->state->crtc)
		interlaced = plane->state->crtc->state->adjusted_mode.flags
			& DRM_MODE_FLAG_INTERLACE;

	regmap_update_bits(backend->engine.regs, SUN4I_BACKEND_MODCTL_REG,
			   SUN4I_BACKEND_MODCTL_ITLMOD_EN,
			   interlaced ? SUN4I_BACKEND_MODCTL_ITLMOD_EN : 0);

	DRM_DEBUG_DRIVER("Switching display backend interlaced mode %s\n",
			 interlaced ? "on" : "off");

	val = SUN4I_BACKEND_ATTCTL_REG0_LAY_GLBALPHA(state->alpha >> 8);
	if (state->alpha != DRM_BLEND_ALPHA_OPAQUE)
		val |= SUN4I_BACKEND_ATTCTL_REG0_LAY_GLBALPHA_EN;
	regmap_update_bits(backend->engine.regs,
			   SUN4I_BACKEND_ATTCTL_REG0(layer),
			   SUN4I_BACKEND_ATTCTL_REG0_LAY_GLBALPHA_MASK |
			   SUN4I_BACKEND_ATTCTL_REG0_LAY_GLBALPHA_EN,
			   val);

	if (fb->format->is_yuv)
		return sun4i_backend_update_yuv_format(backend, layer, plane);

	ret = sun4i_backend_drm_format_to_layer(fb->format->format, &val);
	if (ret) {
		DRM_DEBUG_DRIVER("Invalid format\n");
		return ret;
	}

	regmap_update_bits(backend->engine.regs,
			   SUN4I_BACKEND_ATTCTL_REG1(layer),
			   SUN4I_BACKEND_ATTCTL_REG1_LAY_FBFMT, val);

	return 0;
}