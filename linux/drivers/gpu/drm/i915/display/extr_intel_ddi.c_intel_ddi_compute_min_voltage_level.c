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
struct intel_crtc_state {int port_clock; int min_voltage_level; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_CANNONLAKE (struct drm_i915_private*) ; 

void intel_ddi_compute_min_voltage_level(struct drm_i915_private *dev_priv,
					 struct intel_crtc_state *crtc_state)
{
	if (INTEL_GEN(dev_priv) >= 11 && crtc_state->port_clock > 594000)
		crtc_state->min_voltage_level = 1;
	else if (IS_CANNONLAKE(dev_priv) && crtc_state->port_clock > 594000)
		crtc_state->min_voltage_level = 2;
}