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
typedef  int u32 ;
struct ccu_data {int dummy; } ;
struct bcm_clk_gate {int hw_sw_sel_bit; int en_bit; int /*<<< orphan*/  status_bit; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int __ccu_read (struct ccu_data*,int /*<<< orphan*/ ) ; 
 int __ccu_wait_bit (struct ccu_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __ccu_write (struct ccu_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gate_exists (struct bcm_clk_gate*) ; 
 int gate_is_enabled (struct bcm_clk_gate*) ; 
 scalar_t__ gate_is_hw_controllable (struct bcm_clk_gate*) ; 
 int /*<<< orphan*/  gate_is_no_disable (struct bcm_clk_gate*) ; 
 int /*<<< orphan*/  gate_is_sw_controllable (struct bcm_clk_gate*) ; 
 scalar_t__ gate_is_sw_managed (struct bcm_clk_gate*) ; 

__attribute__((used)) static bool
__gate_commit(struct ccu_data *ccu, struct bcm_clk_gate *gate)
{
	u32 reg_val;
	u32 mask;
	bool enabled = false;

	BUG_ON(!gate_exists(gate));
	if (!gate_is_sw_controllable(gate))
		return true;		/* Nothing we can change */

	reg_val = __ccu_read(ccu, gate->offset);

	/* For a hardware/software gate, set which is in control */
	if (gate_is_hw_controllable(gate)) {
		mask = (u32)1 << gate->hw_sw_sel_bit;
		if (gate_is_sw_managed(gate))
			reg_val |= mask;
		else
			reg_val &= ~mask;
	}

	/*
	 * If software is in control, enable or disable the gate.
	 * If hardware is, clear the enabled bit for good measure.
	 * If a software controlled gate can't be disabled, we're
	 * required to write a 0 into the enable bit (but the gate
	 * will be enabled).
	 */
	mask = (u32)1 << gate->en_bit;
	if (gate_is_sw_managed(gate) && (enabled = gate_is_enabled(gate)) &&
			!gate_is_no_disable(gate))
		reg_val |= mask;
	else
		reg_val &= ~mask;

	__ccu_write(ccu, gate->offset, reg_val);

	/* For a hardware controlled gate, we're done */
	if (!gate_is_sw_managed(gate))
		return true;

	/* Otherwise wait for the gate to be in desired state */
	return __ccu_wait_bit(ccu, gate->offset, gate->status_bit, enabled);
}