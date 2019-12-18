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
struct TYPE_2__ {struct ddi_vbt_port_info* ddi_port_info; } ;
struct drm_i915_private {TYPE_1__ vbt; } ;
struct ddi_vbt_port_info {int supports_dvi; int supports_hdmi; int supports_dp; int supports_edp; } ;
typedef  enum port { ____Placeholder_port } port ;
typedef  enum phy { ____Placeholder_phy } phy ;

/* Variables and functions */
 int I915_MAX_PORTS ; 
 int PORT_A ; 
 int PORT_E ; 
 scalar_t__ intel_phy_is_tc (struct drm_i915_private*,int) ; 
 int intel_port_to_phy (struct drm_i915_private*,int) ; 

__attribute__((used)) static void
init_vbt_missing_defaults(struct drm_i915_private *dev_priv)
{
	enum port port;

	for (port = PORT_A; port < I915_MAX_PORTS; port++) {
		struct ddi_vbt_port_info *info =
			&dev_priv->vbt.ddi_port_info[port];
		enum phy phy = intel_port_to_phy(dev_priv, port);

		/*
		 * VBT has the TypeC mode (native,TBT/USB) and we don't want
		 * to detect it.
		 */
		if (intel_phy_is_tc(dev_priv, phy))
			continue;

		info->supports_dvi = (port != PORT_A && port != PORT_E);
		info->supports_hdmi = info->supports_dvi;
		info->supports_dp = (port != PORT_E);
		info->supports_edp = (port == PORT_A);
	}
}