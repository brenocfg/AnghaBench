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
struct intel_fbc {int active; } ;
struct drm_i915_private {struct intel_fbc fbc; } ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_GM45 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  g4x_fbc_activate (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen7_fbc_activate (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i8xx_fbc_activate (struct drm_i915_private*) ; 
 int /*<<< orphan*/  ilk_fbc_activate (struct drm_i915_private*) ; 

__attribute__((used)) static void intel_fbc_hw_activate(struct drm_i915_private *dev_priv)
{
	struct intel_fbc *fbc = &dev_priv->fbc;

	fbc->active = true;

	if (INTEL_GEN(dev_priv) >= 7)
		gen7_fbc_activate(dev_priv);
	else if (INTEL_GEN(dev_priv) >= 5)
		ilk_fbc_activate(dev_priv);
	else if (IS_GM45(dev_priv))
		g4x_fbc_activate(dev_priv);
	else
		i8xx_fbc_activate(dev_priv);
}