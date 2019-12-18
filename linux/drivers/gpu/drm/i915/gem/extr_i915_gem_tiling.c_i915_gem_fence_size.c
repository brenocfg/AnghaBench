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
typedef  int u32 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 unsigned int I915_TILING_NONE ; 
 int /*<<< orphan*/  I965_FENCE_PAGE ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_ALIGNED (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 unsigned int i915_gem_tile_height (unsigned int) ; 
 int roundup (int,unsigned int) ; 

u32 i915_gem_fence_size(struct drm_i915_private *i915,
			u32 size, unsigned int tiling, unsigned int stride)
{
	u32 ggtt_size;

	GEM_BUG_ON(!size);

	if (tiling == I915_TILING_NONE)
		return size;

	GEM_BUG_ON(!stride);

	if (INTEL_GEN(i915) >= 4) {
		stride *= i915_gem_tile_height(tiling);
		GEM_BUG_ON(!IS_ALIGNED(stride, I965_FENCE_PAGE));
		return roundup(size, stride);
	}

	/* Previous chips need a power-of-two fence region when tiling */
	if (IS_GEN(i915, 3))
		ggtt_size = 1024*1024;
	else
		ggtt_size = 512*1024;

	while (ggtt_size < size)
		ggtt_size <<= 1;

	return ggtt_size;
}