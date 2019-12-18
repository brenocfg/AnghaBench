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
typedef  int /*<<< orphan*/  u32 ;
struct pps_registers {int /*<<< orphan*/  pp_div; int /*<<< orphan*/  pp_off; int /*<<< orphan*/  pp_on; int /*<<< orphan*/  pp_ctrl; } ;
struct intel_dp {int dummy; } ;
struct edp_power_seq {int t1_t3; int t8; int t9; int t10; int t11_t12; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BXT_POWER_CYCLE_DELAY_MASK ; 
 int /*<<< orphan*/  HAS_DDI (struct drm_i915_private*) ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PANEL_LIGHT_OFF_DELAY_MASK ; 
 int /*<<< orphan*/  PANEL_LIGHT_ON_DELAY_MASK ; 
 int /*<<< orphan*/  PANEL_POWER_CYCLE_DELAY_MASK ; 
 int /*<<< orphan*/  PANEL_POWER_DOWN_DELAY_MASK ; 
 int /*<<< orphan*/  PANEL_POWER_UP_DELAY_MASK ; 
 int REG_FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* dp_to_i915 (struct intel_dp*) ; 
 scalar_t__ i915_mmio_reg_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_pps_get_registers (struct intel_dp*,struct pps_registers*) ; 
 int /*<<< orphan*/  ironlake_get_pp_control (struct intel_dp*) ; 

__attribute__((used)) static void
intel_pps_readout_hw_state(struct intel_dp *intel_dp, struct edp_power_seq *seq)
{
	struct drm_i915_private *dev_priv = dp_to_i915(intel_dp);
	u32 pp_on, pp_off, pp_ctl;
	struct pps_registers regs;

	intel_pps_get_registers(intel_dp, &regs);

	pp_ctl = ironlake_get_pp_control(intel_dp);

	/* Ensure PPS is unlocked */
	if (!HAS_DDI(dev_priv))
		I915_WRITE(regs.pp_ctrl, pp_ctl);

	pp_on = I915_READ(regs.pp_on);
	pp_off = I915_READ(regs.pp_off);

	/* Pull timing values out of registers */
	seq->t1_t3 = REG_FIELD_GET(PANEL_POWER_UP_DELAY_MASK, pp_on);
	seq->t8 = REG_FIELD_GET(PANEL_LIGHT_ON_DELAY_MASK, pp_on);
	seq->t9 = REG_FIELD_GET(PANEL_LIGHT_OFF_DELAY_MASK, pp_off);
	seq->t10 = REG_FIELD_GET(PANEL_POWER_DOWN_DELAY_MASK, pp_off);

	if (i915_mmio_reg_valid(regs.pp_div)) {
		u32 pp_div;

		pp_div = I915_READ(regs.pp_div);

		seq->t11_t12 = REG_FIELD_GET(PANEL_POWER_CYCLE_DELAY_MASK, pp_div) * 1000;
	} else {
		seq->t11_t12 = REG_FIELD_GET(BXT_POWER_CYCLE_DELAY_MASK, pp_ctl) * 1000;
	}
}