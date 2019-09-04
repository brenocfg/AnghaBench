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
 int /*<<< orphan*/  GEN6_PMIIR ; 
 int /*<<< orphan*/  GEN8_GT_IIR (int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 

__attribute__((used)) static i915_reg_t gen6_pm_iir(struct drm_i915_private *dev_priv)
{
	WARN_ON_ONCE(INTEL_GEN(dev_priv) >= 11);

	return INTEL_GEN(dev_priv) >= 8 ? GEN8_GT_IIR(2) : GEN6_PMIIR;
}