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
struct intel_dp {int want_panel_vdd; int /*<<< orphan*/  aux_power_domain; int /*<<< orphan*/  panel_power_off_time; } ;
struct drm_i915_private {int /*<<< orphan*/  pps_mutex; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;
struct TYPE_3__ {int /*<<< orphan*/  port; } ;
struct TYPE_4__ {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ) ; 
 int EDP_BLC_ENABLE ; 
 int EDP_FORCE_VDD ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int PANEL_POWER_ON ; 
 int PANEL_POWER_RESET ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _pp_ctrl_reg (struct intel_dp*) ; 
 TYPE_2__* dp_to_dig_port (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_display_power_put (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_dp_is_edp (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_to_dev (struct intel_dp*) ; 
 int ironlake_get_pp_control (struct intel_dp*) ; 
 int /*<<< orphan*/  ktime_get_boottime () ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  port_name (int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_panel_off (struct intel_dp*) ; 

__attribute__((used)) static void edp_panel_off(struct intel_dp *intel_dp)
{
	struct drm_i915_private *dev_priv = to_i915(intel_dp_to_dev(intel_dp));
	u32 pp;
	i915_reg_t pp_ctrl_reg;

	lockdep_assert_held(&dev_priv->pps_mutex);

	if (!intel_dp_is_edp(intel_dp))
		return;

	DRM_DEBUG_KMS("Turn eDP port %c panel power off\n",
		      port_name(dp_to_dig_port(intel_dp)->base.port));

	WARN(!intel_dp->want_panel_vdd, "Need eDP port %c VDD to turn off panel\n",
	     port_name(dp_to_dig_port(intel_dp)->base.port));

	pp = ironlake_get_pp_control(intel_dp);
	/* We need to switch off panel power _and_ force vdd, for otherwise some
	 * panels get very unhappy and cease to work. */
	pp &= ~(PANEL_POWER_ON | PANEL_POWER_RESET | EDP_FORCE_VDD |
		EDP_BLC_ENABLE);

	pp_ctrl_reg = _pp_ctrl_reg(intel_dp);

	intel_dp->want_panel_vdd = false;

	I915_WRITE(pp_ctrl_reg, pp);
	POSTING_READ(pp_ctrl_reg);

	wait_panel_off(intel_dp);
	intel_dp->panel_power_off_time = ktime_get_boottime();

	/* We got a reference when we enabled the VDD. */
	intel_display_power_put(dev_priv, intel_dp->aux_power_domain);
}