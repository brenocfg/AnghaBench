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
struct e1000_hw {int dummy; } ;
struct igb_adapter {int vfs_allocated_count; int flags; int /*<<< orphan*/  active_vlans; struct e1000_hw hw; } ;
typedef  int s32 ;

/* Variables and functions */
 int IGB_FLAG_VLAN_PROMISC ; 
 int /*<<< orphan*/  igb_update_pf_vlvf (struct igb_adapter*,int) ; 
 int igb_vfta_set (struct e1000_hw*,int,int,int,int) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 igb_set_vf_vlan(struct igb_adapter *adapter, u32 vid,
			   bool add, u32 vf)
{
	int pf_id = adapter->vfs_allocated_count;
	struct e1000_hw *hw = &adapter->hw;
	int err;

	/* If VLAN overlaps with one the PF is currently monitoring make
	 * sure that we are able to allocate a VLVF entry.  This may be
	 * redundant but it guarantees PF will maintain visibility to
	 * the VLAN.
	 */
	if (add && test_bit(vid, adapter->active_vlans)) {
		err = igb_vfta_set(hw, vid, pf_id, true, false);
		if (err)
			return err;
	}

	err = igb_vfta_set(hw, vid, vf, add, false);

	if (add && !err)
		return err;

	/* If we failed to add the VF VLAN or we are removing the VF VLAN
	 * we may need to drop the PF pool bit in order to allow us to free
	 * up the VLVF resources.
	 */
	if (test_bit(vid, adapter->active_vlans) ||
	    (adapter->flags & IGB_FLAG_VLAN_PROMISC))
		igb_update_pf_vlvf(adapter, vid);

	return err;
}