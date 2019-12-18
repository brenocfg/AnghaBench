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
struct ixgbe_hw {int dummy; } ;

/* Variables and functions */
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_VLVF (int) ; 
 int IXGBE_VLVF_ENTRIES ; 
 int VLAN_VID_MASK ; 

__attribute__((used)) static int ixgbe_find_vlvf_entry(struct ixgbe_hw *hw, u32 vlan)
{
	u32 vlvf;
	int idx;

	/* short cut the special case */
	if (vlan == 0)
		return 0;

	/* Search for the vlan id in the VLVF entries */
	for (idx = IXGBE_VLVF_ENTRIES; --idx;) {
		vlvf = IXGBE_READ_REG(hw, IXGBE_VLVF(idx));
		if ((vlvf & VLAN_VID_MASK) == vlan)
			break;
	}

	return idx;
}