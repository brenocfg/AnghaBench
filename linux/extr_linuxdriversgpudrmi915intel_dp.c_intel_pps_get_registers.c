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
struct pps_registers {int /*<<< orphan*/  pp_div; int /*<<< orphan*/  pp_off; int /*<<< orphan*/  pp_on; int /*<<< orphan*/  pp_stat; int /*<<< orphan*/  pp_ctrl; } ;
struct intel_dp {int dummy; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HAS_PCH_CNP (struct drm_i915_private*) ; 
 int /*<<< orphan*/  HAS_PCH_ICP (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PP_CONTROL (int) ; 
 int /*<<< orphan*/  PP_DIVISOR (int) ; 
 int /*<<< orphan*/  PP_OFF_DELAYS (int) ; 
 int /*<<< orphan*/  PP_ON_DELAYS (int) ; 
 int /*<<< orphan*/  PP_STATUS (int) ; 
 int bxt_power_sequencer_idx (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_to_dev (struct intel_dp*) ; 
 int /*<<< orphan*/  memset (struct pps_registers*,int /*<<< orphan*/ ,int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 int vlv_power_sequencer_pipe (struct intel_dp*) ; 

__attribute__((used)) static void intel_pps_get_registers(struct intel_dp *intel_dp,
				    struct pps_registers *regs)
{
	struct drm_i915_private *dev_priv = to_i915(intel_dp_to_dev(intel_dp));
	int pps_idx = 0;

	memset(regs, 0, sizeof(*regs));

	if (IS_GEN9_LP(dev_priv))
		pps_idx = bxt_power_sequencer_idx(intel_dp);
	else if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		pps_idx = vlv_power_sequencer_pipe(intel_dp);

	regs->pp_ctrl = PP_CONTROL(pps_idx);
	regs->pp_stat = PP_STATUS(pps_idx);
	regs->pp_on = PP_ON_DELAYS(pps_idx);
	regs->pp_off = PP_OFF_DELAYS(pps_idx);
	if (!IS_GEN9_LP(dev_priv) && !HAS_PCH_CNP(dev_priv) &&
	    !HAS_PCH_ICP(dev_priv))
		regs->pp_div = PP_DIVISOR(pps_idx);
}