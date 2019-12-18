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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {unsigned int rotation; struct drm_framebuffer* fb; int /*<<< orphan*/  plane; } ;
struct intel_plane_state {TYPE_1__* color_plane; TYPE_2__ base; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct intel_plane {scalar_t__ id; TYPE_3__ base; } ;
struct drm_i915_private {int dummy; } ;
struct drm_framebuffer {int dummy; } ;
struct TYPE_4__ {int stride; } ;

/* Variables and functions */
 scalar_t__ PLANE_CURSOR ; 
 int /*<<< orphan*/  intel_compute_aligned_offset (struct drm_i915_private*,int*,int*,struct drm_framebuffer const*,int,int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_cursor_alignment (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_surf_alignment (struct drm_framebuffer const*,int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_plane* to_intel_plane (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 intel_plane_compute_aligned_offset(int *x, int *y,
					      const struct intel_plane_state *state,
					      int color_plane)
{
	struct intel_plane *intel_plane = to_intel_plane(state->base.plane);
	struct drm_i915_private *dev_priv = to_i915(intel_plane->base.dev);
	const struct drm_framebuffer *fb = state->base.fb;
	unsigned int rotation = state->base.rotation;
	int pitch = state->color_plane[color_plane].stride;
	u32 alignment;

	if (intel_plane->id == PLANE_CURSOR)
		alignment = intel_cursor_alignment(dev_priv);
	else
		alignment = intel_surf_alignment(fb, color_plane);

	return intel_compute_aligned_offset(dev_priv, x, y, fb, color_plane,
					    pitch, rotation, alignment);
}