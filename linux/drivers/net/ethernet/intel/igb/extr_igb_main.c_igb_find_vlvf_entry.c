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

/* Variables and functions */
 int /*<<< orphan*/  E1000_VLVF (int) ; 
 int E1000_VLVF_ARRAY_SIZE ; 
 int VLAN_VID_MASK ; 
 int rd32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int igb_find_vlvf_entry(struct e1000_hw *hw, u32 vlan)
{
	u32 vlvf;
	int idx;

	/* short cut the special case */
	if (vlan == 0)
		return 0;

	/* Search for the VLAN id in the VLVF entries */
	for (idx = E1000_VLVF_ARRAY_SIZE; --idx;) {
		vlvf = rd32(E1000_VLVF(idx));
		if ((vlvf & VLAN_VID_MASK) == vlan)
			break;
	}

	return idx;
}