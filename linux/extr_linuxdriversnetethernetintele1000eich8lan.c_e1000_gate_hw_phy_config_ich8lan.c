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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_1__ mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_EXTCNF_CTRL_GATE_PHY_CFG ; 
 int /*<<< orphan*/  EXTCNF_CTRL ; 
 scalar_t__ e1000_pch2lan ; 
 int /*<<< orphan*/  er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void e1000_gate_hw_phy_config_ich8lan(struct e1000_hw *hw, bool gate)
{
	u32 extcnf_ctrl;

	if (hw->mac.type < e1000_pch2lan)
		return;

	extcnf_ctrl = er32(EXTCNF_CTRL);

	if (gate)
		extcnf_ctrl |= E1000_EXTCNF_CTRL_GATE_PHY_CFG;
	else
		extcnf_ctrl &= ~E1000_EXTCNF_CTRL_GATE_PHY_CFG;

	ew32(EXTCNF_CTRL, extcnf_ctrl);
}