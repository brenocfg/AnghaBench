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
struct i915_power_well {int dummy; } ;
struct i915_power_domains {int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {scalar_t__ dmc_payload; } ;
struct drm_i915_private {TYPE_1__ csr; struct i915_power_domains power_domains; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_STATE_DISABLE ; 
 int /*<<< orphan*/  HAS_PCH_NOP (struct drm_i915_private*) ; 
 int /*<<< orphan*/  SKL_DISP_PW_1 ; 
 int /*<<< orphan*/  SKL_DISP_PW_MISC_IO ; 
 int /*<<< orphan*/  gen9_dbuf_enable (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen9_set_dc_state (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_cdclk_init (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_csr_load_program (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_pch_reset_handshake (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_power_well_enable (struct drm_i915_private*,struct i915_power_well*) ; 
 struct i915_power_well* lookup_power_well (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void skl_display_core_init(struct drm_i915_private *dev_priv,
				  bool resume)
{
	struct i915_power_domains *power_domains = &dev_priv->power_domains;
	struct i915_power_well *well;

	gen9_set_dc_state(dev_priv, DC_STATE_DISABLE);

	/* enable PCH reset handshake */
	intel_pch_reset_handshake(dev_priv, !HAS_PCH_NOP(dev_priv));

	/* enable PG1 and Misc I/O */
	mutex_lock(&power_domains->lock);

	well = lookup_power_well(dev_priv, SKL_DISP_PW_1);
	intel_power_well_enable(dev_priv, well);

	well = lookup_power_well(dev_priv, SKL_DISP_PW_MISC_IO);
	intel_power_well_enable(dev_priv, well);

	mutex_unlock(&power_domains->lock);

	intel_cdclk_init(dev_priv);

	gen9_dbuf_enable(dev_priv);

	if (resume && dev_priv->csr.dmc_payload)
		intel_csr_load_program(dev_priv);
}