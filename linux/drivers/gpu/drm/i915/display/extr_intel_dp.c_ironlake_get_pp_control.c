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
struct intel_dp {int dummy; } ;
struct drm_i915_private {int /*<<< orphan*/  pps_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  HAS_DDI (struct drm_i915_private*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int PANEL_UNLOCK_MASK ; 
 int PANEL_UNLOCK_REGS ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  _pp_ctrl_reg (struct intel_dp*) ; 
 struct drm_i915_private* dp_to_i915 (struct intel_dp*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static  u32 ironlake_get_pp_control(struct intel_dp *intel_dp)
{
	struct drm_i915_private *dev_priv = dp_to_i915(intel_dp);
	u32 control;

	lockdep_assert_held(&dev_priv->pps_mutex);

	control = I915_READ(_pp_ctrl_reg(intel_dp));
	if (WARN_ON(!HAS_DDI(dev_priv) &&
		    (control & PANEL_UNLOCK_MASK) != PANEL_UNLOCK_REGS)) {
		control &= ~PANEL_UNLOCK_MASK;
		control |= PANEL_UNLOCK_REGS;
	}
	return control;
}