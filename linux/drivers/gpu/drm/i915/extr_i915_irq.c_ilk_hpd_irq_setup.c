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
 int /*<<< orphan*/  DE_DP_A_HOTPLUG ; 
 int /*<<< orphan*/  DE_DP_A_HOTPLUG_IVB ; 
 int /*<<< orphan*/  GEN8_PORT_DP_A_HOTPLUG ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  bdw_update_port_irq (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpd_bdw ; 
 int /*<<< orphan*/  hpd_ilk ; 
 int /*<<< orphan*/  hpd_ivb ; 
 int /*<<< orphan*/  ibx_hpd_irq_setup (struct drm_i915_private*) ; 
 int /*<<< orphan*/  ilk_hpd_detection_setup (struct drm_i915_private*) ; 
 int /*<<< orphan*/  ilk_update_display_irq (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_hpd_enabled_irqs (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ilk_hpd_irq_setup(struct drm_i915_private *dev_priv)
{
	u32 hotplug_irqs, enabled_irqs;

	if (INTEL_GEN(dev_priv) >= 8) {
		hotplug_irqs = GEN8_PORT_DP_A_HOTPLUG;
		enabled_irqs = intel_hpd_enabled_irqs(dev_priv, hpd_bdw);

		bdw_update_port_irq(dev_priv, hotplug_irqs, enabled_irqs);
	} else if (INTEL_GEN(dev_priv) >= 7) {
		hotplug_irqs = DE_DP_A_HOTPLUG_IVB;
		enabled_irqs = intel_hpd_enabled_irqs(dev_priv, hpd_ivb);

		ilk_update_display_irq(dev_priv, hotplug_irqs, enabled_irqs);
	} else {
		hotplug_irqs = DE_DP_A_HOTPLUG;
		enabled_irqs = intel_hpd_enabled_irqs(dev_priv, hpd_ilk);

		ilk_update_display_irq(dev_priv, hotplug_irqs, enabled_irqs);
	}

	ilk_hpd_detection_setup(dev_priv);

	ibx_hpd_irq_setup(dev_priv);
}