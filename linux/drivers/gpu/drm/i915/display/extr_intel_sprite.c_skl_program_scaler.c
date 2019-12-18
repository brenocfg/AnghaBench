#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct intel_scaler {int mode; } ;
struct TYPE_15__ {int x1; int y1; } ;
struct TYPE_14__ {TYPE_4__* fb; TYPE_6__ dst; int /*<<< orphan*/  src; } ;
struct intel_plane_state {int scaler_id; TYPE_5__ base; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
struct intel_plane {int pipe; int /*<<< orphan*/  id; TYPE_1__ base; } ;
struct TYPE_11__ {struct intel_scaler* scalers; } ;
struct intel_crtc_state {TYPE_2__ scaler_state; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
struct TYPE_13__ {TYPE_3__* format; } ;
struct TYPE_12__ {int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE_FW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  INT_MAX ; 
 int PS_PLANE_SEL (int /*<<< orphan*/ ) ; 
 int PS_SCALER_EN ; 
 int PS_UV_RGB_PHASE (scalar_t__) ; 
 int PS_Y_PHASE (scalar_t__) ; 
 int /*<<< orphan*/  SKL_PS_CTRL (int,int) ; 
 int /*<<< orphan*/  SKL_PS_HPHASE (int,int) ; 
 int /*<<< orphan*/  SKL_PS_VPHASE (int,int) ; 
 int /*<<< orphan*/  SKL_PS_WIN_POS (int,int) ; 
 int /*<<< orphan*/  SKL_PS_WIN_SZ (int,int) ; 
 int drm_rect_calc_hscale (int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int drm_rect_calc_vscale (int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int drm_rect_height (TYPE_6__*) ; 
 int drm_rect_width (TYPE_6__*) ; 
 int /*<<< orphan*/  icl_is_hdr_plane (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_planar_yuv_format (int /*<<< orphan*/ ) ; 
 scalar_t__ skl_scaler_calc_phase (int,int,int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
skl_program_scaler(struct intel_plane *plane,
		   const struct intel_crtc_state *crtc_state,
		   const struct intel_plane_state *plane_state)
{
	struct drm_i915_private *dev_priv = to_i915(plane->base.dev);
	enum pipe pipe = plane->pipe;
	int scaler_id = plane_state->scaler_id;
	const struct intel_scaler *scaler =
		&crtc_state->scaler_state.scalers[scaler_id];
	int crtc_x = plane_state->base.dst.x1;
	int crtc_y = plane_state->base.dst.y1;
	u32 crtc_w = drm_rect_width(&plane_state->base.dst);
	u32 crtc_h = drm_rect_height(&plane_state->base.dst);
	u16 y_hphase, uv_rgb_hphase;
	u16 y_vphase, uv_rgb_vphase;
	int hscale, vscale;

	hscale = drm_rect_calc_hscale(&plane_state->base.src,
				      &plane_state->base.dst,
				      0, INT_MAX);
	vscale = drm_rect_calc_vscale(&plane_state->base.src,
				      &plane_state->base.dst,
				      0, INT_MAX);

	/* TODO: handle sub-pixel coordinates */
	if (is_planar_yuv_format(plane_state->base.fb->format->format) &&
	    !icl_is_hdr_plane(dev_priv, plane->id)) {
		y_hphase = skl_scaler_calc_phase(1, hscale, false);
		y_vphase = skl_scaler_calc_phase(1, vscale, false);

		/* MPEG2 chroma siting convention */
		uv_rgb_hphase = skl_scaler_calc_phase(2, hscale, true);
		uv_rgb_vphase = skl_scaler_calc_phase(2, vscale, false);
	} else {
		/* not used */
		y_hphase = 0;
		y_vphase = 0;

		uv_rgb_hphase = skl_scaler_calc_phase(1, hscale, false);
		uv_rgb_vphase = skl_scaler_calc_phase(1, vscale, false);
	}

	I915_WRITE_FW(SKL_PS_CTRL(pipe, scaler_id),
		      PS_SCALER_EN | PS_PLANE_SEL(plane->id) | scaler->mode);
	I915_WRITE_FW(SKL_PS_VPHASE(pipe, scaler_id),
		      PS_Y_PHASE(y_vphase) | PS_UV_RGB_PHASE(uv_rgb_vphase));
	I915_WRITE_FW(SKL_PS_HPHASE(pipe, scaler_id),
		      PS_Y_PHASE(y_hphase) | PS_UV_RGB_PHASE(uv_rgb_hphase));
	I915_WRITE_FW(SKL_PS_WIN_POS(pipe, scaler_id), (crtc_x << 16) | crtc_y);
	I915_WRITE_FW(SKL_PS_WIN_SZ(pipe, scaler_id), (crtc_w << 16) | crtc_h);
}