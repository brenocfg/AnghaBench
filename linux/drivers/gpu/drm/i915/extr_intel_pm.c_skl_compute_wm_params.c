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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct skl_wm_params {int y_tiled; int x_tiled; int rc_surface; int width; int cpp; int dbuf_block_size; int y_min_scanlines; int plane_bytes_per_line; int /*<<< orphan*/  linetime_us; void* plane_blocks_per_line; int /*<<< orphan*/  y_tile_minimum; scalar_t__ plane_pixel_rate; scalar_t__ is_planar; } ;
struct TYPE_3__ {int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {TYPE_1__ base; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {TYPE_2__ base; } ;
struct drm_i915_private {int dummy; } ;
struct drm_format_info {int* cpp; int /*<<< orphan*/  format; } ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int EINVAL ; 
 scalar_t__ I915_FORMAT_MOD_X_TILED ; 
 scalar_t__ I915_FORMAT_MOD_Y_TILED ; 
 scalar_t__ I915_FORMAT_MOD_Y_TILED_CCS ; 
 scalar_t__ I915_FORMAT_MOD_Yf_TILED ; 
 scalar_t__ I915_FORMAT_MOD_Yf_TILED_CCS ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 void* div_fixed16 (scalar_t__,int) ; 
 scalar_t__ drm_rotation_90_or_270 (unsigned int) ; 
 int /*<<< orphan*/  fixed16_to_u32_round_up (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_get_linetime_us (struct intel_crtc_state const*) ; 
 scalar_t__ is_planar_yuv_format (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mul_u32_fixed16 (int,void*) ; 
 scalar_t__ skl_needs_memory_bw_wa (struct drm_i915_private*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 
 void* u32_to_fixed16 (scalar_t__) ; 

__attribute__((used)) static int
skl_compute_wm_params(const struct intel_crtc_state *crtc_state,
		      int width, const struct drm_format_info *format,
		      u64 modifier, unsigned int rotation,
		      u32 plane_pixel_rate, struct skl_wm_params *wp,
		      int color_plane)
{
	struct intel_crtc *crtc = to_intel_crtc(crtc_state->base.crtc);
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	u32 interm_pbpl;

	/* only planar format has two planes */
	if (color_plane == 1 && !is_planar_yuv_format(format->format)) {
		DRM_DEBUG_KMS("Non planar format have single plane\n");
		return -EINVAL;
	}

	wp->y_tiled = modifier == I915_FORMAT_MOD_Y_TILED ||
		      modifier == I915_FORMAT_MOD_Yf_TILED ||
		      modifier == I915_FORMAT_MOD_Y_TILED_CCS ||
		      modifier == I915_FORMAT_MOD_Yf_TILED_CCS;
	wp->x_tiled = modifier == I915_FORMAT_MOD_X_TILED;
	wp->rc_surface = modifier == I915_FORMAT_MOD_Y_TILED_CCS ||
			 modifier == I915_FORMAT_MOD_Yf_TILED_CCS;
	wp->is_planar = is_planar_yuv_format(format->format);

	wp->width = width;
	if (color_plane == 1 && wp->is_planar)
		wp->width /= 2;

	wp->cpp = format->cpp[color_plane];
	wp->plane_pixel_rate = plane_pixel_rate;

	if (INTEL_GEN(dev_priv) >= 11 &&
	    modifier == I915_FORMAT_MOD_Yf_TILED  && wp->cpp == 1)
		wp->dbuf_block_size = 256;
	else
		wp->dbuf_block_size = 512;

	if (drm_rotation_90_or_270(rotation)) {
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

	if (skl_needs_memory_bw_wa(dev_priv))
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
	} else if (wp->x_tiled && IS_GEN(dev_priv, 9)) {
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
					intel_get_linetime_us(crtc_state));

	return 0;
}