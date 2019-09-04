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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  (* enqueue_tx ) (struct fm10k_hw*,struct fm10k_mbx_info*,int*) ;} ;
struct fm10k_mbx_info {TYPE_1__ ops; } ;
struct fm10k_hw {struct fm10k_mbx_info mbx; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_ERR_PARAM ; 
 int /*<<< orphan*/  FM10K_MAC_VLAN_MSG_VLAN ; 
 int /*<<< orphan*/  FM10K_VF_MSG_ID_MAC_VLAN ; 
 int FM10K_VLAN_CLEAR ; 
 int /*<<< orphan*/  fm10k_tlv_attr_put_u32 (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fm10k_tlv_msg_init (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct fm10k_hw*,struct fm10k_mbx_info*,int*) ; 

__attribute__((used)) static s32 fm10k_update_vlan_vf(struct fm10k_hw *hw, u32 vid, u8 vsi, bool set)
{
	struct fm10k_mbx_info *mbx = &hw->mbx;
	u32 msg[4];

	/* verify the index is not set */
	if (vsi)
		return FM10K_ERR_PARAM;

	/* clever trick to verify reserved bits in both vid and length */
	if ((vid << 16 | vid) >> 28)
		return FM10K_ERR_PARAM;

	/* encode set bit into the VLAN ID */
	if (!set)
		vid |= FM10K_VLAN_CLEAR;

	/* generate VLAN request */
	fm10k_tlv_msg_init(msg, FM10K_VF_MSG_ID_MAC_VLAN);
	fm10k_tlv_attr_put_u32(msg, FM10K_MAC_VLAN_MSG_VLAN, vid);

	/* load onto outgoing mailbox */
	return mbx->ops.enqueue_tx(hw, mbx, msg);
}