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
struct intel_dp {int dummy; } ;
struct drm_i915_private {int /*<<< orphan*/  pps_mutex; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _pp_ctrl_reg (struct intel_dp*) ; 
 int /*<<< orphan*/  _pp_stat_reg (struct intel_dp*) ; 
 struct drm_i915_private* dp_to_i915 (struct intel_dp*) ; 
 scalar_t__ intel_de_wait_for_register (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intel_pps_verify_state (struct intel_dp*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wait_panel_status(struct intel_dp *intel_dp,
				       u32 mask,
				       u32 value)
{
	struct drm_i915_private *dev_priv = dp_to_i915(intel_dp);
	i915_reg_t pp_stat_reg, pp_ctrl_reg;

	lockdep_assert_held(&dev_priv->pps_mutex);

	intel_pps_verify_state(intel_dp);

	pp_stat_reg = _pp_stat_reg(intel_dp);
	pp_ctrl_reg = _pp_ctrl_reg(intel_dp);

	DRM_DEBUG_KMS("mask %08x value %08x status %08x control %08x\n",
			mask, value,
			I915_READ(pp_stat_reg),
			I915_READ(pp_ctrl_reg));

	if (intel_de_wait_for_register(dev_priv, pp_stat_reg,
				       mask, value, 5000))
		DRM_ERROR("Panel status timeout: status %08x control %08x\n",
				I915_READ(pp_stat_reg),
				I915_READ(pp_ctrl_reg));

	DRM_DEBUG_KMS("Wait complete\n");
}