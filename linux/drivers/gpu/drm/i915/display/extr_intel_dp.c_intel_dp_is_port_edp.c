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
struct drm_i915_private {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 int PORT_A ; 
 int intel_bios_is_port_edp (struct drm_i915_private*,int) ; 

bool intel_dp_is_port_edp(struct drm_i915_private *dev_priv, enum port port)
{
	/*
	 * eDP not supported on g4x. so bail out early just
	 * for a bit extra safety in case the VBT is bonkers.
	 */
	if (INTEL_GEN(dev_priv) < 5)
		return false;

	if (INTEL_GEN(dev_priv) < 9 && port == PORT_A)
		return true;

	return intel_bios_is_port_edp(dev_priv, port);
}