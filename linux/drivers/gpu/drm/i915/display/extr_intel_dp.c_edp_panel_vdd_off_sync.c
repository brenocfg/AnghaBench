#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct intel_dp {int /*<<< orphan*/  panel_power_off_time; int /*<<< orphan*/  want_panel_vdd; } ;
struct TYPE_2__ {int /*<<< orphan*/  port; } ;
struct intel_digital_port {TYPE_1__ base; } ;
struct drm_i915_private {int /*<<< orphan*/  pps_mutex; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,...) ; 
 int EDP_FORCE_VDD ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int PANEL_POWER_ON ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _pp_ctrl_reg (struct intel_dp*) ; 
 int /*<<< orphan*/  _pp_stat_reg (struct intel_dp*) ; 
 struct intel_digital_port* dp_to_dig_port (struct intel_dp*) ; 
 struct drm_i915_private* dp_to_i915 (struct intel_dp*) ; 
 int /*<<< orphan*/  edp_have_panel_vdd (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_aux_power_domain (struct intel_digital_port*) ; 
 int /*<<< orphan*/  intel_display_power_put_unchecked (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int ironlake_get_pp_control (struct intel_dp*) ; 
 int /*<<< orphan*/  ktime_get_boottime () ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  port_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void edp_panel_vdd_off_sync(struct intel_dp *intel_dp)
{
	struct drm_i915_private *dev_priv = dp_to_i915(intel_dp);
	struct intel_digital_port *intel_dig_port =
		dp_to_dig_port(intel_dp);
	u32 pp;
	i915_reg_t pp_stat_reg, pp_ctrl_reg;

	lockdep_assert_held(&dev_priv->pps_mutex);

	WARN_ON(intel_dp->want_panel_vdd);

	if (!edp_have_panel_vdd(intel_dp))
		return;

	DRM_DEBUG_KMS("Turning eDP port %c VDD off\n",
		      port_name(intel_dig_port->base.port));

	pp = ironlake_get_pp_control(intel_dp);
	pp &= ~EDP_FORCE_VDD;

	pp_ctrl_reg = _pp_ctrl_reg(intel_dp);
	pp_stat_reg = _pp_stat_reg(intel_dp);

	I915_WRITE(pp_ctrl_reg, pp);
	POSTING_READ(pp_ctrl_reg);

	/* Make sure sequencer is idle before allowing subsequent activity */
	DRM_DEBUG_KMS("PP_STATUS: 0x%08x PP_CONTROL: 0x%08x\n",
	I915_READ(pp_stat_reg), I915_READ(pp_ctrl_reg));

	if ((pp & PANEL_POWER_ON) == 0)
		intel_dp->panel_power_off_time = ktime_get_boottime();

	intel_display_power_put_unchecked(dev_priv,
					  intel_aux_power_domain(intel_dig_port));
}