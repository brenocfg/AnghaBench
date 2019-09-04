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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct i40e_hw {int dummy; } ;
struct i40e_asq_cmd_details {int dummy; } ;
struct i40e_aqc_write_personalization_profile {int /*<<< orphan*/  profile_track_id; } ;
struct i40e_aqc_write_ddp_resp {int /*<<< orphan*/  error_info; int /*<<< orphan*/  error_offset; } ;
struct TYPE_2__ {int /*<<< orphan*/  raw; } ;
struct i40e_aq_desc {TYPE_1__ params; int /*<<< orphan*/  datalen; int /*<<< orphan*/  flags; } ;
typedef  int i40e_status ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 int I40E_AQ_FLAG_BUF ; 
 scalar_t__ I40E_AQ_FLAG_LB ; 
 int I40E_AQ_FLAG_RD ; 
 int I40E_AQ_LARGE_BUF ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_aqc_opc_write_personalization_profile ; 
 int i40evf_asq_send_command (struct i40e_hw*,struct i40e_aq_desc*,void*,int,struct i40e_asq_cmd_details*) ; 
 int /*<<< orphan*/  i40evf_fill_default_direct_cmd_desc (struct i40e_aq_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

enum
i40e_status_code i40evf_aq_write_ddp(struct i40e_hw *hw, void *buff,
				     u16 buff_size, u32 track_id,
				     u32 *error_offset, u32 *error_info,
				     struct i40e_asq_cmd_details *cmd_details)
{
	struct i40e_aq_desc desc;
	struct i40e_aqc_write_personalization_profile *cmd =
		(struct i40e_aqc_write_personalization_profile *)
		&desc.params.raw;
	struct i40e_aqc_write_ddp_resp *resp;
	i40e_status status;

	i40evf_fill_default_direct_cmd_desc(&desc,
					    i40e_aqc_opc_write_personalization_profile);

	desc.flags |= cpu_to_le16(I40E_AQ_FLAG_BUF | I40E_AQ_FLAG_RD);
	if (buff_size > I40E_AQ_LARGE_BUF)
		desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_LB);

	desc.datalen = cpu_to_le16(buff_size);

	cmd->profile_track_id = cpu_to_le32(track_id);

	status = i40evf_asq_send_command(hw, &desc, buff, buff_size, cmd_details);
	if (!status) {
		resp = (struct i40e_aqc_write_ddp_resp *)&desc.params.raw;
		if (error_offset)
			*error_offset = le32_to_cpu(resp->error_offset);
		if (error_info)
			*error_info = le32_to_cpu(resp->error_info);
	}

	return status;
}