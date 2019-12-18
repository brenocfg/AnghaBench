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
typedef  int /*<<< orphan*/  irq_handler_t ;

/* Variables and functions */
 scalar_t__ HAS_GMCH (struct drm_i915_private*) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  cherryview_irq_handler ; 
 int /*<<< orphan*/  gen11_irq_handler ; 
 int /*<<< orphan*/  gen8_irq_handler ; 
 int /*<<< orphan*/  i8xx_irq_handler ; 
 int /*<<< orphan*/  i915_irq_handler ; 
 int /*<<< orphan*/  i965_irq_handler ; 
 int /*<<< orphan*/  ironlake_irq_handler ; 
 int /*<<< orphan*/  valleyview_irq_handler ; 

__attribute__((used)) static irq_handler_t intel_irq_handler(struct drm_i915_private *dev_priv)
{
	if (HAS_GMCH(dev_priv)) {
		if (IS_CHERRYVIEW(dev_priv))
			return cherryview_irq_handler;
		else if (IS_VALLEYVIEW(dev_priv))
			return valleyview_irq_handler;
		else if (IS_GEN(dev_priv, 4))
			return i965_irq_handler;
		else if (IS_GEN(dev_priv, 3))
			return i915_irq_handler;
		else
			return i8xx_irq_handler;
	} else {
		if (INTEL_GEN(dev_priv) >= 11)
			return gen11_irq_handler;
		else if (INTEL_GEN(dev_priv) >= 8)
			return gen8_irq_handler;
		else
			return ironlake_irq_handler;
	}
}