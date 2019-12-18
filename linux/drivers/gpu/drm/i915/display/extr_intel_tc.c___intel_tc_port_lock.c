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
struct intel_digital_port {int /*<<< orphan*/  tc_lock_wakeref; int /*<<< orphan*/  tc_link_refcount; int /*<<< orphan*/  tc_lock; TYPE_2__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  intel_wakeref_t ;

/* Variables and functions */
 int /*<<< orphan*/  POWER_DOMAIN_DISPLAY_CORE ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_display_power_get (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_tc_port_needs_reset (struct intel_digital_port*) ; 
 int /*<<< orphan*/  intel_tc_port_reset_mode (struct intel_digital_port*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __intel_tc_port_lock(struct intel_digital_port *dig_port,
				 int required_lanes)
{
	struct drm_i915_private *i915 = to_i915(dig_port->base.base.dev);
	intel_wakeref_t wakeref;

	wakeref = intel_display_power_get(i915, POWER_DOMAIN_DISPLAY_CORE);

	mutex_lock(&dig_port->tc_lock);

	if (!dig_port->tc_link_refcount &&
	    intel_tc_port_needs_reset(dig_port))
		intel_tc_port_reset_mode(dig_port, required_lanes);

	WARN_ON(dig_port->tc_lock_wakeref);
	dig_port->tc_lock_wakeref = wakeref;
}