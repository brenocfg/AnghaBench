#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct i915_power_domains {int power_well_count; int /*<<< orphan*/  async_put_work; int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  allowed_dc_mask; } ;
struct drm_i915_private {TYPE_1__ csr; struct i915_power_domains power_domains; } ;
struct TYPE_4__ {int /*<<< orphan*/  enable_dc; int /*<<< orphan*/  disable_power_well; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_BROXTON (struct drm_i915_private*) ; 
 scalar_t__ IS_CANNONLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_CNL_WITH_PORT_F (struct drm_i915_private*) ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 scalar_t__ IS_GEN9_BC (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_I830 (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int POWER_DOMAIN_NUM ; 
 int /*<<< orphan*/  bdw_power_wells ; 
 int /*<<< orphan*/  bxt_power_wells ; 
 int /*<<< orphan*/  chv_power_wells ; 
 int /*<<< orphan*/  cnl_power_wells ; 
 int /*<<< orphan*/  get_allowed_dc_mask (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glk_power_wells ; 
 int /*<<< orphan*/  hsw_power_wells ; 
 int /*<<< orphan*/  i830_power_wells ; 
 TYPE_2__ i915_modparams ; 
 int /*<<< orphan*/  i9xx_always_on_power_well ; 
 int /*<<< orphan*/  icl_power_wells ; 
 int /*<<< orphan*/  intel_display_power_put_async_work ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sanitize_disable_power_well_option (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int set_power_wells (struct i915_power_domains*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skl_power_wells ; 
 int /*<<< orphan*/  tgl_power_wells ; 
 int /*<<< orphan*/  vlv_power_wells ; 

int intel_power_domains_init(struct drm_i915_private *dev_priv)
{
	struct i915_power_domains *power_domains = &dev_priv->power_domains;
	int err;

	i915_modparams.disable_power_well =
		sanitize_disable_power_well_option(dev_priv,
						   i915_modparams.disable_power_well);
	dev_priv->csr.allowed_dc_mask =
		get_allowed_dc_mask(dev_priv, i915_modparams.enable_dc);

	BUILD_BUG_ON(POWER_DOMAIN_NUM > 64);

	mutex_init(&power_domains->lock);

	INIT_DELAYED_WORK(&power_domains->async_put_work,
			  intel_display_power_put_async_work);

	/*
	 * The enabling order will be from lower to higher indexed wells,
	 * the disabling order is reversed.
	 */
	if (IS_GEN(dev_priv, 12)) {
		err = set_power_wells(power_domains, tgl_power_wells);
	} else if (IS_GEN(dev_priv, 11)) {
		err = set_power_wells(power_domains, icl_power_wells);
	} else if (IS_CANNONLAKE(dev_priv)) {
		err = set_power_wells(power_domains, cnl_power_wells);

		/*
		 * DDI and Aux IO are getting enabled for all ports
		 * regardless the presence or use. So, in order to avoid
		 * timeouts, lets remove them from the list
		 * for the SKUs without port F.
		 */
		if (!IS_CNL_WITH_PORT_F(dev_priv))
			power_domains->power_well_count -= 2;
	} else if (IS_GEMINILAKE(dev_priv)) {
		err = set_power_wells(power_domains, glk_power_wells);
	} else if (IS_BROXTON(dev_priv)) {
		err = set_power_wells(power_domains, bxt_power_wells);
	} else if (IS_GEN9_BC(dev_priv)) {
		err = set_power_wells(power_domains, skl_power_wells);
	} else if (IS_CHERRYVIEW(dev_priv)) {
		err = set_power_wells(power_domains, chv_power_wells);
	} else if (IS_BROADWELL(dev_priv)) {
		err = set_power_wells(power_domains, bdw_power_wells);
	} else if (IS_HASWELL(dev_priv)) {
		err = set_power_wells(power_domains, hsw_power_wells);
	} else if (IS_VALLEYVIEW(dev_priv)) {
		err = set_power_wells(power_domains, vlv_power_wells);
	} else if (IS_I830(dev_priv)) {
		err = set_power_wells(power_domains, i830_power_wells);
	} else {
		err = set_power_wells(power_domains, i9xx_always_on_power_well);
	}

	return err;
}