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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {unsigned int rotation; struct drm_framebuffer* fb; int /*<<< orphan*/  plane; } ;
struct intel_plane_state {TYPE_1__ base; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct intel_plane {scalar_t__ id; TYPE_2__ base; } ;
struct drm_i915_private {int dummy; } ;
struct drm_framebuffer {int dummy; } ;

/* Variables and functions */
 scalar_t__ PLANE_CURSOR ; 
 int /*<<< orphan*/  _intel_compute_tile_offset (struct drm_i915_private*,int*,int*,struct drm_framebuffer const*,int,int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_cursor_alignment (struct drm_i915_private*) ; 
 int intel_fb_pitch (struct drm_framebuffer const*,int,unsigned int) ; 
 int /*<<< orphan*/  intel_surf_alignment (struct drm_framebuffer const*,int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_plane* to_intel_plane (int /*<<< orphan*/ ) ; 

u32 intel_compute_tile_offset(int *x, int *y,
			      const struct intel_plane_state *state,
			      int plane)
{
	struct intel_plane *intel_plane = to_intel_plane(state->base.plane);
	struct drm_i915_private *dev_priv = to_i915(intel_plane->base.dev);
	const struct drm_framebuffer *fb = state->base.fb;
	unsigned int rotation = state->base.rotation;
	int pitch = intel_fb_pitch(fb, plane, rotation);
	u32 alignment;

	if (intel_plane->id == PLANE_CURSOR)
		alignment = intel_cursor_alignment(dev_priv);
	else
		alignment = intel_surf_alignment(fb, plane);

	return _intel_compute_tile_offset(dev_priv, x, y, fb, plane, pitch,
					  rotation, alignment);
}