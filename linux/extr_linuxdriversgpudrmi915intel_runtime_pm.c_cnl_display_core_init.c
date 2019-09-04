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
typedef  int /*<<< orphan*/  u32 ;
struct i915_power_well {int dummy; } ;
struct i915_power_domains {int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {scalar_t__ dmc_payload; } ;
struct drm_i915_private {TYPE_1__ csr; struct i915_power_domains power_domains; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHICKEN_MISC_2 ; 
 int /*<<< orphan*/  CL_POWER_DOWN_ENABLE ; 
 int /*<<< orphan*/  CNL_COMP_PWR_DOWN ; 
 int /*<<< orphan*/  CNL_PORT_CL1CM_DW5 ; 
 int /*<<< orphan*/  CNL_PORT_COMP_DW0 ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DC_STATE_DISABLE ; 
 int /*<<< orphan*/  HSW_NDE_RSTWRN_OPT ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PORT_A ; 
 int /*<<< orphan*/  RESET_PCH_HANDSHAKE_ENABLE ; 
 int /*<<< orphan*/  SKL_DISP_PW_1 ; 
 int /*<<< orphan*/  cnl_init_cdclk (struct drm_i915_private*) ; 
 int /*<<< orphan*/  cnl_set_procmon_ref_values (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen9_dbuf_enable (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen9_set_dc_state (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_csr_load_program (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_power_well_enable (struct drm_i915_private*,struct i915_power_well*) ; 
 struct i915_power_well* lookup_power_well (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cnl_display_core_init(struct drm_i915_private *dev_priv, bool resume)
{
	struct i915_power_domains *power_domains = &dev_priv->power_domains;
	struct i915_power_well *well;
	u32 val;

	gen9_set_dc_state(dev_priv, DC_STATE_DISABLE);

	/* 1. Enable PCH Reset Handshake */
	val = I915_READ(HSW_NDE_RSTWRN_OPT);
	val |= RESET_PCH_HANDSHAKE_ENABLE;
	I915_WRITE(HSW_NDE_RSTWRN_OPT, val);

	/* 2. Enable Comp */
	val = I915_READ(CHICKEN_MISC_2);
	val &= ~CNL_COMP_PWR_DOWN;
	I915_WRITE(CHICKEN_MISC_2, val);

	/* Dummy PORT_A to get the correct CNL register from the ICL macro */
	cnl_set_procmon_ref_values(dev_priv, PORT_A);

	val = I915_READ(CNL_PORT_COMP_DW0);
	val |= COMP_INIT;
	I915_WRITE(CNL_PORT_COMP_DW0, val);

	/* 3. */
	val = I915_READ(CNL_PORT_CL1CM_DW5);
	val |= CL_POWER_DOWN_ENABLE;
	I915_WRITE(CNL_PORT_CL1CM_DW5, val);

	/*
	 * 4. Enable Power Well 1 (PG1).
	 *    The AUX IO power wells will be enabled on demand.
	 */
	mutex_lock(&power_domains->lock);
	well = lookup_power_well(dev_priv, SKL_DISP_PW_1);
	intel_power_well_enable(dev_priv, well);
	mutex_unlock(&power_domains->lock);

	/* 5. Enable CD clock */
	cnl_init_cdclk(dev_priv);

	/* 6. Enable DBUF */
	gen9_dbuf_enable(dev_priv);

	if (resume && dev_priv->csr.dmc_payload)
		intel_csr_load_program(dev_priv);
}