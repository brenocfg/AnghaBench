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
typedef  int u8 ;
struct i40e_hw {int dummy; } ;
struct i40e_asq_cmd_details {int dummy; } ;
struct i40e_aqc_nvm_update {int command_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  raw; } ;
struct i40e_aq_desc {TYPE_1__ params; } ;
typedef  int /*<<< orphan*/  i40e_status ;

/* Variables and functions */
 int I40E_AQ_NVM_REARRANGE_TO_FLAT ; 
 int I40E_AQ_NVM_REARRANGE_TO_STRUCT ; 
 int /*<<< orphan*/  I40E_ERR_PARAM ; 
 int /*<<< orphan*/  i40e_aqc_opc_nvm_update ; 
 int /*<<< orphan*/  i40e_asq_send_command (struct i40e_hw*,struct i40e_aq_desc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct i40e_asq_cmd_details*) ; 
 int /*<<< orphan*/  i40e_fill_default_direct_cmd_desc (struct i40e_aq_desc*,int /*<<< orphan*/ ) ; 

i40e_status i40e_aq_rearrange_nvm(struct i40e_hw *hw,
				  u8 rearrange_nvm,
				  struct i40e_asq_cmd_details *cmd_details)
{
	struct i40e_aqc_nvm_update *cmd;
	i40e_status status;
	struct i40e_aq_desc desc;

	cmd = (struct i40e_aqc_nvm_update *)&desc.params.raw;

	i40e_fill_default_direct_cmd_desc(&desc, i40e_aqc_opc_nvm_update);

	rearrange_nvm &= (I40E_AQ_NVM_REARRANGE_TO_FLAT |
			 I40E_AQ_NVM_REARRANGE_TO_STRUCT);

	if (!rearrange_nvm) {
		status = I40E_ERR_PARAM;
		goto i40e_aq_rearrange_nvm_exit;
	}

	cmd->command_flags |= rearrange_nvm;
	status = i40e_asq_send_command(hw, &desc, NULL, 0, cmd_details);

i40e_aq_rearrange_nvm_exit:
	return status;
}