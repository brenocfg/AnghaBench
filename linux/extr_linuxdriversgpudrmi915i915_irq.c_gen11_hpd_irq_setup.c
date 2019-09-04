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
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN11_DE_HPD_IMR ; 
 int GEN11_DE_TBT_HOTPLUG_MASK ; 
 int GEN11_DE_TC_HOTPLUG_MASK ; 
 scalar_t__ HAS_PCH_ICP (struct drm_i915_private*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen11_hpd_detection_setup (struct drm_i915_private*) ; 
 int /*<<< orphan*/  hpd_gen11 ; 
 int /*<<< orphan*/  icp_hpd_irq_setup (struct drm_i915_private*) ; 
 int intel_hpd_enabled_irqs (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gen11_hpd_irq_setup(struct drm_i915_private *dev_priv)
{
	u32 hotplug_irqs, enabled_irqs;
	u32 val;

	enabled_irqs = intel_hpd_enabled_irqs(dev_priv, hpd_gen11);
	hotplug_irqs = GEN11_DE_TC_HOTPLUG_MASK | GEN11_DE_TBT_HOTPLUG_MASK;

	val = I915_READ(GEN11_DE_HPD_IMR);
	val &= ~hotplug_irqs;
	I915_WRITE(GEN11_DE_HPD_IMR, val);
	POSTING_READ(GEN11_DE_HPD_IMR);

	gen11_hpd_detection_setup(dev_priv);

	if (HAS_PCH_ICP(dev_priv))
		icp_hpd_irq_setup(dev_priv);
}