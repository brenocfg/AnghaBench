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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u32 ;
struct sun4i_frontend {int /*<<< orphan*/  regs; } ;
struct drm_plane_state {struct drm_framebuffer* fb; } ;
struct drm_plane {struct drm_plane_state* state; } ;
struct drm_framebuffer {TYPE_1__* format; } ;
struct TYPE_2__ {int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  SUN4I_FRONTEND_CH0_HORZPHASE_REG ; 
 int /*<<< orphan*/  SUN4I_FRONTEND_CH0_VERTPHASE0_REG ; 
 int /*<<< orphan*/  SUN4I_FRONTEND_CH0_VERTPHASE1_REG ; 
 int /*<<< orphan*/  SUN4I_FRONTEND_CH1_HORZPHASE_REG ; 
 int /*<<< orphan*/  SUN4I_FRONTEND_CH1_VERTPHASE0_REG ; 
 int /*<<< orphan*/  SUN4I_FRONTEND_CH1_VERTPHASE1_REG ; 
 int SUN4I_FRONTEND_INPUT_FMT_DATA_FMT (int /*<<< orphan*/ ) ; 
 int SUN4I_FRONTEND_INPUT_FMT_DATA_MOD (int) ; 
 int SUN4I_FRONTEND_INPUT_FMT_PS (int) ; 
 int /*<<< orphan*/  SUN4I_FRONTEND_INPUT_FMT_REG ; 
 int SUN4I_FRONTEND_OUTPUT_FMT_DATA_FMT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUN4I_FRONTEND_OUTPUT_FMT_REG ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int sun4i_frontend_drm_format_to_input_fmt (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sun4i_frontend_drm_format_to_output_fmt (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int sun4i_frontend_update_formats(struct sun4i_frontend *frontend,
				  struct drm_plane *plane, uint32_t out_fmt)
{
	struct drm_plane_state *state = plane->state;
	struct drm_framebuffer *fb = state->fb;
	u32 out_fmt_val;
	u32 in_fmt_val;
	int ret;

	ret = sun4i_frontend_drm_format_to_input_fmt(fb->format->format,
						     &in_fmt_val);
	if (ret) {
		DRM_DEBUG_DRIVER("Invalid input format\n");
		return ret;
	}

	ret = sun4i_frontend_drm_format_to_output_fmt(out_fmt, &out_fmt_val);
	if (ret) {
		DRM_DEBUG_DRIVER("Invalid output format\n");
		return ret;
	}

	/*
	 * I have no idea what this does exactly, but it seems to be
	 * related to the scaler FIR filter phase parameters.
	 */
	regmap_write(frontend->regs, SUN4I_FRONTEND_CH0_HORZPHASE_REG, 0x400);
	regmap_write(frontend->regs, SUN4I_FRONTEND_CH1_HORZPHASE_REG, 0x400);
	regmap_write(frontend->regs, SUN4I_FRONTEND_CH0_VERTPHASE0_REG, 0x400);
	regmap_write(frontend->regs, SUN4I_FRONTEND_CH1_VERTPHASE0_REG, 0x400);
	regmap_write(frontend->regs, SUN4I_FRONTEND_CH0_VERTPHASE1_REG, 0x400);
	regmap_write(frontend->regs, SUN4I_FRONTEND_CH1_VERTPHASE1_REG, 0x400);

	regmap_write(frontend->regs, SUN4I_FRONTEND_INPUT_FMT_REG,
		     SUN4I_FRONTEND_INPUT_FMT_DATA_MOD(1) |
		     SUN4I_FRONTEND_INPUT_FMT_DATA_FMT(in_fmt_val) |
		     SUN4I_FRONTEND_INPUT_FMT_PS(1));

	/*
	 * TODO: It look like the A31 and A80 at least will need the
	 * bit 7 (ALPHA_EN) enabled when using a format with alpha (so
	 * ARGB8888).
	 */
	regmap_write(frontend->regs, SUN4I_FRONTEND_OUTPUT_FMT_REG,
		     SUN4I_FRONTEND_OUTPUT_FMT_DATA_FMT(out_fmt_val));

	return 0;
}