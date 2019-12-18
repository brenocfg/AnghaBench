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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_plane {scalar_t__ i9xx_plane; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HAS_GMCH (struct drm_i915_private*) ; 
 scalar_t__ I915_FORMAT_MOD_X_TILED ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ PLANE_C ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

unsigned int
i9xx_plane_max_stride(struct intel_plane *plane,
		      u32 pixel_format, u64 modifier,
		      unsigned int rotation)
{
	struct drm_i915_private *dev_priv = to_i915(plane->base.dev);

	if (!HAS_GMCH(dev_priv)) {
		return 32*1024;
	} else if (INTEL_GEN(dev_priv) >= 4) {
		if (modifier == I915_FORMAT_MOD_X_TILED)
			return 16*1024;
		else
			return 32*1024;
	} else if (INTEL_GEN(dev_priv) >= 3) {
		if (modifier == I915_FORMAT_MOD_X_TILED)
			return 8*1024;
		else
			return 16*1024;
	} else {
		if (plane->i9xx_plane == PLANE_C)
			return 4*1024;
		else
			return 8*1024;
	}
}