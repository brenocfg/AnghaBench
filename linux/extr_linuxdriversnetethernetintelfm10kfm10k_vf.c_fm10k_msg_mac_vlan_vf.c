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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct fm10k_mbx_info {int dummy; } ;
struct TYPE_2__ {int default_vid; int vlan_override; int /*<<< orphan*/  perm_addr; } ;
struct fm10k_hw {TYPE_1__ mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int ETH_ALEN ; 
 size_t FM10K_MAC_VLAN_MSG_DEFAULT_MAC ; 
 int FM10K_VLAN_OVERRIDE ; 
 int FM10K_VLAN_TABLE_VID_MAX ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ fm10k_tlv_attr_get_mac_vlan (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 

s32 fm10k_msg_mac_vlan_vf(struct fm10k_hw *hw, u32 **results,
			  struct fm10k_mbx_info *mbx)
{
	u8 perm_addr[ETH_ALEN];
	u16 vid;
	s32 err;

	/* record MAC address requested */
	err = fm10k_tlv_attr_get_mac_vlan(
					results[FM10K_MAC_VLAN_MSG_DEFAULT_MAC],
					perm_addr, &vid);
	if (err)
		return err;

	ether_addr_copy(hw->mac.perm_addr, perm_addr);
	hw->mac.default_vid = vid & (FM10K_VLAN_TABLE_VID_MAX - 1);
	hw->mac.vlan_override = !!(vid & FM10K_VLAN_OVERRIDE);

	return 0;
}