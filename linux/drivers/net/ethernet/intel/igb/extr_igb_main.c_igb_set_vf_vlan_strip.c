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
struct igb_adapter {struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_DVMOLR (int) ; 
 int /*<<< orphan*/  E1000_VMOLR (int) ; 
 int /*<<< orphan*/  E1000_VMOLR_STRVLAN ; 
 scalar_t__ e1000_82576 ; 
 scalar_t__ e1000_i350 ; 
 int /*<<< orphan*/  rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void igb_set_vf_vlan_strip(struct igb_adapter *adapter,
					 int vfn, bool enable)
{
	struct e1000_hw *hw = &adapter->hw;
	u32 val, reg;

	if (hw->mac.type < e1000_82576)
		return;

	if (hw->mac.type == e1000_i350)
		reg = E1000_DVMOLR(vfn);
	else
		reg = E1000_VMOLR(vfn);

	val = rd32(reg);
	if (enable)
		val |= E1000_VMOLR_STRVLAN;
	else
		val &= ~(E1000_VMOLR_STRVLAN);
	wr32(reg, val);
}