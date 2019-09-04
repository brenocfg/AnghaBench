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
struct i915_power_domains {int initializing; int /*<<< orphan*/  lock; } ;
struct drm_i915_private {struct i915_power_domains power_domains; } ;
struct TYPE_2__ {int /*<<< orphan*/  disable_power_well; } ;

/* Variables and functions */
 scalar_t__ IS_CANNONLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_BC (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 scalar_t__ IS_ICELAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  POWER_DOMAIN_INIT ; 
 int /*<<< orphan*/  bxt_display_core_init (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  chv_phy_control_init (struct drm_i915_private*) ; 
 int /*<<< orphan*/  cnl_display_core_init (struct drm_i915_private*,int) ; 
 TYPE_1__ i915_modparams ; 
 int /*<<< orphan*/  icl_display_core_init (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_display_power_get (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_display_set_init_power (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_power_domains_sync_hw (struct drm_i915_private*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skl_display_core_init (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  vlv_cmnlane_wa (struct drm_i915_private*) ; 

void intel_power_domains_init_hw(struct drm_i915_private *dev_priv, bool resume)
{
	struct i915_power_domains *power_domains = &dev_priv->power_domains;

	power_domains->initializing = true;

	if (IS_ICELAKE(dev_priv)) {
		icl_display_core_init(dev_priv, resume);
	} else if (IS_CANNONLAKE(dev_priv)) {
		cnl_display_core_init(dev_priv, resume);
	} else if (IS_GEN9_BC(dev_priv)) {
		skl_display_core_init(dev_priv, resume);
	} else if (IS_GEN9_LP(dev_priv)) {
		bxt_display_core_init(dev_priv, resume);
	} else if (IS_CHERRYVIEW(dev_priv)) {
		mutex_lock(&power_domains->lock);
		chv_phy_control_init(dev_priv);
		mutex_unlock(&power_domains->lock);
	} else if (IS_VALLEYVIEW(dev_priv)) {
		mutex_lock(&power_domains->lock);
		vlv_cmnlane_wa(dev_priv);
		mutex_unlock(&power_domains->lock);
	}

	/* For now, we need the power well to be always enabled. */
	intel_display_set_init_power(dev_priv, true);
	/* Disable power support if the user asked so. */
	if (!i915_modparams.disable_power_well)
		intel_display_power_get(dev_priv, POWER_DOMAIN_INIT);
	intel_power_domains_sync_hw(dev_priv);
	power_domains->initializing = false;
}