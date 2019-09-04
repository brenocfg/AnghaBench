#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_5__ {int /*<<< orphan*/  (* write_vfta ) (struct e1000_hw*,scalar_t__,unsigned int) ;} ;
struct TYPE_6__ {int type; TYPE_2__ ops; } ;
struct e1000_hw {TYPE_3__ mac; } ;
struct igb_adapter {int flags; scalar_t__ vfs_allocated_count; TYPE_1__* netdev; struct e1000_hw hw; } ;
struct TYPE_4__ {int features; } ;

/* Variables and functions */
 scalar_t__ BIT (scalar_t__) ; 
 scalar_t__ E1000_VLAN_FILTER_TBL_SIZE ; 
 int /*<<< orphan*/  E1000_VLVF (scalar_t__) ; 
 scalar_t__ E1000_VLVF_ARRAY_SIZE ; 
 scalar_t__ E1000_VLVF_POOLSEL_SHIFT ; 
 int IGB_FLAG_VLAN_PROMISC ; 
 int NETIF_F_NTUPLE ; 
#define  e1000_82576 133 
#define  e1000_82580 132 
#define  e1000_i210 131 
#define  e1000_i211 130 
#define  e1000_i350 129 
#define  e1000_i354 128 
 scalar_t__ rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int igb_vlan_promisc_enable(struct igb_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	u32 i, pf_id;

	switch (hw->mac.type) {
	case e1000_i210:
	case e1000_i211:
	case e1000_i350:
		/* VLAN filtering needed for VLAN prio filter */
		if (adapter->netdev->features & NETIF_F_NTUPLE)
			break;
		/* fall through */
	case e1000_82576:
	case e1000_82580:
	case e1000_i354:
		/* VLAN filtering needed for pool filtering */
		if (adapter->vfs_allocated_count)
			break;
		/* fall through */
	default:
		return 1;
	}

	/* We are already in VLAN promisc, nothing to do */
	if (adapter->flags & IGB_FLAG_VLAN_PROMISC)
		return 0;

	if (!adapter->vfs_allocated_count)
		goto set_vfta;

	/* Add PF to all active pools */
	pf_id = adapter->vfs_allocated_count + E1000_VLVF_POOLSEL_SHIFT;

	for (i = E1000_VLVF_ARRAY_SIZE; --i;) {
		u32 vlvf = rd32(E1000_VLVF(i));

		vlvf |= BIT(pf_id);
		wr32(E1000_VLVF(i), vlvf);
	}

set_vfta:
	/* Set all bits in the VLAN filter table array */
	for (i = E1000_VLAN_FILTER_TBL_SIZE; i--;)
		hw->mac.ops.write_vfta(hw, i, ~0U);

	/* Set flag so we don't redo unnecessary work */
	adapter->flags |= IGB_FLAG_VLAN_PROMISC;

	return 0;
}