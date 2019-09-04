#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct drm_i915_private {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  disable_power_well; } ;

/* Variables and functions */
 scalar_t__ IS_CANNONLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_BC (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 scalar_t__ IS_ICELAKE (struct drm_i915_private*) ; 
 int /*<<< orphan*/  POWER_DOMAIN_INIT ; 
 int /*<<< orphan*/  bxt_display_core_uninit (struct drm_i915_private*) ; 
 int /*<<< orphan*/  cnl_display_core_uninit (struct drm_i915_private*) ; 
 TYPE_1__ i915_modparams ; 
 int /*<<< orphan*/  icl_display_core_uninit (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_display_power_put (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skl_display_core_uninit (struct drm_i915_private*) ; 

void intel_power_domains_suspend(struct drm_i915_private *dev_priv)
{
	/*
	 * Even if power well support was disabled we still want to disable
	 * power wells while we are system suspended.
	 */
	if (!i915_modparams.disable_power_well)
		intel_display_power_put(dev_priv, POWER_DOMAIN_INIT);

	if (IS_ICELAKE(dev_priv))
		icl_display_core_uninit(dev_priv);
	else if (IS_CANNONLAKE(dev_priv))
		cnl_display_core_uninit(dev_priv);
	else if (IS_GEN9_BC(dev_priv))
		skl_display_core_uninit(dev_priv);
	else if (IS_GEN9_LP(dev_priv))
		bxt_display_core_uninit(dev_priv);
}