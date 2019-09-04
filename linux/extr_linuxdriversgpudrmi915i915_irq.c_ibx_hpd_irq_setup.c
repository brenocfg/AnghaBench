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
typedef  int /*<<< orphan*/  u32 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 scalar_t__ HAS_PCH_IBX (struct drm_i915_private*) ; 
 int /*<<< orphan*/  SDE_HOTPLUG_MASK ; 
 int /*<<< orphan*/  SDE_HOTPLUG_MASK_CPT ; 
 int /*<<< orphan*/  hpd_cpt ; 
 int /*<<< orphan*/  hpd_ibx ; 
 int /*<<< orphan*/  ibx_display_interrupt_update (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibx_hpd_detection_setup (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_hpd_enabled_irqs (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ibx_hpd_irq_setup(struct drm_i915_private *dev_priv)
{
	u32 hotplug_irqs, enabled_irqs;

	if (HAS_PCH_IBX(dev_priv)) {
		hotplug_irqs = SDE_HOTPLUG_MASK;
		enabled_irqs = intel_hpd_enabled_irqs(dev_priv, hpd_ibx);
	} else {
		hotplug_irqs = SDE_HOTPLUG_MASK_CPT;
		enabled_irqs = intel_hpd_enabled_irqs(dev_priv, hpd_cpt);
	}

	ibx_display_interrupt_update(dev_priv, hotplug_irqs, enabled_irqs);

	ibx_hpd_detection_setup(dev_priv);
}