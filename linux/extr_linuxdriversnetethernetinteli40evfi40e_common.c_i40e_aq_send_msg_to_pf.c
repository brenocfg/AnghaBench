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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct i40e_hw {int dummy; } ;
struct i40e_asq_cmd_details {int async; } ;
struct i40e_aq_desc {int /*<<< orphan*/  datalen; int /*<<< orphan*/  flags; void* cookie_low; void* cookie_high; } ;
typedef  int i40e_status ;
typedef  enum virtchnl_ops { ____Placeholder_virtchnl_ops } virtchnl_ops ;
typedef  int /*<<< orphan*/  details ;

/* Variables and functions */
 int I40E_AQ_FLAG_BUF ; 
 scalar_t__ I40E_AQ_FLAG_LB ; 
 int I40E_AQ_FLAG_RD ; 
 scalar_t__ I40E_AQ_FLAG_SI ; 
 int /*<<< orphan*/  I40E_AQ_LARGE_BUF ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  i40e_aqc_opc_send_msg_to_pf ; 
 int i40evf_asq_send_command (struct i40e_hw*,struct i40e_aq_desc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct i40e_asq_cmd_details*) ; 
 int /*<<< orphan*/  i40evf_fill_default_direct_cmd_desc (struct i40e_aq_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct i40e_asq_cmd_details*,int /*<<< orphan*/ ,int) ; 

i40e_status i40e_aq_send_msg_to_pf(struct i40e_hw *hw,
				enum virtchnl_ops v_opcode,
				i40e_status v_retval,
				u8 *msg, u16 msglen,
				struct i40e_asq_cmd_details *cmd_details)
{
	struct i40e_aq_desc desc;
	struct i40e_asq_cmd_details details;
	i40e_status status;

	i40evf_fill_default_direct_cmd_desc(&desc, i40e_aqc_opc_send_msg_to_pf);
	desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_SI);
	desc.cookie_high = cpu_to_le32(v_opcode);
	desc.cookie_low = cpu_to_le32(v_retval);
	if (msglen) {
		desc.flags |= cpu_to_le16((u16)(I40E_AQ_FLAG_BUF
						| I40E_AQ_FLAG_RD));
		if (msglen > I40E_AQ_LARGE_BUF)
			desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_LB);
		desc.datalen = cpu_to_le16(msglen);
	}
	if (!cmd_details) {
		memset(&details, 0, sizeof(details));
		details.async = true;
		cmd_details = &details;
	}
	status = i40evf_asq_send_command(hw, &desc, msg, msglen, cmd_details);
	return status;
}