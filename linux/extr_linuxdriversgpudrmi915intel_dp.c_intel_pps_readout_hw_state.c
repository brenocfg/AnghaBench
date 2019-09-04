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
struct pps_registers {int /*<<< orphan*/  pp_div; int /*<<< orphan*/  pp_ctrl; int /*<<< orphan*/  pp_off; int /*<<< orphan*/  pp_on; } ;
struct intel_dp {int dummy; } ;
struct edp_power_seq {int t1_t3; int t8; int t9; int t10; int t11_t12; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int BXT_POWER_CYCLE_DELAY_MASK ; 
 int BXT_POWER_CYCLE_DELAY_SHIFT ; 
 scalar_t__ HAS_PCH_CNP (struct drm_i915_private*) ; 
 scalar_t__ HAS_PCH_ICP (struct drm_i915_private*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 int PANEL_LIGHT_OFF_DELAY_MASK ; 
 int PANEL_LIGHT_OFF_DELAY_SHIFT ; 
 int PANEL_LIGHT_ON_DELAY_MASK ; 
 int PANEL_LIGHT_ON_DELAY_SHIFT ; 
 int PANEL_POWER_CYCLE_DELAY_MASK ; 
 int PANEL_POWER_CYCLE_DELAY_SHIFT ; 
 int PANEL_POWER_DOWN_DELAY_MASK ; 
 int PANEL_POWER_DOWN_DELAY_SHIFT ; 
 int PANEL_POWER_UP_DELAY_MASK ; 
 int PANEL_POWER_UP_DELAY_SHIFT ; 
 int /*<<< orphan*/  intel_dp_to_dev (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_pps_get_registers (struct intel_dp*,struct pps_registers*) ; 
 int ironlake_get_pp_control (struct intel_dp*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
intel_pps_readout_hw_state(struct intel_dp *intel_dp, struct edp_power_seq *seq)
{
	struct drm_i915_private *dev_priv = to_i915(intel_dp_to_dev(intel_dp));
	u32 pp_on, pp_off, pp_div = 0, pp_ctl = 0;
	struct pps_registers regs;

	intel_pps_get_registers(intel_dp, &regs);

	/* Workaround: Need to write PP_CONTROL with the unlock key as
	 * the very first thing. */
	pp_ctl = ironlake_get_pp_control(intel_dp);

	pp_on = I915_READ(regs.pp_on);
	pp_off = I915_READ(regs.pp_off);
	if (!IS_GEN9_LP(dev_priv) && !HAS_PCH_CNP(dev_priv) &&
	    !HAS_PCH_ICP(dev_priv)) {
		I915_WRITE(regs.pp_ctrl, pp_ctl);
		pp_div = I915_READ(regs.pp_div);
	}

	/* Pull timing values out of registers */
	seq->t1_t3 = (pp_on & PANEL_POWER_UP_DELAY_MASK) >>
		     PANEL_POWER_UP_DELAY_SHIFT;

	seq->t8 = (pp_on & PANEL_LIGHT_ON_DELAY_MASK) >>
		  PANEL_LIGHT_ON_DELAY_SHIFT;

	seq->t9 = (pp_off & PANEL_LIGHT_OFF_DELAY_MASK) >>
		  PANEL_LIGHT_OFF_DELAY_SHIFT;

	seq->t10 = (pp_off & PANEL_POWER_DOWN_DELAY_MASK) >>
		   PANEL_POWER_DOWN_DELAY_SHIFT;

	if (IS_GEN9_LP(dev_priv) || HAS_PCH_CNP(dev_priv) ||
	    HAS_PCH_ICP(dev_priv)) {
		seq->t11_t12 = ((pp_ctl & BXT_POWER_CYCLE_DELAY_MASK) >>
				BXT_POWER_CYCLE_DELAY_SHIFT) * 1000;
	} else {
		seq->t11_t12 = ((pp_div & PANEL_POWER_CYCLE_DELAY_MASK) >>
		       PANEL_POWER_CYCLE_DELAY_SHIFT) * 1000;
	}
}