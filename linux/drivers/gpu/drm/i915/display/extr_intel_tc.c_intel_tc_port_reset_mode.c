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
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_1__ base; } ;
struct intel_digital_port {int tc_mode; int /*<<< orphan*/  tc_port_name; TYPE_2__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum tc_port_mode { ____Placeholder_tc_port_mode } tc_port_mode ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icl_tc_phy_connect (struct intel_digital_port*,int) ; 
 int /*<<< orphan*/  icl_tc_phy_disconnect (struct intel_digital_port*) ; 
 int /*<<< orphan*/  intel_aux_power_domain (struct intel_digital_port*) ; 
 int /*<<< orphan*/  intel_display_power_flush_work (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_display_power_is_enabled (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tc_port_mode_name (int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_tc_port_reset_mode(struct intel_digital_port *dig_port,
				     int required_lanes)
{
	struct drm_i915_private *i915 = to_i915(dig_port->base.base.dev);
	enum tc_port_mode old_tc_mode = dig_port->tc_mode;

	intel_display_power_flush_work(i915);
	WARN_ON(intel_display_power_is_enabled(i915,
					       intel_aux_power_domain(dig_port)));

	icl_tc_phy_disconnect(dig_port);
	icl_tc_phy_connect(dig_port, required_lanes);

	DRM_DEBUG_KMS("Port %s: TC port mode reset (%s -> %s)\n",
		      dig_port->tc_port_name,
		      tc_port_mode_name(old_tc_mode),
		      tc_port_mode_name(dig_port->tc_mode));
}