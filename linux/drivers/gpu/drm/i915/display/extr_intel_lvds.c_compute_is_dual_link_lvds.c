#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {struct drm_device* dev; } ;
struct TYPE_13__ {TYPE_5__ base; } ;
struct intel_lvds_encoder {int /*<<< orphan*/  reg; TYPE_3__* attached_connector; TYPE_6__ base; } ;
struct TYPE_11__ {unsigned int bios_lvds_val; } ;
struct drm_i915_private {TYPE_4__ vbt; } ;
struct drm_device {int dummy; } ;
struct TYPE_14__ {int lvds_channel_mode; } ;
struct TYPE_9__ {TYPE_1__* fixed_mode; } ;
struct TYPE_10__ {TYPE_2__ panel; } ;
struct TYPE_8__ {int clock; } ;

/* Variables and functions */
 scalar_t__ HAS_PCH_CPT (struct drm_i915_private*) ; 
 unsigned int I915_READ (int /*<<< orphan*/ ) ; 
 unsigned int LVDS_CLKB_POWER_MASK ; 
 unsigned int LVDS_CLKB_POWER_UP ; 
 unsigned int LVDS_DETECTED ; 
 unsigned int LVDS_PIPE_SEL_MASK ; 
 unsigned int LVDS_PIPE_SEL_MASK_CPT ; 
 scalar_t__ dmi_check_system (int /*<<< orphan*/ ) ; 
 TYPE_7__ i915_modparams ; 
 int /*<<< orphan*/  intel_dual_link_lvds ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static bool compute_is_dual_link_lvds(struct intel_lvds_encoder *lvds_encoder)
{
	struct drm_device *dev = lvds_encoder->base.base.dev;
	unsigned int val;
	struct drm_i915_private *dev_priv = to_i915(dev);

	/* use the module option value if specified */
	if (i915_modparams.lvds_channel_mode > 0)
		return i915_modparams.lvds_channel_mode == 2;

	/* single channel LVDS is limited to 112 MHz */
	if (lvds_encoder->attached_connector->panel.fixed_mode->clock > 112999)
		return true;

	if (dmi_check_system(intel_dual_link_lvds))
		return true;

	/*
	 * BIOS should set the proper LVDS register value at boot, but
	 * in reality, it doesn't set the value when the lid is closed;
	 * we need to check "the value to be set" in VBT when LVDS
	 * register is uninitialized.
	 */
	val = I915_READ(lvds_encoder->reg);
	if (HAS_PCH_CPT(dev_priv))
		val &= ~(LVDS_DETECTED | LVDS_PIPE_SEL_MASK_CPT);
	else
		val &= ~(LVDS_DETECTED | LVDS_PIPE_SEL_MASK);
	if (val == 0)
		val = dev_priv->vbt.bios_lvds_val;

	return (val & LVDS_CLKB_POWER_MASK) == LVDS_CLKB_POWER_UP;
}