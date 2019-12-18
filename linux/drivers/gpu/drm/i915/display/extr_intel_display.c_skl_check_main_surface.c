#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_12__ {int x1; int y1; } ;
struct TYPE_11__ {unsigned int rotation; TYPE_5__ src; struct drm_framebuffer* fb; TYPE_1__* plane; } ;
struct intel_plane_state {TYPE_4__ base; TYPE_3__* color_plane; } ;
struct drm_i915_private {int dummy; } ;
struct drm_framebuffer {scalar_t__ modifier; TYPE_2__* format; } ;
struct TYPE_10__ {int offset; int stride; int x; int y; } ;
struct TYPE_9__ {int* cpp; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int EINVAL ; 
 scalar_t__ I915_FORMAT_MOD_X_TILED ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 
 int drm_rect_height (TYPE_5__*) ; 
 int /*<<< orphan*/  drm_rect_translate (TYPE_5__*,int,int) ; 
 int drm_rect_width (TYPE_5__*) ; 
 int glk_max_plane_width (struct drm_framebuffer const*,int /*<<< orphan*/ ,unsigned int) ; 
 int icl_max_plane_width (struct drm_framebuffer const*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  intel_add_fb_offsets (int*,int*,struct intel_plane_state*,int /*<<< orphan*/ ) ; 
 int intel_plane_adjust_aligned_offset (int*,int*,struct intel_plane_state*,int /*<<< orphan*/ ,int,int) ; 
 int intel_plane_compute_aligned_offset (int*,int*,struct intel_plane_state*,int /*<<< orphan*/ ) ; 
 int intel_surf_alignment (struct drm_framebuffer const*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_ccs_modifier (scalar_t__) ; 
 int /*<<< orphan*/  skl_check_main_ccs_coordinates (struct intel_plane_state*,int,int,int) ; 
 int skl_max_plane_width (struct drm_framebuffer const*,int /*<<< orphan*/ ,unsigned int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int skl_check_main_surface(struct intel_plane_state *plane_state)
{
	struct drm_i915_private *dev_priv = to_i915(plane_state->base.plane->dev);
	const struct drm_framebuffer *fb = plane_state->base.fb;
	unsigned int rotation = plane_state->base.rotation;
	int x = plane_state->base.src.x1 >> 16;
	int y = plane_state->base.src.y1 >> 16;
	int w = drm_rect_width(&plane_state->base.src) >> 16;
	int h = drm_rect_height(&plane_state->base.src) >> 16;
	int max_width;
	int max_height = 4096;
	u32 alignment, offset, aux_offset = plane_state->color_plane[1].offset;

	if (INTEL_GEN(dev_priv) >= 11)
		max_width = icl_max_plane_width(fb, 0, rotation);
	else if (INTEL_GEN(dev_priv) >= 10 || IS_GEMINILAKE(dev_priv))
		max_width = glk_max_plane_width(fb, 0, rotation);
	else
		max_width = skl_max_plane_width(fb, 0, rotation);

	if (w > max_width || h > max_height) {
		DRM_DEBUG_KMS("requested Y/RGB source size %dx%d too big (limit %dx%d)\n",
			      w, h, max_width, max_height);
		return -EINVAL;
	}

	intel_add_fb_offsets(&x, &y, plane_state, 0);
	offset = intel_plane_compute_aligned_offset(&x, &y, plane_state, 0);
	alignment = intel_surf_alignment(fb, 0);

	/*
	 * AUX surface offset is specified as the distance from the
	 * main surface offset, and it must be non-negative. Make
	 * sure that is what we will get.
	 */
	if (offset > aux_offset)
		offset = intel_plane_adjust_aligned_offset(&x, &y, plane_state, 0,
							   offset, aux_offset & ~(alignment - 1));

	/*
	 * When using an X-tiled surface, the plane blows up
	 * if the x offset + width exceed the stride.
	 *
	 * TODO: linear and Y-tiled seem fine, Yf untested,
	 */
	if (fb->modifier == I915_FORMAT_MOD_X_TILED) {
		int cpp = fb->format->cpp[0];

		while ((x + w) * cpp > plane_state->color_plane[0].stride) {
			if (offset == 0) {
				DRM_DEBUG_KMS("Unable to find suitable display surface offset due to X-tiling\n");
				return -EINVAL;
			}

			offset = intel_plane_adjust_aligned_offset(&x, &y, plane_state, 0,
								   offset, offset - alignment);
		}
	}

	/*
	 * CCS AUX surface doesn't have its own x/y offsets, we must make sure
	 * they match with the main surface x/y offsets.
	 */
	if (is_ccs_modifier(fb->modifier)) {
		while (!skl_check_main_ccs_coordinates(plane_state, x, y, offset)) {
			if (offset == 0)
				break;

			offset = intel_plane_adjust_aligned_offset(&x, &y, plane_state, 0,
								   offset, offset - alignment);
		}

		if (x != plane_state->color_plane[1].x || y != plane_state->color_plane[1].y) {
			DRM_DEBUG_KMS("Unable to find suitable display surface offset due to CCS\n");
			return -EINVAL;
		}
	}

	plane_state->color_plane[0].offset = offset;
	plane_state->color_plane[0].x = x;
	plane_state->color_plane[0].y = y;

	/*
	 * Put the final coordinates back so that the src
	 * coordinate checks will see the right values.
	 */
	drm_rect_translate(&plane_state->base.src,
			   (x << 16) - plane_state->base.src.x1,
			   (y << 16) - plane_state->base.src.y1);

	return 0;
}