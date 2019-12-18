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
typedef  int u32 ;
typedef  int u16 ;
struct fm10k_vf_info {int vf_flags; int /*<<< orphan*/  glort; int /*<<< orphan*/  mac; int /*<<< orphan*/  vsi; scalar_t__ pf_vid; } ;
struct fm10k_mbx_info {int dummy; } ;
struct TYPE_3__ {int (* update_vlan ) (struct fm10k_hw*,int,int /*<<< orphan*/ ,int) ;int (* update_uc_addr ) (struct fm10k_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ;int (* update_mc_addr ) (struct fm10k_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct fm10k_hw {TYPE_2__ mac; } ;
typedef  int s32 ;

/* Variables and functions */
 int ETH_ALEN ; 
 int FM10K_ERR_PARAM ; 
 size_t FM10K_MAC_VLAN_MSG_MAC ; 
 size_t FM10K_MAC_VLAN_MSG_MULTICAST ; 
 size_t FM10K_MAC_VLAN_MSG_VLAN ; 
 int /*<<< orphan*/  FM10K_VF_FLAG_ENABLED (struct fm10k_vf_info*) ; 
 int FM10K_VF_FLAG_MULTI_ENABLED ; 
 int FM10K_VLAN_CLEAR ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int fm10k_iov_select_vid (struct fm10k_vf_info*,int) ; 
 int fm10k_tlv_attr_get_mac_vlan (int*,int /*<<< orphan*/ *,int*) ; 
 int fm10k_tlv_attr_get_u32 (int*,int*) ; 
 scalar_t__ is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int stub1 (struct fm10k_hw*,int,int /*<<< orphan*/ ,int) ; 
 int stub2 (struct fm10k_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int stub3 (struct fm10k_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 

s32 fm10k_iov_msg_mac_vlan_pf(struct fm10k_hw *hw, u32 **results,
			      struct fm10k_mbx_info *mbx)
{
	struct fm10k_vf_info *vf_info = (struct fm10k_vf_info *)mbx;
	u8 mac[ETH_ALEN];
	u32 *result;
	int err = 0;
	bool set;
	u16 vlan;
	u32 vid;

	/* we shouldn't be updating rules on a disabled interface */
	if (!FM10K_VF_FLAG_ENABLED(vf_info))
		err = FM10K_ERR_PARAM;

	if (!err && !!results[FM10K_MAC_VLAN_MSG_VLAN]) {
		result = results[FM10K_MAC_VLAN_MSG_VLAN];

		/* record VLAN id requested */
		err = fm10k_tlv_attr_get_u32(result, &vid);
		if (err)
			return err;

		set = !(vid & FM10K_VLAN_CLEAR);
		vid &= ~FM10K_VLAN_CLEAR;

		/* if the length field has been set, this is a multi-bit
		 * update request. For multi-bit requests, simply disallow
		 * them when the pf_vid has been set. In this case, the PF
		 * should have already cleared the VLAN_TABLE, and if we
		 * allowed them, it could allow a rogue VF to receive traffic
		 * on a VLAN it was not assigned. In the single-bit case, we
		 * need to modify requests for VLAN 0 to use the default PF or
		 * SW vid when assigned.
		 */

		if (vid >> 16) {
			/* prevent multi-bit requests when PF has
			 * administratively set the VLAN for this VF
			 */
			if (vf_info->pf_vid)
				return FM10K_ERR_PARAM;
		} else {
			err = fm10k_iov_select_vid(vf_info, (u16)vid);
			if (err < 0)
				return err;

			vid = err;
		}

		/* update VSI info for VF in regards to VLAN table */
		err = hw->mac.ops.update_vlan(hw, vid, vf_info->vsi, set);
	}

	if (!err && !!results[FM10K_MAC_VLAN_MSG_MAC]) {
		result = results[FM10K_MAC_VLAN_MSG_MAC];

		/* record unicast MAC address requested */
		err = fm10k_tlv_attr_get_mac_vlan(result, mac, &vlan);
		if (err)
			return err;

		/* block attempts to set MAC for a locked device */
		if (is_valid_ether_addr(vf_info->mac) &&
		    !ether_addr_equal(mac, vf_info->mac))
			return FM10K_ERR_PARAM;

		set = !(vlan & FM10K_VLAN_CLEAR);
		vlan &= ~FM10K_VLAN_CLEAR;

		err = fm10k_iov_select_vid(vf_info, vlan);
		if (err < 0)
			return err;

		vlan = (u16)err;

		/* notify switch of request for new unicast address */
		err = hw->mac.ops.update_uc_addr(hw, vf_info->glort,
						 mac, vlan, set, 0);
	}

	if (!err && !!results[FM10K_MAC_VLAN_MSG_MULTICAST]) {
		result = results[FM10K_MAC_VLAN_MSG_MULTICAST];

		/* record multicast MAC address requested */
		err = fm10k_tlv_attr_get_mac_vlan(result, mac, &vlan);
		if (err)
			return err;

		/* verify that the VF is allowed to request multicast */
		if (!(vf_info->vf_flags & FM10K_VF_FLAG_MULTI_ENABLED))
			return FM10K_ERR_PARAM;

		set = !(vlan & FM10K_VLAN_CLEAR);
		vlan &= ~FM10K_VLAN_CLEAR;

		err = fm10k_iov_select_vid(vf_info, vlan);
		if (err < 0)
			return err;

		vlan = (u16)err;

		/* notify switch of request for new multicast address */
		err = hw->mac.ops.update_mc_addr(hw, vf_info->glort,
						 mac, vlan, set);
	}

	return err;
}