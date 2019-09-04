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
struct sun4i_frontend {int /*<<< orphan*/  regs; } ;
struct drm_plane_state {int crtc_w; int crtc_h; int src_h; int src_w; } ;
struct drm_plane {struct drm_plane_state* state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int,int) ; 
 int /*<<< orphan*/  SUN4I_FRONTEND_CH0_HORZFACT_REG ; 
 int /*<<< orphan*/  SUN4I_FRONTEND_CH0_INSIZE_REG ; 
 int /*<<< orphan*/  SUN4I_FRONTEND_CH0_OUTSIZE_REG ; 
 int /*<<< orphan*/  SUN4I_FRONTEND_CH0_VERTFACT_REG ; 
 int /*<<< orphan*/  SUN4I_FRONTEND_CH1_HORZFACT_REG ; 
 int /*<<< orphan*/  SUN4I_FRONTEND_CH1_INSIZE_REG ; 
 int /*<<< orphan*/  SUN4I_FRONTEND_CH1_OUTSIZE_REG ; 
 int /*<<< orphan*/  SUN4I_FRONTEND_CH1_VERTFACT_REG ; 
 int /*<<< orphan*/  SUN4I_FRONTEND_FRM_CTRL_REG ; 
 int /*<<< orphan*/  SUN4I_FRONTEND_FRM_CTRL_REG_RDY ; 
 int SUN4I_FRONTEND_INSIZE (int,int) ; 
 int SUN4I_FRONTEND_OUTSIZE (int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_write_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sun4i_frontend_update_coord(struct sun4i_frontend *frontend,
				 struct drm_plane *plane)
{
	struct drm_plane_state *state = plane->state;

	/* Set height and width */
	DRM_DEBUG_DRIVER("Frontend size W: %u H: %u\n",
			 state->crtc_w, state->crtc_h);
	regmap_write(frontend->regs, SUN4I_FRONTEND_CH0_INSIZE_REG,
		     SUN4I_FRONTEND_INSIZE(state->src_h >> 16,
					   state->src_w >> 16));
	regmap_write(frontend->regs, SUN4I_FRONTEND_CH1_INSIZE_REG,
		     SUN4I_FRONTEND_INSIZE(state->src_h >> 16,
					   state->src_w >> 16));

	regmap_write(frontend->regs, SUN4I_FRONTEND_CH0_OUTSIZE_REG,
		     SUN4I_FRONTEND_OUTSIZE(state->crtc_h, state->crtc_w));
	regmap_write(frontend->regs, SUN4I_FRONTEND_CH1_OUTSIZE_REG,
		     SUN4I_FRONTEND_OUTSIZE(state->crtc_h, state->crtc_w));

	regmap_write(frontend->regs, SUN4I_FRONTEND_CH0_HORZFACT_REG,
		     state->src_w / state->crtc_w);
	regmap_write(frontend->regs, SUN4I_FRONTEND_CH1_HORZFACT_REG,
		     state->src_w / state->crtc_w);

	regmap_write(frontend->regs, SUN4I_FRONTEND_CH0_VERTFACT_REG,
		     state->src_h / state->crtc_h);
	regmap_write(frontend->regs, SUN4I_FRONTEND_CH1_VERTFACT_REG,
		     state->src_h / state->crtc_h);

	regmap_write_bits(frontend->regs, SUN4I_FRONTEND_FRM_CTRL_REG,
			  SUN4I_FRONTEND_FRM_CTRL_REG_RDY,
			  SUN4I_FRONTEND_FRM_CTRL_REG_RDY);
}