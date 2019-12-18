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
struct intel_encoder {int /*<<< orphan*/  hpd_pin; int /*<<< orphan*/  port; TYPE_1__ base; } ;
struct intel_digital_port {int dummy; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum phy { ____Placeholder_phy } phy ;

/* Variables and functions */
 int /*<<< orphan*/  MISSING_CASE (int /*<<< orphan*/ ) ; 
 struct intel_digital_port* enc_to_dig_port (TYPE_1__*) ; 
 int icl_combo_port_connected (struct drm_i915_private*,struct intel_digital_port*) ; 
 scalar_t__ intel_phy_is_combo (struct drm_i915_private*,int) ; 
 scalar_t__ intel_phy_is_tc (struct drm_i915_private*,int) ; 
 int intel_port_to_phy (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int intel_tc_port_connected (struct intel_digital_port*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool icl_digital_port_connected(struct intel_encoder *encoder)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	struct intel_digital_port *dig_port = enc_to_dig_port(&encoder->base);
	enum phy phy = intel_port_to_phy(dev_priv, encoder->port);

	if (intel_phy_is_combo(dev_priv, phy))
		return icl_combo_port_connected(dev_priv, dig_port);
	else if (intel_phy_is_tc(dev_priv, phy))
		return intel_tc_port_connected(dig_port);
	else
		MISSING_CASE(encoder->hpd_pin);

	return false;
}