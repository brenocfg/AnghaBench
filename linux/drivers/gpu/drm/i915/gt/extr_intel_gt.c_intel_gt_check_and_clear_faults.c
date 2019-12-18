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
struct intel_gt {struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_ENGINES ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen6_check_faults (struct intel_gt*) ; 
 int /*<<< orphan*/  gen8_check_faults (struct intel_gt*) ; 
 int /*<<< orphan*/  intel_gt_clear_error_registers (struct intel_gt*,int /*<<< orphan*/ ) ; 

void intel_gt_check_and_clear_faults(struct intel_gt *gt)
{
	struct drm_i915_private *i915 = gt->i915;

	/* From GEN8 onwards we only have one 'All Engine Fault Register' */
	if (INTEL_GEN(i915) >= 8)
		gen8_check_faults(gt);
	else if (INTEL_GEN(i915) >= 6)
		gen6_check_faults(gt);
	else
		return;

	intel_gt_clear_error_registers(gt, ALL_ENGINES);
}