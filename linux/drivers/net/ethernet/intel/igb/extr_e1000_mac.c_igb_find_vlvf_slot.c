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
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ E1000_ERR_NO_SPACE ; 
 int /*<<< orphan*/  E1000_VLVF (scalar_t__) ; 
 scalar_t__ E1000_VLVF_ARRAY_SIZE ; 
 int E1000_VLVF_VLANID_MASK ; 
 int rd32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 igb_find_vlvf_slot(struct e1000_hw *hw, u32 vlan, bool vlvf_bypass)
{
	s32 regindex, first_empty_slot;
	u32 bits;

	/* short cut the special case */
	if (vlan == 0)
		return 0;

	/* if vlvf_bypass is set we don't want to use an empty slot, we
	 * will simply bypass the VLVF if there are no entries present in the
	 * VLVF that contain our VLAN
	 */
	first_empty_slot = vlvf_bypass ? -E1000_ERR_NO_SPACE : 0;

	/* Search for the VLAN id in the VLVF entries. Save off the first empty
	 * slot found along the way.
	 *
	 * pre-decrement loop covering (IXGBE_VLVF_ENTRIES - 1) .. 1
	 */
	for (regindex = E1000_VLVF_ARRAY_SIZE; --regindex > 0;) {
		bits = rd32(E1000_VLVF(regindex)) & E1000_VLVF_VLANID_MASK;
		if (bits == vlan)
			return regindex;
		if (!first_empty_slot && !bits)
			first_empty_slot = regindex;
	}

	return first_empty_slot ? : -E1000_ERR_NO_SPACE;
}