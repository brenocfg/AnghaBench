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
 scalar_t__ HAS_PCH_CPT (struct drm_i915_private*) ; 
 scalar_t__ HAS_PCH_IBX (struct drm_i915_private*) ; 
 scalar_t__ HAS_PCH_LPT (struct drm_i915_private*) ; 
 int /*<<< orphan*/  ironlake_init_pch_refclk (struct drm_i915_private*) ; 
 int /*<<< orphan*/  lpt_init_pch_refclk (struct drm_i915_private*) ; 

void intel_init_pch_refclk(struct drm_i915_private *dev_priv)
{
	if (HAS_PCH_IBX(dev_priv) || HAS_PCH_CPT(dev_priv))
		ironlake_init_pch_refclk(dev_priv);
	else if (HAS_PCH_LPT(dev_priv))
		lpt_init_pch_refclk(dev_priv);
}