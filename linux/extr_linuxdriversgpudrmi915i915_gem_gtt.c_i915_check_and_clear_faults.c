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

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen6_check_and_clear_faults (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen8_check_and_clear_faults (struct drm_i915_private*) ; 

void i915_check_and_clear_faults(struct drm_i915_private *dev_priv)
{
	/* From GEN8 onwards we only have one 'All Engine Fault Register' */
	if (INTEL_GEN(dev_priv) >= 8)
		gen8_check_and_clear_faults(dev_priv);
	else if (INTEL_GEN(dev_priv) >= 6)
		gen6_check_and_clear_faults(dev_priv);
	else
		return;
}