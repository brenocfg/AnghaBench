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
struct drm_i915_private {int /*<<< orphan*/  irq_lock; } ;

/* Variables and functions */
 int CRT_HOTPLUG_ACTIVATION_PERIOD_64 ; 
 int CRT_HOTPLUG_VOLTAGE_COMPARE_50 ; 
 int CRT_HOTPLUG_VOLTAGE_COMPARE_MASK ; 
 int HOTPLUG_INT_EN_MASK ; 
 scalar_t__ IS_G4X (struct drm_i915_private*) ; 
 int /*<<< orphan*/  hpd_mask_i915 ; 
 int /*<<< orphan*/  i915_hotplug_interrupt_update_locked (struct drm_i915_private*,int,int) ; 
 int intel_hpd_enabled_irqs (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i915_hpd_irq_setup(struct drm_i915_private *dev_priv)
{
	u32 hotplug_en;

	lockdep_assert_held(&dev_priv->irq_lock);

	/* Note HDMI and DP share hotplug bits */
	/* enable bits are the same for all generations */
	hotplug_en = intel_hpd_enabled_irqs(dev_priv, hpd_mask_i915);
	/* Programming the CRT detection parameters tends
	   to generate a spurious hotplug event about three
	   seconds later.  So just do it once.
	*/
	if (IS_G4X(dev_priv))
		hotplug_en |= CRT_HOTPLUG_ACTIVATION_PERIOD_64;
	hotplug_en |= CRT_HOTPLUG_VOLTAGE_COMPARE_50;

	/* Ignore TV since it's buggy */
	i915_hotplug_interrupt_update_locked(dev_priv,
					     HOTPLUG_INT_EN_MASK |
					     CRT_HOTPLUG_VOLTAGE_COMPARE_MASK |
					     CRT_HOTPLUG_ACTIVATION_PERIOD_64,
					     hotplug_en);
}