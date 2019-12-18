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
 int INTEL_GEN (struct drm_i915_private*) ; 

__attribute__((used)) static bool mcr_range(struct drm_i915_private *i915, u32 offset)
{
	/*
	 * Registers in this range are affected by the MCR selector
	 * which only controls CPU initiated MMIO. Routing does not
	 * work for CS access so we cannot verify them on this path.
	 */
	if (INTEL_GEN(i915) >= 8 && (offset >= 0xb100 && offset <= 0xb3ff))
		return true;

	return false;
}