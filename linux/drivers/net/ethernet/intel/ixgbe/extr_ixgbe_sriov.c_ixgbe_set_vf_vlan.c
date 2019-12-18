#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int (* set_vfta ) (struct ixgbe_hw*,int,int /*<<< orphan*/ ,int,int) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ mac; } ;
struct ixgbe_adapter {int flags2; int /*<<< orphan*/  active_vlans; struct ixgbe_hw hw; } ;

/* Variables and functions */
 int IXGBE_FLAG2_VLAN_PROMISC ; 
 int /*<<< orphan*/  VMDQ_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_update_pf_promisc_vlvf (struct ixgbe_adapter*,int) ; 
 int stub1 (struct ixgbe_hw*,int,int /*<<< orphan*/ ,int,int) ; 
 int stub2 (struct ixgbe_hw*,int,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ixgbe_set_vf_vlan(struct ixgbe_adapter *adapter, int add, int vid,
			     u32 vf)
{
	struct ixgbe_hw *hw = &adapter->hw;
	int err;

	/* If VLAN overlaps with one the PF is currently monitoring make
	 * sure that we are able to allocate a VLVF entry.  This may be
	 * redundant but it guarantees PF will maintain visibility to
	 * the VLAN.
	 */
	if (add && test_bit(vid, adapter->active_vlans)) {
		err = hw->mac.ops.set_vfta(hw, vid, VMDQ_P(0), true, false);
		if (err)
			return err;
	}

	err = hw->mac.ops.set_vfta(hw, vid, vf, !!add, false);

	if (add && !err)
		return err;

	/* If we failed to add the VF VLAN or we are removing the VF VLAN
	 * we may need to drop the PF pool bit in order to allow us to free
	 * up the VLVF resources.
	 */
	if (test_bit(vid, adapter->active_vlans) ||
	    (adapter->flags2 & IXGBE_FLAG2_VLAN_PROMISC))
		ixgbe_update_pf_promisc_vlvf(adapter, vid);

	return err;
}