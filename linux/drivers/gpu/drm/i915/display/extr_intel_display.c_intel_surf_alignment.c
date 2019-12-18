#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct drm_i915_private {int dummy; } ;
struct drm_framebuffer {int modifier; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  DRM_FORMAT_MOD_LINEAR 133 
#define  I915_FORMAT_MOD_X_TILED 132 
#define  I915_FORMAT_MOD_Y_TILED 131 
#define  I915_FORMAT_MOD_Y_TILED_CCS 130 
#define  I915_FORMAT_MOD_Yf_TILED 129 
#define  I915_FORMAT_MOD_Yf_TILED_CCS 128 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 unsigned int intel_linear_alignment (struct drm_i915_private*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int intel_surf_alignment(const struct drm_framebuffer *fb,
					 int color_plane)
{
	struct drm_i915_private *dev_priv = to_i915(fb->dev);

	/* AUX_DIST needs only 4K alignment */
	if (color_plane == 1)
		return 4096;

	switch (fb->modifier) {
	case DRM_FORMAT_MOD_LINEAR:
		return intel_linear_alignment(dev_priv);
	case I915_FORMAT_MOD_X_TILED:
		if (INTEL_GEN(dev_priv) >= 9)
			return 256 * 1024;
		return 0;
	case I915_FORMAT_MOD_Y_TILED_CCS:
	case I915_FORMAT_MOD_Yf_TILED_CCS:
	case I915_FORMAT_MOD_Y_TILED:
	case I915_FORMAT_MOD_Yf_TILED:
		return 1 * 1024 * 1024;
	default:
		MISSING_CASE(fb->modifier);
		return 0;
	}
}