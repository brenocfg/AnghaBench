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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct drm_i915_gem_object {TYPE_1__ base; } ;

/* Variables and functions */
 unsigned int GEN7_FENCE_MAX_PITCH_VAL ; 
 scalar_t__ HAS_128_BYTE_Y_TILING (struct drm_i915_private*) ; 
 unsigned int I915_TILING_LAST ; 
 unsigned int I915_TILING_NONE ; 
 unsigned int I915_TILING_Y ; 
 unsigned int I965_FENCE_MAX_PITCH_VAL ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_ALIGNED (unsigned int,unsigned int) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  is_power_of_2 (unsigned int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
i915_tiling_ok(struct drm_i915_gem_object *obj,
	       unsigned int tiling, unsigned int stride)
{
	struct drm_i915_private *i915 = to_i915(obj->base.dev);
	unsigned int tile_width;

	/* Linear is always fine */
	if (tiling == I915_TILING_NONE)
		return true;

	if (tiling > I915_TILING_LAST)
		return false;

	/* check maximum stride & object size */
	/* i965+ stores the end address of the gtt mapping in the fence
	 * reg, so dont bother to check the size */
	if (INTEL_GEN(i915) >= 7) {
		if (stride / 128 > GEN7_FENCE_MAX_PITCH_VAL)
			return false;
	} else if (INTEL_GEN(i915) >= 4) {
		if (stride / 128 > I965_FENCE_MAX_PITCH_VAL)
			return false;
	} else {
		if (stride > 8192)
			return false;

		if (!is_power_of_2(stride))
			return false;
	}

	if (IS_GEN(i915, 2) ||
	    (tiling == I915_TILING_Y && HAS_128_BYTE_Y_TILING(i915)))
		tile_width = 128;
	else
		tile_width = 512;

	if (!stride || !IS_ALIGNED(stride, tile_width))
		return false;

	return true;
}