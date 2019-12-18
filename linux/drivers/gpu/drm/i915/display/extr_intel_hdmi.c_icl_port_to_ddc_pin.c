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
typedef  int u8 ;
struct drm_i915_private {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;
typedef  enum phy { ____Placeholder_phy } phy ;

/* Variables and functions */
 int GMBUS_PIN_1_BXT ; 
 int GMBUS_PIN_2_BXT ; 
 int GMBUS_PIN_9_TC1_ICP ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_phy_is_combo (struct drm_i915_private*,int) ; 
 scalar_t__ intel_phy_is_tc (struct drm_i915_private*,int) ; 
 int intel_port_to_phy (struct drm_i915_private*,int) ; 
 int intel_port_to_tc (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  port_name (int) ; 

__attribute__((used)) static u8 icl_port_to_ddc_pin(struct drm_i915_private *dev_priv, enum port port)
{
	enum phy phy = intel_port_to_phy(dev_priv, port);

	if (intel_phy_is_combo(dev_priv, phy))
		return GMBUS_PIN_1_BXT + port;
	else if (intel_phy_is_tc(dev_priv, phy))
		return GMBUS_PIN_9_TC1_ICP + intel_port_to_tc(dev_priv, port);

	WARN(1, "Unknown port:%c\n", port_name(port));
	return GMBUS_PIN_2_BXT;
}