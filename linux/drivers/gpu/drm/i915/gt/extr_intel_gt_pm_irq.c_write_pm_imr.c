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
struct intel_uncore {int dummy; } ;
struct intel_gt {int pm_imr; struct intel_uncore* uncore; struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 int /*<<< orphan*/  GEN11_GPM_WGBOXPERF_INTR_MASK ; 
 int /*<<< orphan*/  GEN6_PMIMR ; 
 int /*<<< orphan*/  GEN8_GT_IMR (int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_uncore_write (struct intel_uncore*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void write_pm_imr(struct intel_gt *gt)
{
	struct drm_i915_private *i915 = gt->i915;
	struct intel_uncore *uncore = gt->uncore;
	u32 mask = gt->pm_imr;
	i915_reg_t reg;

	if (INTEL_GEN(i915) >= 11) {
		reg = GEN11_GPM_WGBOXPERF_INTR_MASK;
		mask <<= 16; /* pm is in upper half */
	} else if (INTEL_GEN(i915) >= 8) {
		reg = GEN8_GT_IMR(2);
	} else {
		reg = GEN6_PMIMR;
	}

	intel_uncore_write(uncore, reg, mask);
}