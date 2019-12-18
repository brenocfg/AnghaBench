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
struct intel_dp {int want_panel_vdd; } ;
struct drm_i915_private {int /*<<< orphan*/  pps_mutex; } ;
struct TYPE_3__ {int /*<<< orphan*/  port; } ;
struct TYPE_4__ {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_STATE_WARN (int,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* dp_to_dig_port (struct intel_dp*) ; 
 struct drm_i915_private* dp_to_i915 (struct intel_dp*) ; 
 int /*<<< orphan*/  edp_panel_vdd_off_sync (struct intel_dp*) ; 
 int /*<<< orphan*/  edp_panel_vdd_schedule_off (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_is_edp (struct intel_dp*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  port_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void edp_panel_vdd_off(struct intel_dp *intel_dp, bool sync)
{
	struct drm_i915_private *dev_priv = dp_to_i915(intel_dp);

	lockdep_assert_held(&dev_priv->pps_mutex);

	if (!intel_dp_is_edp(intel_dp))
		return;

	I915_STATE_WARN(!intel_dp->want_panel_vdd, "eDP port %c VDD not forced on",
	     port_name(dp_to_dig_port(intel_dp)->base.port));

	intel_dp->want_panel_vdd = false;

	if (sync)
		edp_panel_vdd_off_sync(intel_dp);
	else
		edp_panel_vdd_schedule_off(intel_dp);
}