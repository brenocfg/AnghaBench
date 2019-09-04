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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int /*<<< orphan*/  (* enqueue_tx ) (struct fm10k_hw*,struct fm10k_mbx_info*,int /*<<< orphan*/ *) ;} ;
struct fm10k_mbx_info {TYPE_1__ ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  const* perm_addr; } ;
struct fm10k_hw {TYPE_2__ mac; struct fm10k_mbx_info mbx; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_ERR_PARAM ; 
 int /*<<< orphan*/  FM10K_MAC_VLAN_MSG_MAC ; 
 int /*<<< orphan*/  FM10K_VF_MSG_ID_MAC_VLAN ; 
 int /*<<< orphan*/  FM10K_VLAN_CLEAR ; 
 int /*<<< orphan*/  FM10K_VLAN_TABLE_VID_MAX ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  fm10k_tlv_attr_put_mac_vlan (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm10k_tlv_msg_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ is_valid_ether_addr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  stub1 (struct fm10k_hw*,struct fm10k_mbx_info*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static s32 fm10k_update_uc_addr_vf(struct fm10k_hw *hw, u16 glort,
				   const u8 *mac, u16 vid, bool add, u8 flags)
{
	struct fm10k_mbx_info *mbx = &hw->mbx;
	u32 msg[7];

	/* verify VLAN ID is valid */
	if (vid >= FM10K_VLAN_TABLE_VID_MAX)
		return FM10K_ERR_PARAM;

	/* verify MAC address is valid */
	if (!is_valid_ether_addr(mac))
		return FM10K_ERR_PARAM;

	/* verify we are not locked down on the MAC address */
	if (is_valid_ether_addr(hw->mac.perm_addr) &&
	    !ether_addr_equal(hw->mac.perm_addr, mac))
		return FM10K_ERR_PARAM;

	/* add bit to notify us if this is a set or clear operation */
	if (!add)
		vid |= FM10K_VLAN_CLEAR;

	/* generate VLAN request */
	fm10k_tlv_msg_init(msg, FM10K_VF_MSG_ID_MAC_VLAN);
	fm10k_tlv_attr_put_mac_vlan(msg, FM10K_MAC_VLAN_MSG_MAC, mac, vid);

	/* load onto outgoing mailbox */
	return mbx->ops.enqueue_tx(hw, mbx, msg);
}