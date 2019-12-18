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
typedef  int u32 ;
struct pps_registers {int /*<<< orphan*/  pp_ctrl; int /*<<< orphan*/  pp_div; int /*<<< orphan*/  pp_off; int /*<<< orphan*/  pp_on; } ;
struct edp_power_seq {int t1_t3; int t8; int t9; int t10; int /*<<< orphan*/  t11_t12; } ;
struct intel_dp {struct edp_power_seq pps_delays; } ;
struct drm_i915_private {int rawclk_freq; int /*<<< orphan*/  pps_mutex; } ;
typedef  enum port { ____Placeholder_port } port ;
struct TYPE_3__ {int port; } ;
struct TYPE_4__ {TYPE_1__ base; } ;

/* Variables and functions */
 int BXT_POWER_CYCLE_DELAY_MASK ; 
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int EDP_FORCE_VDD ; 
 scalar_t__ HAS_PCH_CPT (struct drm_i915_private*) ; 
 scalar_t__ HAS_PCH_IBX (struct drm_i915_private*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 int PANEL_LIGHT_OFF_DELAY_MASK ; 
 int PANEL_LIGHT_ON_DELAY_MASK ; 
 int PANEL_PORT_SELECT_DPA ; 
 int PANEL_PORT_SELECT_DPC ; 
 int PANEL_PORT_SELECT_DPD ; 
 int PANEL_PORT_SELECT_VLV (int) ; 
 int PANEL_POWER_CYCLE_DELAY_MASK ; 
 int PANEL_POWER_DOWN_DELAY_MASK ; 
 int PANEL_POWER_ON ; 
 int PANEL_POWER_UP_DELAY_MASK ; 
#define  PORT_A 130 
#define  PORT_C 129 
#define  PORT_D 128 
 int PP_REFERENCE_DIVIDER_MASK ; 
 int REG_FIELD_PREP (int,int) ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 TYPE_2__* dp_to_dig_port (struct intel_dp*) ; 
 struct drm_i915_private* dp_to_i915 (struct intel_dp*) ; 
 scalar_t__ i915_mmio_reg_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_pps_get_registers (struct intel_dp*,struct pps_registers*) ; 
 int ironlake_get_pp_control (struct intel_dp*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
intel_dp_init_panel_power_sequencer_registers(struct intel_dp *intel_dp,
					      bool force_disable_vdd)
{
	struct drm_i915_private *dev_priv = dp_to_i915(intel_dp);
	u32 pp_on, pp_off, port_sel = 0;
	int div = dev_priv->rawclk_freq / 1000;
	struct pps_registers regs;
	enum port port = dp_to_dig_port(intel_dp)->base.port;
	const struct edp_power_seq *seq = &intel_dp->pps_delays;

	lockdep_assert_held(&dev_priv->pps_mutex);

	intel_pps_get_registers(intel_dp, &regs);

	/*
	 * On some VLV machines the BIOS can leave the VDD
	 * enabled even on power sequencers which aren't
	 * hooked up to any port. This would mess up the
	 * power domain tracking the first time we pick
	 * one of these power sequencers for use since
	 * edp_panel_vdd_on() would notice that the VDD was
	 * already on and therefore wouldn't grab the power
	 * domain reference. Disable VDD first to avoid this.
	 * This also avoids spuriously turning the VDD on as
	 * soon as the new power sequencer gets initialized.
	 */
	if (force_disable_vdd) {
		u32 pp = ironlake_get_pp_control(intel_dp);

		WARN(pp & PANEL_POWER_ON, "Panel power already on\n");

		if (pp & EDP_FORCE_VDD)
			DRM_DEBUG_KMS("VDD already on, disabling first\n");

		pp &= ~EDP_FORCE_VDD;

		I915_WRITE(regs.pp_ctrl, pp);
	}

	pp_on = REG_FIELD_PREP(PANEL_POWER_UP_DELAY_MASK, seq->t1_t3) |
		REG_FIELD_PREP(PANEL_LIGHT_ON_DELAY_MASK, seq->t8);
	pp_off = REG_FIELD_PREP(PANEL_LIGHT_OFF_DELAY_MASK, seq->t9) |
		REG_FIELD_PREP(PANEL_POWER_DOWN_DELAY_MASK, seq->t10);

	/* Haswell doesn't have any port selection bits for the panel
	 * power sequencer any more. */
	if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) {
		port_sel = PANEL_PORT_SELECT_VLV(port);
	} else if (HAS_PCH_IBX(dev_priv) || HAS_PCH_CPT(dev_priv)) {
		switch (port) {
		case PORT_A:
			port_sel = PANEL_PORT_SELECT_DPA;
			break;
		case PORT_C:
			port_sel = PANEL_PORT_SELECT_DPC;
			break;
		case PORT_D:
			port_sel = PANEL_PORT_SELECT_DPD;
			break;
		default:
			MISSING_CASE(port);
			break;
		}
	}

	pp_on |= port_sel;

	I915_WRITE(regs.pp_on, pp_on);
	I915_WRITE(regs.pp_off, pp_off);

	/*
	 * Compute the divisor for the pp clock, simply match the Bspec formula.
	 */
	if (i915_mmio_reg_valid(regs.pp_div)) {
		I915_WRITE(regs.pp_div,
			   REG_FIELD_PREP(PP_REFERENCE_DIVIDER_MASK, (100 * div) / 2 - 1) |
			   REG_FIELD_PREP(PANEL_POWER_CYCLE_DELAY_MASK, DIV_ROUND_UP(seq->t11_t12, 1000)));
	} else {
		u32 pp_ctl;

		pp_ctl = I915_READ(regs.pp_ctrl);
		pp_ctl &= ~BXT_POWER_CYCLE_DELAY_MASK;
		pp_ctl |= REG_FIELD_PREP(BXT_POWER_CYCLE_DELAY_MASK, DIV_ROUND_UP(seq->t11_t12, 1000));
		I915_WRITE(regs.pp_ctrl, pp_ctl);
	}

	DRM_DEBUG_KMS("panel power sequencer register settings: PP_ON %#x, PP_OFF %#x, PP_DIV %#x\n",
		      I915_READ(regs.pp_on),
		      I915_READ(regs.pp_off),
		      i915_mmio_reg_valid(regs.pp_div) ?
		      I915_READ(regs.pp_div) :
		      (I915_READ(regs.pp_ctrl) & BXT_POWER_CYCLE_DELAY_MASK));
}