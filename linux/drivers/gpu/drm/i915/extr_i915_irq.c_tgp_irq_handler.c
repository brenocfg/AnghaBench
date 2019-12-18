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
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int SDE_DDI_MASK_TGP ; 
 int SDE_GMBUS_ICP ; 
 int SDE_TC_MASK_TGP ; 
 int /*<<< orphan*/  SHOTPLUG_CTL_DDI ; 
 int /*<<< orphan*/  SHOTPLUG_CTL_TC ; 
 int /*<<< orphan*/  gmbus_irq_handler (struct drm_i915_private*) ; 
 int /*<<< orphan*/  hpd_tgp ; 
 int /*<<< orphan*/  intel_get_hpd_pins (struct drm_i915_private*,int*,int*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_hpd_irq_handler (struct drm_i915_private*,int,int) ; 
 int /*<<< orphan*/  tgp_ddi_port_hotplug_long_detect ; 
 int /*<<< orphan*/  tgp_tc_port_hotplug_long_detect ; 

__attribute__((used)) static void tgp_irq_handler(struct drm_i915_private *dev_priv, u32 pch_iir)
{
	u32 ddi_hotplug_trigger = pch_iir & SDE_DDI_MASK_TGP;
	u32 tc_hotplug_trigger = pch_iir & SDE_TC_MASK_TGP;
	u32 pin_mask = 0, long_mask = 0;

	if (ddi_hotplug_trigger) {
		u32 dig_hotplug_reg;

		dig_hotplug_reg = I915_READ(SHOTPLUG_CTL_DDI);
		I915_WRITE(SHOTPLUG_CTL_DDI, dig_hotplug_reg);

		intel_get_hpd_pins(dev_priv, &pin_mask, &long_mask,
				   ddi_hotplug_trigger,
				   dig_hotplug_reg, hpd_tgp,
				   tgp_ddi_port_hotplug_long_detect);
	}

	if (tc_hotplug_trigger) {
		u32 dig_hotplug_reg;

		dig_hotplug_reg = I915_READ(SHOTPLUG_CTL_TC);
		I915_WRITE(SHOTPLUG_CTL_TC, dig_hotplug_reg);

		intel_get_hpd_pins(dev_priv, &pin_mask, &long_mask,
				   tc_hotplug_trigger,
				   dig_hotplug_reg, hpd_tgp,
				   tgp_tc_port_hotplug_long_detect);
	}

	if (pin_mask)
		intel_hpd_irq_handler(dev_priv, pin_mask, long_mask);

	if (pch_iir & SDE_GMBUS_ICP)
		gmbus_irq_handler(dev_priv);
}