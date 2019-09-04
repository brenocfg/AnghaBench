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
typedef  int u32 ;
struct igb_adapter {int* shadow_vfta; int /*<<< orphan*/  vfs_allocated_count; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* write_vfta ) (struct e1000_hw*,int,int) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct e1000_hw {TYPE_2__ mac; struct igb_adapter* back; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int BIT (int) ; 
 scalar_t__ E1000_ERR_PARAM ; 
 int /*<<< orphan*/  E1000_VLVF (scalar_t__) ; 
 int E1000_VLVF_POOLSEL_MASK ; 
 int E1000_VLVF_POOLSEL_SHIFT ; 
 int E1000_VLVF_VLANID_ENABLE ; 
 scalar_t__ igb_find_vlvf_slot (struct e1000_hw*,int,int) ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*,int,int) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 

s32 igb_vfta_set(struct e1000_hw *hw, u32 vlan, u32 vind,
		 bool vlan_on, bool vlvf_bypass)
{
	struct igb_adapter *adapter = hw->back;
	u32 regidx, vfta_delta, vfta, bits;
	s32 vlvf_index;

	if ((vlan > 4095) || (vind > 7))
		return -E1000_ERR_PARAM;

	/* this is a 2 part operation - first the VFTA, then the
	 * VLVF and VLVFB if VT Mode is set
	 * We don't write the VFTA until we know the VLVF part succeeded.
	 */

	/* Part 1
	 * The VFTA is a bitstring made up of 128 32-bit registers
	 * that enable the particular VLAN id, much like the MTA:
	 *    bits[11-5]: which register
	 *    bits[4-0]:  which bit in the register
	 */
	regidx = vlan / 32;
	vfta_delta = BIT(vlan % 32);
	vfta = adapter->shadow_vfta[regidx];

	/* vfta_delta represents the difference between the current value
	 * of vfta and the value we want in the register.  Since the diff
	 * is an XOR mask we can just update vfta using an XOR.
	 */
	vfta_delta &= vlan_on ? ~vfta : vfta;
	vfta ^= vfta_delta;

	/* Part 2
	 * If VT Mode is set
	 *   Either vlan_on
	 *     make sure the VLAN is in VLVF
	 *     set the vind bit in the matching VLVFB
	 *   Or !vlan_on
	 *     clear the pool bit and possibly the vind
	 */
	if (!adapter->vfs_allocated_count)
		goto vfta_update;

	vlvf_index = igb_find_vlvf_slot(hw, vlan, vlvf_bypass);
	if (vlvf_index < 0) {
		if (vlvf_bypass)
			goto vfta_update;
		return vlvf_index;
	}

	bits = rd32(E1000_VLVF(vlvf_index));

	/* set the pool bit */
	bits |= BIT(E1000_VLVF_POOLSEL_SHIFT + vind);
	if (vlan_on)
		goto vlvf_update;

	/* clear the pool bit */
	bits ^= BIT(E1000_VLVF_POOLSEL_SHIFT + vind);

	if (!(bits & E1000_VLVF_POOLSEL_MASK)) {
		/* Clear VFTA first, then disable VLVF.  Otherwise
		 * we run the risk of stray packets leaking into
		 * the PF via the default pool
		 */
		if (vfta_delta)
			hw->mac.ops.write_vfta(hw, regidx, vfta);

		/* disable VLVF and clear remaining bit from pool */
		wr32(E1000_VLVF(vlvf_index), 0);

		return 0;
	}

	/* If there are still bits set in the VLVFB registers
	 * for the VLAN ID indicated we need to see if the
	 * caller is requesting that we clear the VFTA entry bit.
	 * If the caller has requested that we clear the VFTA
	 * entry bit but there are still pools/VFs using this VLAN
	 * ID entry then ignore the request.  We're not worried
	 * about the case where we're turning the VFTA VLAN ID
	 * entry bit on, only when requested to turn it off as
	 * there may be multiple pools and/or VFs using the
	 * VLAN ID entry.  In that case we cannot clear the
	 * VFTA bit until all pools/VFs using that VLAN ID have also
	 * been cleared.  This will be indicated by "bits" being
	 * zero.
	 */
	vfta_delta = 0;

vlvf_update:
	/* record pool change and enable VLAN ID if not already enabled */
	wr32(E1000_VLVF(vlvf_index), bits | vlan | E1000_VLVF_VLANID_ENABLE);

vfta_update:
	/* bit was set/cleared before we started */
	if (vfta_delta)
		hw->mac.ops.write_vfta(hw, regidx, vfta);

	return 0;
}