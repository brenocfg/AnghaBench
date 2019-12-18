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
typedef  scalar_t__ u32 ;
struct drm_i915_private {int dummy; } ;
struct drm_framebuffer {scalar_t__* pitches; int /*<<< orphan*/  modifier; TYPE_1__* format; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_FORMAT_MOD_LINEAR ; 
 scalar_t__ intel_plane_fb_max_stride (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_tile_size (struct drm_i915_private*) ; 
 scalar_t__ intel_tile_width_bytes (struct drm_framebuffer const*,int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32
intel_fb_stride_alignment(const struct drm_framebuffer *fb, int color_plane)
{
	struct drm_i915_private *dev_priv = to_i915(fb->dev);

	if (fb->modifier == DRM_FORMAT_MOD_LINEAR) {
		u32 max_stride = intel_plane_fb_max_stride(dev_priv,
							   fb->format->format,
							   fb->modifier);

		/*
		 * To make remapping with linear generally feasible
		 * we need the stride to be page aligned.
		 */
		if (fb->pitches[color_plane] > max_stride)
			return intel_tile_size(dev_priv);
		else
			return 64;
	} else {
		return intel_tile_width_bytes(fb, color_plane);
	}
}