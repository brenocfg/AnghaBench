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
struct i915_power_well {int dummy; } ;
struct i915_power_domains {int /*<<< orphan*/  lock; } ;
struct drm_i915_private {struct i915_power_domains power_domains; } ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int CL_POWER_DOWN_ENABLE ; 
 int CNL_DDI_CLOCK_REG_ACCESS_ON ; 
 int COMP_INIT ; 
 int /*<<< orphan*/  DC_STATE_DISABLE ; 
 int /*<<< orphan*/  GEN8_CHICKEN_DCPR_1 ; 
 int /*<<< orphan*/  HSW_NDE_RSTWRN_OPT ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ICL_DISP_PW_1 ; 
 int /*<<< orphan*/  ICL_PHY_MISC (int) ; 
 int ICL_PHY_MISC_DE_IO_COMP_PWR_DOWN ; 
 int /*<<< orphan*/  ICL_PORT_CL_DW5 (int) ; 
 int /*<<< orphan*/  ICL_PORT_COMP_DW0 (int) ; 
 int PORT_A ; 
 int PORT_B ; 
 int RESET_PCH_HANDSHAKE_ENABLE ; 
 int /*<<< orphan*/  cnl_set_procmon_ref_values (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  gen9_set_dc_state (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icl_dbuf_enable (struct drm_i915_private*) ; 
 int /*<<< orphan*/  icl_init_cdclk (struct drm_i915_private*) ; 
 int /*<<< orphan*/  icl_mbus_init (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_power_well_enable (struct drm_i915_private*,struct i915_power_well*) ; 
 struct i915_power_well* lookup_power_well (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void icl_display_core_init(struct drm_i915_private *dev_priv,
				  bool resume)
{
	struct i915_power_domains *power_domains = &dev_priv->power_domains;
	struct i915_power_well *well;
	enum port port;
	u32 val;

	gen9_set_dc_state(dev_priv, DC_STATE_DISABLE);

	/* 1. Enable PCH reset handshake. */
	val = I915_READ(HSW_NDE_RSTWRN_OPT);
	val |= RESET_PCH_HANDSHAKE_ENABLE;
	I915_WRITE(HSW_NDE_RSTWRN_OPT, val);

	for (port = PORT_A; port <= PORT_B; port++) {
		/* 2. Enable DDI combo PHY comp. */
		val = I915_READ(ICL_PHY_MISC(port));
		val &= ~ICL_PHY_MISC_DE_IO_COMP_PWR_DOWN;
		I915_WRITE(ICL_PHY_MISC(port), val);

		cnl_set_procmon_ref_values(dev_priv, port);

		val = I915_READ(ICL_PORT_COMP_DW0(port));
		val |= COMP_INIT;
		I915_WRITE(ICL_PORT_COMP_DW0(port), val);

		/* 3. Set power down enable. */
		val = I915_READ(ICL_PORT_CL_DW5(port));
		val |= CL_POWER_DOWN_ENABLE;
		I915_WRITE(ICL_PORT_CL_DW5(port), val);
	}

	/*
	 * 4. Enable Power Well 1 (PG1).
	 *    The AUX IO power wells will be enabled on demand.
	 */
	mutex_lock(&power_domains->lock);
	well = lookup_power_well(dev_priv, ICL_DISP_PW_1);
	intel_power_well_enable(dev_priv, well);
	mutex_unlock(&power_domains->lock);

	/* 5. Enable CDCLK. */
	icl_init_cdclk(dev_priv);

	/* 6. Enable DBUF. */
	icl_dbuf_enable(dev_priv);

	/* 7. Setup MBUS. */
	icl_mbus_init(dev_priv);

	/* 8. CHICKEN_DCPR_1 */
	I915_WRITE(GEN8_CHICKEN_DCPR_1, I915_READ(GEN8_CHICKEN_DCPR_1) |
					CNL_DDI_CLOCK_REG_ACCESS_ON);
}