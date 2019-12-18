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
typedef  int u32 ;
struct intel_dp {int dummy; } ;
struct intel_digital_port {scalar_t__ aux_ch; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 scalar_t__ AUX_CH_A ; 
 scalar_t__ HAS_PCH_LPT_H (struct drm_i915_private*) ; 
 struct intel_digital_port* dp_to_dig_port (struct intel_dp*) ; 
 struct drm_i915_private* dp_to_i915 (struct intel_dp*) ; 
 int ilk_get_aux_clock_divider (struct intel_dp*,int) ; 

__attribute__((used)) static u32 hsw_get_aux_clock_divider(struct intel_dp *intel_dp, int index)
{
	struct drm_i915_private *dev_priv = dp_to_i915(intel_dp);
	struct intel_digital_port *dig_port = dp_to_dig_port(intel_dp);

	if (dig_port->aux_ch != AUX_CH_A && HAS_PCH_LPT_H(dev_priv)) {
		/* Workaround for non-ULT HSW */
		switch (index) {
		case 0: return 63;
		case 1: return 72;
		default: return 0;
		}
	}

	return ilk_get_aux_clock_divider(intel_dp, index);
}