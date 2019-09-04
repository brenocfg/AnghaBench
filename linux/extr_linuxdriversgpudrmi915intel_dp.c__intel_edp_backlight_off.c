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
struct intel_dp {int /*<<< orphan*/  last_backlight_off; } ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 int /*<<< orphan*/  EDP_BLC_ENABLE ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _pp_ctrl_reg (struct intel_dp*) ; 
 int /*<<< orphan*/  edp_wait_backlight_off (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_is_edp (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_to_dev (struct intel_dp*) ; 
 int /*<<< orphan*/  ironlake_get_pp_control (struct intel_dp*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  pps_lock (struct intel_dp*) ; 
 int /*<<< orphan*/  pps_unlock (struct intel_dp*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _intel_edp_backlight_off(struct intel_dp *intel_dp)
{
	struct drm_i915_private *dev_priv = to_i915(intel_dp_to_dev(intel_dp));
	u32 pp;
	i915_reg_t pp_ctrl_reg;

	if (!intel_dp_is_edp(intel_dp))
		return;

	pps_lock(intel_dp);

	pp = ironlake_get_pp_control(intel_dp);
	pp &= ~EDP_BLC_ENABLE;

	pp_ctrl_reg = _pp_ctrl_reg(intel_dp);

	I915_WRITE(pp_ctrl_reg, pp);
	POSTING_READ(pp_ctrl_reg);

	pps_unlock(intel_dp);

	intel_dp->last_backlight_off = jiffies;
	edp_wait_backlight_off(intel_dp);
}