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
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 int /*<<< orphan*/  GEN11_GPM_WGBOXPERF_INTR_ENABLE ; 
 int /*<<< orphan*/  GEN6_PMIER ; 
 int /*<<< orphan*/  GEN8_GT_IER (int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 

__attribute__((used)) static i915_reg_t gen6_pm_ier(struct drm_i915_private *dev_priv)
{
	if (INTEL_GEN(dev_priv) >= 11)
		return GEN11_GPM_WGBOXPERF_INTR_ENABLE;
	else if (INTEL_GEN(dev_priv) >= 8)
		return GEN8_GT_IER(2);
	else
		return GEN6_PMIER;
}