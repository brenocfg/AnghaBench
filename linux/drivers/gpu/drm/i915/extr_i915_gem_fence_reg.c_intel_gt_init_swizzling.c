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
struct intel_uncore {int dummy; } ;
struct intel_gt {struct intel_uncore* uncore; struct drm_i915_private* i915; } ;
struct TYPE_2__ {scalar_t__ bit_6_swizzle_x; } ;
struct drm_i915_private {TYPE_1__ mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARB_MODE ; 
 int /*<<< orphan*/  ARB_MODE_SWIZZLE_BDW ; 
 int /*<<< orphan*/  ARB_MODE_SWIZZLE_IVB ; 
 int /*<<< orphan*/  ARB_MODE_SWIZZLE_SNB ; 
 int /*<<< orphan*/  DISP_ARB_CTL ; 
 int /*<<< orphan*/  DISP_TILE_SURFACE_SWIZZLING ; 
 int /*<<< orphan*/  GAMTARBMODE ; 
 scalar_t__ I915_BIT_6_SWIZZLE_NONE ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 int /*<<< orphan*/  TILECTL ; 
 int /*<<< orphan*/  TILECTL_SWZCTL ; 
 int /*<<< orphan*/  _MASKED_BIT_ENABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_rmw (struct intel_uncore*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_write (struct intel_uncore*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void intel_gt_init_swizzling(struct intel_gt *gt)
{
	struct drm_i915_private *i915 = gt->i915;
	struct intel_uncore *uncore = gt->uncore;

	if (INTEL_GEN(i915) < 5 ||
	    i915->mm.bit_6_swizzle_x == I915_BIT_6_SWIZZLE_NONE)
		return;

	intel_uncore_rmw(uncore, DISP_ARB_CTL, 0, DISP_TILE_SURFACE_SWIZZLING);

	if (IS_GEN(i915, 5))
		return;

	intel_uncore_rmw(uncore, TILECTL, 0, TILECTL_SWZCTL);

	if (IS_GEN(i915, 6))
		intel_uncore_write(uncore,
				   ARB_MODE,
				   _MASKED_BIT_ENABLE(ARB_MODE_SWIZZLE_SNB));
	else if (IS_GEN(i915, 7))
		intel_uncore_write(uncore,
				   ARB_MODE,
				   _MASKED_BIT_ENABLE(ARB_MODE_SWIZZLE_IVB));
	else if (IS_GEN(i915, 8))
		intel_uncore_write(uncore,
				   GAMTARBMODE,
				   _MASKED_BIT_ENABLE(ARB_MODE_SWIZZLE_BDW));
	else
		MISSING_CASE(INTEL_GEN(i915));
}