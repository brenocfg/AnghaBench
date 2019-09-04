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
typedef  scalar_t__ uint32_t ;
struct skl_wm_params {int y_tiled; int x_tiled; int rc_surface; int is_planar; int width; int cpp; int dbuf_block_size; int y_min_scanlines; int plane_bytes_per_line; int /*<<< orphan*/  linetime_us; void* plane_blocks_per_line; int /*<<< orphan*/  y_tile_minimum; int /*<<< orphan*/  plane_pixel_rate; } ;
struct drm_plane_state {int crtc_w; int /*<<< orphan*/  rotation; int /*<<< orphan*/  src; struct drm_framebuffer* fb; int /*<<< orphan*/  plane; } ;
struct intel_plane_state {struct drm_plane_state base; } ;
struct intel_plane {scalar_t__ id; } ;
struct TYPE_3__ {int /*<<< orphan*/  state; } ;
struct intel_crtc_state {TYPE_1__ base; } ;
struct intel_atomic_state {int dummy; } ;
struct drm_i915_private {int dummy; } ;
struct drm_framebuffer {scalar_t__ modifier; TYPE_2__* format; } ;
struct TYPE_4__ {scalar_t__ format; int* cpp; } ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 scalar_t__ DRM_FORMAT_NV12 ; 
 int EINVAL ; 
 scalar_t__ I915_FORMAT_MOD_X_TILED ; 
 scalar_t__ I915_FORMAT_MOD_Y_TILED ; 
 scalar_t__ I915_FORMAT_MOD_Y_TILED_CCS ; 
 scalar_t__ I915_FORMAT_MOD_Yf_TILED ; 
 scalar_t__ I915_FORMAT_MOD_Yf_TILED_CCS ; 
 int INTEL_GEN (struct drm_i915_private const*) ; 
 scalar_t__ IS_GEN9 (struct drm_i915_private const*) ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 scalar_t__ PLANE_CURSOR ; 
 void* div_fixed16 (scalar_t__,int) ; 
 int drm_rect_width (int /*<<< orphan*/ *) ; 
 scalar_t__ drm_rotation_90_or_270 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fixed16_to_u32_round_up (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_get_linetime_us (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_wm_plane_visible (struct intel_crtc_state*,struct intel_plane_state const*) ; 
 int /*<<< orphan*/  mul_u32_fixed16 (int,void*) ; 
 int /*<<< orphan*/  skl_adjusted_plane_pixel_rate (struct intel_crtc_state*,struct intel_plane_state const*) ; 
 int skl_needs_memory_bw_wa (struct intel_atomic_state*) ; 
 struct intel_atomic_state* to_intel_atomic_state (int /*<<< orphan*/ ) ; 
 struct intel_plane* to_intel_plane (int /*<<< orphan*/ ) ; 
 void* u32_to_fixed16 (scalar_t__) ; 

__attribute__((used)) static int
skl_compute_plane_wm_params(const struct drm_i915_private *dev_priv,
			    struct intel_crtc_state *cstate,
			    const struct intel_plane_state *intel_pstate,
			    struct skl_wm_params *wp, int plane_id)
{
	struct intel_plane *plane = to_intel_plane(intel_pstate->base.plane);
	const struct drm_plane_state *pstate = &intel_pstate->base;
	const struct drm_framebuffer *fb = pstate->fb;
	uint32_t interm_pbpl;
	struct intel_atomic_state *state =
		to_intel_atomic_state(cstate->base.state);
	bool apply_memory_bw_wa = skl_needs_memory_bw_wa(state);

	if (!intel_wm_plane_visible(cstate, intel_pstate))
		return 0;

	/* only NV12 format has two planes */
	if (plane_id == 1 && fb->format->format != DRM_FORMAT_NV12) {
		DRM_DEBUG_KMS("Non NV12 format have single plane\n");
		return -EINVAL;
	}

	wp->y_tiled = fb->modifier == I915_FORMAT_MOD_Y_TILED ||
		      fb->modifier == I915_FORMAT_MOD_Yf_TILED ||
		      fb->modifier == I915_FORMAT_MOD_Y_TILED_CCS ||
		      fb->modifier == I915_FORMAT_MOD_Yf_TILED_CCS;
	wp->x_tiled = fb->modifier == I915_FORMAT_MOD_X_TILED;
	wp->rc_surface = fb->modifier == I915_FORMAT_MOD_Y_TILED_CCS ||
			 fb->modifier == I915_FORMAT_MOD_Yf_TILED_CCS;
	wp->is_planar = fb->format->format == DRM_FORMAT_NV12;

	if (plane->id == PLANE_CURSOR) {
		wp->width = intel_pstate->base.crtc_w;
	} else {
		/*
		 * Src coordinates are already rotated by 270 degrees for
		 * the 90/270 degree plane rotation cases (to match the
		 * GTT mapping), hence no need to account for rotation here.
		 */
		wp->width = drm_rect_width(&intel_pstate->base.src) >> 16;
	}

	if (plane_id == 1 && wp->is_planar)
		wp->width /= 2;

	wp->cpp = fb->format->cpp[plane_id];
	wp->plane_pixel_rate = skl_adjusted_plane_pixel_rate(cstate,
							     intel_pstate);

	if (INTEL_GEN(dev_priv) >= 11 &&
	    fb->modifier == I915_FORMAT_MOD_Yf_TILED && wp->cpp == 8)
		wp->dbuf_block_size = 256;
	else
		wp->dbuf_block_size = 512;

	if (drm_rotation_90_or_270(pstate->rotation)) {

		switch (wp->cpp) {
		case 1:
			wp->y_min_scanlines = 16;
			break;
		case 2:
			wp->y_min_scanlines = 8;
			break;
		case 4:
			wp->y_min_scanlines = 4;
			break;
		default:
			MISSING_CASE(wp->cpp);
			return -EINVAL;
		}
	} else {
		wp->y_min_scanlines = 4;
	}

	if (apply_memory_bw_wa)
		wp->y_min_scanlines *= 2;

	wp->plane_bytes_per_line = wp->width * wp->cpp;
	if (wp->y_tiled) {
		interm_pbpl = DIV_ROUND_UP(wp->plane_bytes_per_line *
					   wp->y_min_scanlines,
					   wp->dbuf_block_size);

		if (INTEL_GEN(dev_priv) >= 10)
			interm_pbpl++;

		wp->plane_blocks_per_line = div_fixed16(interm_pbpl,
							wp->y_min_scanlines);
	} else if (wp->x_tiled && IS_GEN9(dev_priv)) {
		interm_pbpl = DIV_ROUND_UP(wp->plane_bytes_per_line,
					   wp->dbuf_block_size);
		wp->plane_blocks_per_line = u32_to_fixed16(interm_pbpl);
	} else {
		interm_pbpl = DIV_ROUND_UP(wp->plane_bytes_per_line,
					   wp->dbuf_block_size) + 1;
		wp->plane_blocks_per_line = u32_to_fixed16(interm_pbpl);
	}

	wp->y_tile_minimum = mul_u32_fixed16(wp->y_min_scanlines,
					     wp->plane_blocks_per_line);
	wp->linetime_us = fixed16_to_u32_round_up(
					intel_get_linetime_us(cstate));

	return 0;
}