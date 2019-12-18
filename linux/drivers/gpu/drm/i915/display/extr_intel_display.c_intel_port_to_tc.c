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
typedef  enum tc_port { ____Placeholder_tc_port } tc_port ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 int PORT_C ; 
 int PORT_D ; 
 int PORT_TC_NONE ; 
 int /*<<< orphan*/  intel_phy_is_tc (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_port_to_phy (struct drm_i915_private*,int) ; 

enum tc_port intel_port_to_tc(struct drm_i915_private *dev_priv, enum port port)
{
	if (!intel_phy_is_tc(dev_priv, intel_port_to_phy(dev_priv, port)))
		return PORT_TC_NONE;

	if (INTEL_GEN(dev_priv) >= 12)
		return port - PORT_D;

	return port - PORT_C;
}