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
struct drm_framebuffer {scalar_t__ modifier; int* offsets; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ DRM_FORMAT_MOD_LINEAR ; 
 int /*<<< orphan*/  DRM_MODE_ROTATE_0 ; 
 int EINVAL ; 
 int /*<<< orphan*/  _intel_adjust_tile_offset (int*,int*,struct drm_framebuffer const*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int intel_tile_size (struct drm_i915_private*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intel_fb_offset_to_xy(int *x, int *y,
				 const struct drm_framebuffer *fb, int plane)
{
	struct drm_i915_private *dev_priv = to_i915(fb->dev);

	if (fb->modifier != DRM_FORMAT_MOD_LINEAR &&
	    fb->offsets[plane] % intel_tile_size(dev_priv))
		return -EINVAL;

	*x = 0;
	*y = 0;

	_intel_adjust_tile_offset(x, y,
				  fb, plane, DRM_MODE_ROTATE_0,
				  fb->offsets[plane], 0);

	return 0;
}