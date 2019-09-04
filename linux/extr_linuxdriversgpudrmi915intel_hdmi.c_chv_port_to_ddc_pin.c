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
 int /*<<< orphan*/  GMBUS_PIN_DPB ; 
 int /*<<< orphan*/  GMBUS_PIN_DPC ; 
 int /*<<< orphan*/  GMBUS_PIN_DPD_CHV ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
#define  PORT_B 130 
#define  PORT_C 129 
#define  PORT_D 128 

__attribute__((used)) static u8 chv_port_to_ddc_pin(struct drm_i915_private *dev_priv, enum port port)
{
	u8 ddc_pin;

	switch (port) {
	case PORT_B:
		ddc_pin = GMBUS_PIN_DPB;
		break;
	case PORT_C:
		ddc_pin = GMBUS_PIN_DPC;
		break;
	case PORT_D:
		ddc_pin = GMBUS_PIN_DPD_CHV;
		break;
	default:
		MISSING_CASE(port);
		ddc_pin = GMBUS_PIN_DPB;
		break;
	}
	return ddc_pin;
}