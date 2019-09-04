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
typedef  int /*<<< orphan*/  u32 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  I915_GTT_MIN_ALIGNMENT ; 
 unsigned int I915_TILING_NONE ; 
 int /*<<< orphan*/  I965_FENCE_PAGE ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_fence_size (struct drm_i915_private*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

u32 i915_gem_fence_alignment(struct drm_i915_private *i915, u32 size,
			     unsigned int tiling, unsigned int stride)
{
	GEM_BUG_ON(!size);

	/*
	 * Minimum alignment is 4k (GTT page size), but might be greater
	 * if a fence register is needed for the object.
	 */
	if (tiling == I915_TILING_NONE)
		return I915_GTT_MIN_ALIGNMENT;

	if (INTEL_GEN(i915) >= 4)
		return I965_FENCE_PAGE;

	/*
	 * Previous chips need to be aligned to the size of the smallest
	 * fence register that can contain the object.
	 */
	return i915_gem_fence_size(i915, size, tiling, stride);
}