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
typedef  int /*<<< orphan*/  u32 ;
struct intel_dp {int /*<<< orphan*/  last_power_on; } ;
struct drm_i915_private {int /*<<< orphan*/  pps_mutex; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;
struct TYPE_3__ {int /*<<< orphan*/  port; } ;
struct TYPE_4__ {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  PANEL_POWER_ON ; 
 int /*<<< orphan*/  PANEL_POWER_RESET ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _pp_ctrl_reg (struct intel_dp*) ; 
 TYPE_2__* dp_to_dig_port (struct intel_dp*) ; 
 struct drm_i915_private* dp_to_i915 (struct intel_dp*) ; 
 int /*<<< orphan*/  edp_have_panel_power (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_is_edp (struct intel_dp*) ; 
 int /*<<< orphan*/  ironlake_get_pp_control (struct intel_dp*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  port_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_panel_on (struct intel_dp*) ; 
 int /*<<< orphan*/  wait_panel_power_cycle (struct intel_dp*) ; 

__attribute__((used)) static void edp_panel_on(struct intel_dp *intel_dp)
{
	struct drm_i915_private *dev_priv = dp_to_i915(intel_dp);
	u32 pp;
	i915_reg_t pp_ctrl_reg;

	lockdep_assert_held(&dev_priv->pps_mutex);

	if (!intel_dp_is_edp(intel_dp))
		return;

	DRM_DEBUG_KMS("Turn eDP port %c panel power on\n",
		      port_name(dp_to_dig_port(intel_dp)->base.port));

	if (WARN(edp_have_panel_power(intel_dp),
		 "eDP port %c panel power already on\n",
		 port_name(dp_to_dig_port(intel_dp)->base.port)))
		return;

	wait_panel_power_cycle(intel_dp);

	pp_ctrl_reg = _pp_ctrl_reg(intel_dp);
	pp = ironlake_get_pp_control(intel_dp);
	if (IS_GEN(dev_priv, 5)) {
		/* ILK workaround: disable reset around power sequence */
		pp &= ~PANEL_POWER_RESET;
		I915_WRITE(pp_ctrl_reg, pp);
		POSTING_READ(pp_ctrl_reg);
	}

	pp |= PANEL_POWER_ON;
	if (!IS_GEN(dev_priv, 5))
		pp |= PANEL_POWER_RESET;

	I915_WRITE(pp_ctrl_reg, pp);
	POSTING_READ(pp_ctrl_reg);

	wait_panel_on(intel_dp);
	intel_dp->last_power_on = jiffies;

	if (IS_GEN(dev_priv, 5)) {
		pp |= PANEL_POWER_RESET; /* restore panel reset bit */
		I915_WRITE(pp_ctrl_reg, pp);
		POSTING_READ(pp_ctrl_reg);
	}
}