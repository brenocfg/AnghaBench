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
struct drm_framebuffer {int modifier; TYPE_1__* format; } ;
struct TYPE_2__ {int* cpp; } ;

/* Variables and functions */
#define  DRM_FORMAT_MOD_LINEAR 133 
#define  I915_FORMAT_MOD_X_TILED 132 
#define  I915_FORMAT_MOD_Y_TILED 131 
#define  I915_FORMAT_MOD_Y_TILED_CCS 130 
#define  I915_FORMAT_MOD_Yf_TILED 129 
#define  I915_FORMAT_MOD_Yf_TILED_CCS 128 
 int /*<<< orphan*/  MISSING_CASE (int) ; 

__attribute__((used)) static int skl_max_plane_width(const struct drm_framebuffer *fb,
			       int color_plane,
			       unsigned int rotation)
{
	int cpp = fb->format->cpp[color_plane];

	switch (fb->modifier) {
	case DRM_FORMAT_MOD_LINEAR:
	case I915_FORMAT_MOD_X_TILED:
		/*
		 * Validated limit is 4k, but has 5k should
		 * work apart from the following features:
		 * - Ytile (already limited to 4k)
		 * - FP16 (already limited to 4k)
		 * - render compression (already limited to 4k)
		 * - KVMR sprite and cursor (don't care)
		 * - horizontal panning (TODO verify this)
		 * - pipe and plane scaling (TODO verify this)
		 */
		if (cpp == 8)
			return 4096;
		else
			return 5120;
	case I915_FORMAT_MOD_Y_TILED_CCS:
	case I915_FORMAT_MOD_Yf_TILED_CCS:
		/* FIXME AUX plane? */
	case I915_FORMAT_MOD_Y_TILED:
	case I915_FORMAT_MOD_Yf_TILED:
		if (cpp == 8)
			return 2048;
		else
			return 4096;
	default:
		MISSING_CASE(fb->modifier);
		return 2048;
	}
}