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
typedef  enum hpd_pin { ____Placeholder_hpd_pin } hpd_pin ;

/* Variables and functions */
 int HPD_NONE ; 
 int HPD_PORT_A ; 
 int HPD_PORT_B ; 
 int HPD_PORT_C ; 
 int HPD_PORT_D ; 
 int HPD_PORT_E ; 
 int HPD_PORT_F ; 
 int HPD_PORT_G ; 
 int HPD_PORT_H ; 
 int HPD_PORT_I ; 
 int /*<<< orphan*/  IS_CNL_WITH_PORT_F (struct drm_i915_private*) ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
#define  PORT_A 136 
#define  PORT_B 135 
#define  PORT_C 134 
#define  PORT_D 133 
#define  PORT_E 132 
#define  PORT_F 131 
#define  PORT_G 130 
#define  PORT_H 129 
#define  PORT_I 128 

enum hpd_pin intel_hpd_pin_default(struct drm_i915_private *dev_priv,
				   enum port port)
{
	switch (port) {
	case PORT_A:
		return HPD_PORT_A;
	case PORT_B:
		return HPD_PORT_B;
	case PORT_C:
		return HPD_PORT_C;
	case PORT_D:
		return HPD_PORT_D;
	case PORT_E:
		return HPD_PORT_E;
	case PORT_F:
		if (IS_CNL_WITH_PORT_F(dev_priv))
			return HPD_PORT_E;
		return HPD_PORT_F;
	case PORT_G:
		return HPD_PORT_G;
	case PORT_H:
		return HPD_PORT_H;
	case PORT_I:
		return HPD_PORT_I;
	default:
		MISSING_CASE(port);
		return HPD_NONE;
	}
}