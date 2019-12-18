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
 scalar_t__ HAS_GMCH (struct drm_i915_private*) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  cherryview_irq_postinstall (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen11_irq_postinstall (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen8_irq_postinstall (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i8xx_irq_postinstall (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_irq_postinstall (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i965_irq_postinstall (struct drm_i915_private*) ; 
 int /*<<< orphan*/  ironlake_irq_postinstall (struct drm_i915_private*) ; 
 int /*<<< orphan*/  valleyview_irq_postinstall (struct drm_i915_private*) ; 

__attribute__((used)) static void intel_irq_postinstall(struct drm_i915_private *dev_priv)
{
	if (HAS_GMCH(dev_priv)) {
		if (IS_CHERRYVIEW(dev_priv))
			cherryview_irq_postinstall(dev_priv);
		else if (IS_VALLEYVIEW(dev_priv))
			valleyview_irq_postinstall(dev_priv);
		else if (IS_GEN(dev_priv, 4))
			i965_irq_postinstall(dev_priv);
		else if (IS_GEN(dev_priv, 3))
			i915_irq_postinstall(dev_priv);
		else
			i8xx_irq_postinstall(dev_priv);
	} else {
		if (INTEL_GEN(dev_priv) >= 11)
			gen11_irq_postinstall(dev_priv);
		else if (INTEL_GEN(dev_priv) >= 8)
			gen8_irq_postinstall(dev_priv);
		else
			ironlake_irq_postinstall(dev_priv);
	}
}