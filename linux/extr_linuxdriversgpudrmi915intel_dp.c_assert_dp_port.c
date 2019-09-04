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
struct intel_dp {int /*<<< orphan*/  output_reg; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  port; TYPE_1__ base; } ;
struct intel_digital_port {TYPE_2__ base; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int DP_PORT_EN ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_STATE_WARN (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct intel_digital_port* dp_to_dig_port (struct intel_dp*) ; 
 int /*<<< orphan*/  onoff (int) ; 
 int /*<<< orphan*/  port_name (int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void assert_dp_port(struct intel_dp *intel_dp, bool state)
{
	struct intel_digital_port *dig_port = dp_to_dig_port(intel_dp);
	struct drm_i915_private *dev_priv = to_i915(dig_port->base.base.dev);
	bool cur_state = I915_READ(intel_dp->output_reg) & DP_PORT_EN;

	I915_STATE_WARN(cur_state != state,
			"DP port %c state assertion failure (expected %s, current %s)\n",
			port_name(dig_port->base.port),
			onoff(state), onoff(cur_state));
}