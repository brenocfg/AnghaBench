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
typedef  int i915_reg_t ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
#define  CHICKEN_TRANS_A 136 
#define  CHICKEN_TRANS_B 135 
#define  CHICKEN_TRANS_C 134 
#define  CHICKEN_TRANS_EDP 133 
 int INTEL_GEN (struct drm_i915_private*) ; 
#define  PORT_A 132 
#define  PORT_B 131 
#define  PORT_C 130 
#define  PORT_D 129 
#define  PORT_E 128 
 scalar_t__ WARN_ON (int) ; 

__attribute__((used)) static i915_reg_t
gen9_chicken_trans_reg_by_port(struct drm_i915_private *dev_priv,
			       enum port port)
{
	static const i915_reg_t regs[] = {
		[PORT_A] = CHICKEN_TRANS_EDP,
		[PORT_B] = CHICKEN_TRANS_A,
		[PORT_C] = CHICKEN_TRANS_B,
		[PORT_D] = CHICKEN_TRANS_C,
		[PORT_E] = CHICKEN_TRANS_A,
	};

	WARN_ON(INTEL_GEN(dev_priv) < 9);

	if (WARN_ON(port < PORT_A || port > PORT_E))
		port = PORT_A;

	return regs[port];
}