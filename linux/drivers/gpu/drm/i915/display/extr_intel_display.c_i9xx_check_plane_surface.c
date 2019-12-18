#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_10__ {int x1; int y1; } ;
struct TYPE_8__ {unsigned int rotation; TYPE_4__ src; int /*<<< orphan*/  visible; TYPE_1__* plane; } ;
struct intel_plane_state {TYPE_3__* color_plane; TYPE_2__ base; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_9__ {int x; int y; scalar_t__ offset; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int DRM_MODE_REFLECT_X ; 
 unsigned int DRM_MODE_ROTATE_180 ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_BROADWELL (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_HASWELL (struct drm_i915_private*) ; 
 int drm_rect_height (TYPE_4__*) ; 
 int /*<<< orphan*/  drm_rect_translate (TYPE_4__*,int,int) ; 
 int drm_rect_width (TYPE_4__*) ; 
 int /*<<< orphan*/  intel_add_fb_offsets (int*,int*,struct intel_plane_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_plane_compute_aligned_offset (int*,int*,struct intel_plane_state*,int /*<<< orphan*/ ) ; 
 int intel_plane_compute_gtt (struct intel_plane_state*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

int i9xx_check_plane_surface(struct intel_plane_state *plane_state)
{
	struct drm_i915_private *dev_priv =
		to_i915(plane_state->base.plane->dev);
	int src_x, src_y;
	u32 offset;
	int ret;

	ret = intel_plane_compute_gtt(plane_state);
	if (ret)
		return ret;

	if (!plane_state->base.visible)
		return 0;

	src_x = plane_state->base.src.x1 >> 16;
	src_y = plane_state->base.src.y1 >> 16;

	intel_add_fb_offsets(&src_x, &src_y, plane_state, 0);

	if (INTEL_GEN(dev_priv) >= 4)
		offset = intel_plane_compute_aligned_offset(&src_x, &src_y,
							    plane_state, 0);
	else
		offset = 0;

	/*
	 * Put the final coordinates back so that the src
	 * coordinate checks will see the right values.
	 */
	drm_rect_translate(&plane_state->base.src,
			   (src_x << 16) - plane_state->base.src.x1,
			   (src_y << 16) - plane_state->base.src.y1);

	/* HSW/BDW do this automagically in hardware */
	if (!IS_HASWELL(dev_priv) && !IS_BROADWELL(dev_priv)) {
		unsigned int rotation = plane_state->base.rotation;
		int src_w = drm_rect_width(&plane_state->base.src) >> 16;
		int src_h = drm_rect_height(&plane_state->base.src) >> 16;

		if (rotation & DRM_MODE_ROTATE_180) {
			src_x += src_w - 1;
			src_y += src_h - 1;
		} else if (rotation & DRM_MODE_REFLECT_X) {
			src_x += src_w - 1;
		}
	}

	plane_state->color_plane[0].offset = offset;
	plane_state->color_plane[0].x = src_x;
	plane_state->color_plane[0].y = src_y;

	return 0;
}