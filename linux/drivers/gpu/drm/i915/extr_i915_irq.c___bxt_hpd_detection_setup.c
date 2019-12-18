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
 int BXT_DDIA_HPD_INVERT ; 
 int BXT_DDIB_HPD_INVERT ; 
 int BXT_DDIC_HPD_INVERT ; 
 int BXT_DDI_HPD_INVERT_MASK ; 
 int BXT_DE_PORT_HP_DDIA ; 
 int BXT_DE_PORT_HP_DDIB ; 
 int BXT_DE_PORT_HP_DDIC ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PCH_PORT_HOTPLUG ; 
 int PORTA_HOTPLUG_ENABLE ; 
 int PORTB_HOTPLUG_ENABLE ; 
 int PORTC_HOTPLUG_ENABLE ; 
 int /*<<< orphan*/  PORT_A ; 
 int /*<<< orphan*/  PORT_B ; 
 int /*<<< orphan*/  PORT_C ; 
 scalar_t__ intel_bios_is_port_hpd_inverted (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __bxt_hpd_detection_setup(struct drm_i915_private *dev_priv,
				      u32 enabled_irqs)
{
	u32 hotplug;

	hotplug = I915_READ(PCH_PORT_HOTPLUG);
	hotplug |= PORTA_HOTPLUG_ENABLE |
		   PORTB_HOTPLUG_ENABLE |
		   PORTC_HOTPLUG_ENABLE;

	DRM_DEBUG_KMS("Invert bit setting: hp_ctl:%x hp_port:%x\n",
		      hotplug, enabled_irqs);
	hotplug &= ~BXT_DDI_HPD_INVERT_MASK;

	/*
	 * For BXT invert bit has to be set based on AOB design
	 * for HPD detection logic, update it based on VBT fields.
	 */
	if ((enabled_irqs & BXT_DE_PORT_HP_DDIA) &&
	    intel_bios_is_port_hpd_inverted(dev_priv, PORT_A))
		hotplug |= BXT_DDIA_HPD_INVERT;
	if ((enabled_irqs & BXT_DE_PORT_HP_DDIB) &&
	    intel_bios_is_port_hpd_inverted(dev_priv, PORT_B))
		hotplug |= BXT_DDIB_HPD_INVERT;
	if ((enabled_irqs & BXT_DE_PORT_HP_DDIC) &&
	    intel_bios_is_port_hpd_inverted(dev_priv, PORT_C))
		hotplug |= BXT_DDIC_HPD_INVERT;

	I915_WRITE(PCH_PORT_HOTPLUG, hotplug);
}