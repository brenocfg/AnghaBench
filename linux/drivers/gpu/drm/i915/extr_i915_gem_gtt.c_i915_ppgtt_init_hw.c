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
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  gen6_ppgtt_enable (struct intel_gt*) ; 
 int /*<<< orphan*/  gen7_ppgtt_enable (struct intel_gt*) ; 
 int /*<<< orphan*/  gtt_write_workarounds (struct intel_gt*) ; 

int i915_ppgtt_init_hw(struct intel_gt *gt)
{
	struct drm_i915_private *i915 = gt->i915;

	gtt_write_workarounds(gt);

	if (IS_GEN(i915, 6))
		gen6_ppgtt_enable(gt);
	else if (IS_GEN(i915, 7))
		gen7_ppgtt_enable(gt);

	return 0;
}