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
typedef  int /*<<< orphan*/  u8 ;
struct drm_i915_private {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;
typedef  enum phy { ____Placeholder_phy } phy ;

/* Variables and functions */
 int /*<<< orphan*/  GMBUS_PIN_1_BXT ; 
 int /*<<< orphan*/  GMBUS_PIN_2_BXT ; 
 int /*<<< orphan*/  GMBUS_PIN_9_TC1_ICP ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
#define  PHY_A 130 
#define  PHY_B 129 
#define  PHY_C 128 
 int intel_port_to_phy (struct drm_i915_private*,int) ; 

__attribute__((used)) static u8 mcc_port_to_ddc_pin(struct drm_i915_private *dev_priv, enum port port)
{
	enum phy phy = intel_port_to_phy(dev_priv, port);
	u8 ddc_pin;

	switch (phy) {
	case PHY_A:
		ddc_pin = GMBUS_PIN_1_BXT;
		break;
	case PHY_B:
		ddc_pin = GMBUS_PIN_2_BXT;
		break;
	case PHY_C:
		ddc_pin = GMBUS_PIN_9_TC1_ICP;
		break;
	default:
		MISSING_CASE(phy);
		ddc_pin = GMBUS_PIN_1_BXT;
		break;
	}
	return ddc_pin;
}