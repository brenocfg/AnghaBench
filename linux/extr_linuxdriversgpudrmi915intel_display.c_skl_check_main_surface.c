#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_12__ {int offset; int x; int y; } ;
struct TYPE_11__ {int offset; int x; int y; } ;
struct TYPE_13__ {int x1; int y1; } ;
struct TYPE_9__ {unsigned int rotation; TYPE_6__ dst; TYPE_6__ src; struct drm_framebuffer* fb; TYPE_1__* plane; } ;
struct intel_plane_state {TYPE_5__ main; TYPE_4__ aux; TYPE_2__ base; } ;
struct intel_crtc_state {int pipe_src_w; } ;
struct drm_i915_private {int dummy; } ;
struct drm_framebuffer {scalar_t__ modifier; int* pitches; TYPE_3__* format; } ;
struct TYPE_10__ {int* cpp; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int EINVAL ; 
 int ERANGE ; 
 scalar_t__ I915_FORMAT_MOD_X_TILED ; 
 scalar_t__ I915_FORMAT_MOD_Y_TILED_CCS ; 
 scalar_t__ I915_FORMAT_MOD_Yf_TILED_CCS ; 
 scalar_t__ IS_CANNONLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 
 int drm_rect_height (TYPE_6__*) ; 
 int drm_rect_width (TYPE_6__*) ; 
 int /*<<< orphan*/  intel_add_fb_offsets (int*,int*,struct intel_plane_state*,int /*<<< orphan*/ ) ; 
 int intel_adjust_tile_offset (int*,int*,struct intel_plane_state*,int /*<<< orphan*/ ,int,int) ; 
 int intel_compute_tile_offset (int*,int*,struct intel_plane_state*,int /*<<< orphan*/ ) ; 
 int intel_surf_alignment (struct drm_framebuffer const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skl_check_main_ccs_coordinates (struct intel_plane_state*,int,int,int) ; 
 int skl_max_plane_width (struct drm_framebuffer const*,int /*<<< orphan*/ ,unsigned int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int skl_check_main_surface(const struct intel_crtc_state *crtc_state,
				  struct intel_plane_state *plane_state)
{
	struct drm_i915_private *dev_priv =
		to_i915(plane_state->base.plane->dev);
	const struct drm_framebuffer *fb = plane_state->base.fb;
	unsigned int rotation = plane_state->base.rotation;
	int x = plane_state->base.src.x1 >> 16;
	int y = plane_state->base.src.y1 >> 16;
	int w = drm_rect_width(&plane_state->base.src) >> 16;
	int h = drm_rect_height(&plane_state->base.src) >> 16;
	int dst_x = plane_state->base.dst.x1;
	int dst_w = drm_rect_width(&plane_state->base.dst);
	int pipe_src_w = crtc_state->pipe_src_w;
	int max_width = skl_max_plane_width(fb, 0, rotation);
	int max_height = 4096;
	u32 alignment, offset, aux_offset = plane_state->aux.offset;

	if (w > max_width || h > max_height) {
		DRM_DEBUG_KMS("requested Y/RGB source size %dx%d too big (limit %dx%d)\n",
			      w, h, max_width, max_height);
		return -EINVAL;
	}

	/*
	 * Display WA #1175: cnl,glk
	 * Planes other than the cursor may cause FIFO underflow and display
	 * corruption if starting less than 4 pixels from the right edge of
	 * the screen.
	 * Besides the above WA fix the similar problem, where planes other
	 * than the cursor ending less than 4 pixels from the left edge of the
	 * screen may cause FIFO underflow and display corruption.
	 */
	if ((IS_GEMINILAKE(dev_priv) || IS_CANNONLAKE(dev_priv)) &&
	    (dst_x + dst_w < 4 || dst_x > pipe_src_w - 4)) {
		DRM_DEBUG_KMS("requested plane X %s position %d invalid (valid range %d-%d)\n",
			      dst_x + dst_w < 4 ? "end" : "start",
			      dst_x + dst_w < 4 ? dst_x + dst_w : dst_x,
			      4, pipe_src_w - 4);
		return -ERANGE;
	}

	intel_add_fb_offsets(&x, &y, plane_state, 0);
	offset = intel_compute_tile_offset(&x, &y, plane_state, 0);
	alignment = intel_surf_alignment(fb, 0);

	/*
	 * AUX surface offset is specified as the distance from the
	 * main surface offset, and it must be non-negative. Make
	 * sure that is what we will get.
	 */
	if (offset > aux_offset)
		offset = intel_adjust_tile_offset(&x, &y, plane_state, 0,
						  offset, aux_offset & ~(alignment - 1));

	/*
	 * When using an X-tiled surface, the plane blows up
	 * if the x offset + width exceed the stride.
	 *
	 * TODO: linear and Y-tiled seem fine, Yf untested,
	 */
	if (fb->modifier == I915_FORMAT_MOD_X_TILED) {
		int cpp = fb->format->cpp[0];

		while ((x + w) * cpp > fb->pitches[0]) {
			if (offset == 0) {
				DRM_DEBUG_KMS("Unable to find suitable display surface offset due to X-tiling\n");
				return -EINVAL;
			}

			offset = intel_adjust_tile_offset(&x, &y, plane_state, 0,
							  offset, offset - alignment);
		}
	}

	/*
	 * CCS AUX surface doesn't have its own x/y offsets, we must make sure
	 * they match with the main surface x/y offsets.
	 */
	if (fb->modifier == I915_FORMAT_MOD_Y_TILED_CCS ||
	    fb->modifier == I915_FORMAT_MOD_Yf_TILED_CCS) {
		while (!skl_check_main_ccs_coordinates(plane_state, x, y, offset)) {
			if (offset == 0)
				break;

			offset = intel_adjust_tile_offset(&x, &y, plane_state, 0,
							  offset, offset - alignment);
		}

		if (x != plane_state->aux.x || y != plane_state->aux.y) {
			DRM_DEBUG_KMS("Unable to find suitable display surface offset due to CCS\n");
			return -EINVAL;
		}
	}

	plane_state->main.offset = offset;
	plane_state->main.x = x;
	plane_state->main.y = y;

	return 0;
}