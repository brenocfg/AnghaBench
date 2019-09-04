#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sti_plane {int dummy; } ;
struct sti_mixer {scalar_t__ id; } ;
struct sti_gdp {scalar_t__ clk_pix; struct clk* clk_aux_parent; struct clk* clk_main_parent; } ;
struct drm_plane_state {int crtc_x; int crtc_y; int crtc_w; int crtc_h; int src_x; int src_y; int src_w; int src_h; int /*<<< orphan*/  state; struct drm_framebuffer* fb; struct drm_crtc* crtc; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct drm_plane {TYPE_3__ base; } ;
struct drm_framebuffer {TYPE_1__* format; } ;
struct drm_display_mode {int clock; scalar_t__ vdisplay; scalar_t__ hdisplay; } ;
struct drm_crtc_state {struct drm_display_mode mode; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct drm_crtc {TYPE_2__ base; } ;
struct clk {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int,int,int,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EINVAL ; 
 scalar_t__ GAM_GDP_SIZE_MAX_HEIGHT ; 
 scalar_t__ GAM_GDP_SIZE_MAX_WIDTH ; 
 scalar_t__ STI_MIXER_MAIN ; 
 int clamp_val (int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  clk_set_parent (scalar_t__,struct clk*) ; 
 int clk_set_rate (scalar_t__,int) ; 
 struct drm_crtc_state* drm_atomic_get_crtc_state (int /*<<< orphan*/ ,struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_fb_cma_get_gem_obj (struct drm_framebuffer*,int /*<<< orphan*/ ) ; 
 int sti_gdp_fourcc2format (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sti_mixer_to_str (struct sti_mixer*) ; 
 int /*<<< orphan*/  sti_plane_to_str (struct sti_plane*) ; 
 struct sti_gdp* to_sti_gdp (struct sti_plane*) ; 
 struct sti_mixer* to_sti_mixer (struct drm_crtc*) ; 
 struct sti_plane* to_sti_plane (struct drm_plane*) ; 

__attribute__((used)) static int sti_gdp_atomic_check(struct drm_plane *drm_plane,
				struct drm_plane_state *state)
{
	struct sti_plane *plane = to_sti_plane(drm_plane);
	struct sti_gdp *gdp = to_sti_gdp(plane);
	struct drm_crtc *crtc = state->crtc;
	struct drm_framebuffer *fb =  state->fb;
	struct drm_crtc_state *crtc_state;
	struct sti_mixer *mixer;
	struct drm_display_mode *mode;
	int dst_x, dst_y, dst_w, dst_h;
	int src_x, src_y, src_w, src_h;
	int format;

	/* no need for further checks if the plane is being disabled */
	if (!crtc || !fb)
		return 0;

	mixer = to_sti_mixer(crtc);
	crtc_state = drm_atomic_get_crtc_state(state->state, crtc);
	mode = &crtc_state->mode;
	dst_x = state->crtc_x;
	dst_y = state->crtc_y;
	dst_w = clamp_val(state->crtc_w, 0, mode->hdisplay - dst_x);
	dst_h = clamp_val(state->crtc_h, 0, mode->vdisplay - dst_y);
	/* src_x are in 16.16 format */
	src_x = state->src_x >> 16;
	src_y = state->src_y >> 16;
	src_w = clamp_val(state->src_w >> 16, 0, GAM_GDP_SIZE_MAX_WIDTH);
	src_h = clamp_val(state->src_h >> 16, 0, GAM_GDP_SIZE_MAX_HEIGHT);

	format = sti_gdp_fourcc2format(fb->format->format);
	if (format == -1) {
		DRM_ERROR("Format not supported by GDP %.4s\n",
			  (char *)&fb->format->format);
		return -EINVAL;
	}

	if (!drm_fb_cma_get_gem_obj(fb, 0)) {
		DRM_ERROR("Can't get CMA GEM object for fb\n");
		return -EINVAL;
	}

	/* Set gdp clock */
	if (mode->clock && gdp->clk_pix) {
		struct clk *clkp;
		int rate = mode->clock * 1000;
		int res;

		/*
		 * According to the mixer used, the gdp pixel clock
		 * should have a different parent clock.
		 */
		if (mixer->id == STI_MIXER_MAIN)
			clkp = gdp->clk_main_parent;
		else
			clkp = gdp->clk_aux_parent;

		if (clkp)
			clk_set_parent(gdp->clk_pix, clkp);

		res = clk_set_rate(gdp->clk_pix, rate);
		if (res < 0) {
			DRM_ERROR("Cannot set rate (%dHz) for gdp\n",
				  rate);
			return -EINVAL;
		}
	}

	DRM_DEBUG_KMS("CRTC:%d (%s) drm plane:%d (%s)\n",
		      crtc->base.id, sti_mixer_to_str(mixer),
		      drm_plane->base.id, sti_plane_to_str(plane));
	DRM_DEBUG_KMS("%s dst=(%dx%d)@(%d,%d) - src=(%dx%d)@(%d,%d)\n",
		      sti_plane_to_str(plane),
		      dst_w, dst_h, dst_x, dst_y,
		      src_w, src_h, src_x, src_y);

	return 0;
}