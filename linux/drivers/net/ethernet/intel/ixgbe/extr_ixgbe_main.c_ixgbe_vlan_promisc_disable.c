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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ type; scalar_t__ vft_size; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
struct ixgbe_adapter {int flags; int flags2; struct ixgbe_hw hw; } ;

/* Variables and functions */
 int IXGBE_FLAG2_VLAN_PROMISC ; 
 int IXGBE_FLAG_VMDQ_ENABLED ; 
 scalar_t__ IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_VLNCTRL ; 
 scalar_t__ IXGBE_VLNCTRL_VFE ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ VFTA_BLOCK_SIZE ; 
 scalar_t__ ixgbe_mac_82598EB ; 
 int /*<<< orphan*/  ixgbe_scrub_vfta (struct ixgbe_adapter*,scalar_t__) ; 

__attribute__((used)) static void ixgbe_vlan_promisc_disable(struct ixgbe_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	u32 vlnctrl, i;

	/* Set VLAN filtering to enabled */
	vlnctrl = IXGBE_READ_REG(hw, IXGBE_VLNCTRL);
	vlnctrl |= IXGBE_VLNCTRL_VFE;
	IXGBE_WRITE_REG(hw, IXGBE_VLNCTRL, vlnctrl);

	if (!(adapter->flags & IXGBE_FLAG_VMDQ_ENABLED) ||
	    hw->mac.type == ixgbe_mac_82598EB)
		return;

	/* We are not in VLAN promisc, nothing to do */
	if (!(adapter->flags2 & IXGBE_FLAG2_VLAN_PROMISC))
		return;

	/* Set flag so we don't redo unnecessary work */
	adapter->flags2 &= ~IXGBE_FLAG2_VLAN_PROMISC;

	for (i = 0; i < hw->mac.vft_size; i += VFTA_BLOCK_SIZE)
		ixgbe_scrub_vfta(adapter, i);
}