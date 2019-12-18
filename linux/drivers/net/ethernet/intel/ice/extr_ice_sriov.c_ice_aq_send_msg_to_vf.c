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
typedef  int /*<<< orphan*/  u16 ;
struct ice_sq_cd {int dummy; } ;
struct ice_hw {int /*<<< orphan*/  mailboxq; } ;
struct ice_aqc_pf_vf_msg {void* id; } ;
struct TYPE_2__ {struct ice_aqc_pf_vf_msg virt; } ;
struct ice_aq_desc {int /*<<< orphan*/  flags; void* cookie_low; void* cookie_high; TYPE_1__ params; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_AQ_FLAG_RD ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_fill_dflt_direct_cmd_desc (struct ice_aq_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_mbx_opc_send_msg_to_vf ; 
 int ice_sq_send_cmd (struct ice_hw*,int /*<<< orphan*/ *,struct ice_aq_desc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ice_sq_cd*) ; 

enum ice_status
ice_aq_send_msg_to_vf(struct ice_hw *hw, u16 vfid, u32 v_opcode, u32 v_retval,
		      u8 *msg, u16 msglen, struct ice_sq_cd *cd)
{
	struct ice_aqc_pf_vf_msg *cmd;
	struct ice_aq_desc desc;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_mbx_opc_send_msg_to_vf);

	cmd = &desc.params.virt;
	cmd->id = cpu_to_le32(vfid);

	desc.cookie_high = cpu_to_le32(v_opcode);
	desc.cookie_low = cpu_to_le32(v_retval);

	if (msglen)
		desc.flags |= cpu_to_le16(ICE_AQ_FLAG_RD);

	return ice_sq_send_cmd(hw, &hw->mailboxq, &desc, msg, msglen, cd);
}