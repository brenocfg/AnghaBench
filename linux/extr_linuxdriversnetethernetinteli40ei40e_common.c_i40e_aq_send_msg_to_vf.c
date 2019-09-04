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
struct i40e_hw {int dummy; } ;
struct i40e_asq_cmd_details {int dummy; } ;
struct i40e_aqc_pf_vf_message {void* id; } ;
struct TYPE_2__ {int /*<<< orphan*/  raw; } ;
struct i40e_aq_desc {int /*<<< orphan*/  datalen; int /*<<< orphan*/  flags; void* cookie_low; void* cookie_high; TYPE_1__ params; } ;
typedef  int /*<<< orphan*/  i40e_status ;

/* Variables and functions */
 int I40E_AQ_FLAG_BUF ; 
 scalar_t__ I40E_AQ_FLAG_LB ; 
 int I40E_AQ_FLAG_RD ; 
 scalar_t__ I40E_AQ_FLAG_SI ; 
 int /*<<< orphan*/  I40E_AQ_LARGE_BUF ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_aqc_opc_send_msg_to_vf ; 
 int /*<<< orphan*/  i40e_asq_send_command (struct i40e_hw*,struct i40e_aq_desc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct i40e_asq_cmd_details*) ; 
 int /*<<< orphan*/  i40e_fill_default_direct_cmd_desc (struct i40e_aq_desc*,int /*<<< orphan*/ ) ; 

i40e_status i40e_aq_send_msg_to_vf(struct i40e_hw *hw, u16 vfid,
				u32 v_opcode, u32 v_retval, u8 *msg, u16 msglen,
				struct i40e_asq_cmd_details *cmd_details)
{
	struct i40e_aq_desc desc;
	struct i40e_aqc_pf_vf_message *cmd =
		(struct i40e_aqc_pf_vf_message *)&desc.params.raw;
	i40e_status status;

	i40e_fill_default_direct_cmd_desc(&desc, i40e_aqc_opc_send_msg_to_vf);
	cmd->id = cpu_to_le32(vfid);
	desc.cookie_high = cpu_to_le32(v_opcode);
	desc.cookie_low = cpu_to_le32(v_retval);
	desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_SI);
	if (msglen) {
		desc.flags |= cpu_to_le16((u16)(I40E_AQ_FLAG_BUF |
						I40E_AQ_FLAG_RD));
		if (msglen > I40E_AQ_LARGE_BUF)
			desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_LB);
		desc.datalen = cpu_to_le16(msglen);
	}
	status = i40e_asq_send_command(hw, &desc, msg, msglen, cmd_details);

	return status;
}