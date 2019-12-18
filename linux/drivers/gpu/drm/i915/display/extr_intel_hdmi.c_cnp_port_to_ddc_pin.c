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

/* Variables and functions */
 int /*<<< orphan*/  GMBUS_PIN_1_BXT ; 
 int /*<<< orphan*/  GMBUS_PIN_2_BXT ; 
 int /*<<< orphan*/  GMBUS_PIN_3_BXT ; 
 int /*<<< orphan*/  GMBUS_PIN_4_CNP ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
#define  PORT_B 131 
#define  PORT_C 130 
#define  PORT_D 129 
#define  PORT_F 128 

__attribute__((used)) static u8 cnp_port_to_ddc_pin(struct drm_i915_private *dev_priv,
			      enum port port)
{
	u8 ddc_pin;

	switch (port) {
	case PORT_B:
		ddc_pin = GMBUS_PIN_1_BXT;
		break;
	case PORT_C:
		ddc_pin = GMBUS_PIN_2_BXT;
		break;
	case PORT_D:
		ddc_pin = GMBUS_PIN_4_CNP;
		break;
	case PORT_F:
		ddc_pin = GMBUS_PIN_3_BXT;
		break;
	default:
		MISSING_CASE(port);
		ddc_pin = GMBUS_PIN_1_BXT;
		break;
	}
	return ddc_pin;
}