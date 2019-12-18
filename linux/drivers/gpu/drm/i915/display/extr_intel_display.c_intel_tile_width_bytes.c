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
struct drm_i915_private {int dummy; } ;
struct drm_framebuffer {int modifier; TYPE_1__* format; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {unsigned int* cpp; } ;

/* Variables and functions */
#define  DRM_FORMAT_MOD_LINEAR 133 
 int /*<<< orphan*/  HAS_128_BYTE_Y_TILING (struct drm_i915_private*) ; 
#define  I915_FORMAT_MOD_X_TILED 132 
#define  I915_FORMAT_MOD_Y_TILED 131 
#define  I915_FORMAT_MOD_Y_TILED_CCS 130 
#define  I915_FORMAT_MOD_Yf_TILED 129 
#define  I915_FORMAT_MOD_Yf_TILED_CCS 128 
 int /*<<< orphan*/  IS_GEN (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  MISSING_CASE (unsigned int) ; 
 unsigned int intel_tile_size (struct drm_i915_private*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
intel_tile_width_bytes(const struct drm_framebuffer *fb, int color_plane)
{
	struct drm_i915_private *dev_priv = to_i915(fb->dev);
	unsigned int cpp = fb->format->cpp[color_plane];

	switch (fb->modifier) {
	case DRM_FORMAT_MOD_LINEAR:
		return intel_tile_size(dev_priv);
	case I915_FORMAT_MOD_X_TILED:
		if (IS_GEN(dev_priv, 2))
			return 128;
		else
			return 512;
	case I915_FORMAT_MOD_Y_TILED_CCS:
		if (color_plane == 1)
			return 128;
		/* fall through */
	case I915_FORMAT_MOD_Y_TILED:
		if (IS_GEN(dev_priv, 2) || HAS_128_BYTE_Y_TILING(dev_priv))
			return 128;
		else
			return 512;
	case I915_FORMAT_MOD_Yf_TILED_CCS:
		if (color_plane == 1)
			return 128;
		/* fall through */
	case I915_FORMAT_MOD_Yf_TILED:
		switch (cpp) {
		case 1:
			return 64;
		case 2:
		case 4:
			return 128;
		case 8:
		case 16:
			return 256;
		default:
			MISSING_CASE(cpp);
			return cpp;
		}
		break;
	default:
		MISSING_CASE(fb->modifier);
		return cpp;
	}
}