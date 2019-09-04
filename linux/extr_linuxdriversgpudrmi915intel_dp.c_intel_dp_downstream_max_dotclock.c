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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {TYPE_1__ base; } ;
struct intel_dp {int* downstream_ports; int /*<<< orphan*/  dpcd; } ;
struct intel_digital_port {struct intel_encoder base; } ;
struct drm_i915_private {int max_dotclk_freq; } ;

/* Variables and functions */
 int DP_DS_PORT_TYPE_MASK ; 
 int DP_DS_PORT_TYPE_VGA ; 
 struct intel_digital_port* dp_to_dig_port (struct intel_dp*) ; 
 int drm_dp_downstream_max_clock (int /*<<< orphan*/ ,int*) ; 
 int min (int,int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
intel_dp_downstream_max_dotclock(struct intel_dp *intel_dp)
{
	struct intel_digital_port *intel_dig_port = dp_to_dig_port(intel_dp);
	struct intel_encoder *encoder = &intel_dig_port->base;
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	int max_dotclk = dev_priv->max_dotclk_freq;
	int ds_max_dotclk;

	int type = intel_dp->downstream_ports[0] & DP_DS_PORT_TYPE_MASK;

	if (type != DP_DS_PORT_TYPE_VGA)
		return max_dotclk;

	ds_max_dotclk = drm_dp_downstream_max_clock(intel_dp->dpcd,
						    intel_dp->downstream_ports);

	if (ds_max_dotclk != 0)
		max_dotclk = min(max_dotclk, ds_max_dotclk);

	return max_dotclk;
}