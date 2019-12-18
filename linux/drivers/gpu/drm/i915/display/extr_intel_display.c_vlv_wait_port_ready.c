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
typedef  int u32 ;
struct TYPE_2__ {int port; } ;
struct intel_digital_port {TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DPIO_PHY_STATUS ; 
 int /*<<< orphan*/  DPLL (int /*<<< orphan*/ ) ; 
 int DPLL_PORTB_READY_MASK ; 
 int DPLL_PORTC_READY_MASK ; 
 int DPLL_PORTD_READY_MASK ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
#define  PORT_B 130 
#define  PORT_C 129 
#define  PORT_D 128 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ,int,unsigned int) ; 
 scalar_t__ intel_de_wait_for_register (struct drm_i915_private*,int /*<<< orphan*/ ,int,unsigned int,int) ; 
 int /*<<< orphan*/  port_name (int) ; 

void vlv_wait_port_ready(struct drm_i915_private *dev_priv,
			 struct intel_digital_port *dport,
			 unsigned int expected_mask)
{
	u32 port_mask;
	i915_reg_t dpll_reg;

	switch (dport->base.port) {
	case PORT_B:
		port_mask = DPLL_PORTB_READY_MASK;
		dpll_reg = DPLL(0);
		break;
	case PORT_C:
		port_mask = DPLL_PORTC_READY_MASK;
		dpll_reg = DPLL(0);
		expected_mask <<= 4;
		break;
	case PORT_D:
		port_mask = DPLL_PORTD_READY_MASK;
		dpll_reg = DPIO_PHY_STATUS;
		break;
	default:
		BUG();
	}

	if (intel_de_wait_for_register(dev_priv, dpll_reg,
				       port_mask, expected_mask, 1000))
		WARN(1, "timed out waiting for port %c ready: got 0x%x, expected 0x%x\n",
		     port_name(dport->base.port),
		     I915_READ(dpll_reg) & port_mask, expected_mask);
}