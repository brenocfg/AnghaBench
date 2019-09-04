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
typedef  int /*<<< orphan*/  u16 ;
struct i40e_hw {int dummy; } ;
struct i40e_asq_cmd_details {int dummy; } ;
struct i40e_aqc_get_applied_profiles {int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  raw; } ;
struct i40e_aq_desc {int /*<<< orphan*/  datalen; int /*<<< orphan*/  flags; TYPE_1__ params; } ;
typedef  int i40e_status ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 scalar_t__ I40E_AQ_FLAG_BUF ; 
 scalar_t__ I40E_AQ_FLAG_LB ; 
 int /*<<< orphan*/  I40E_AQ_LARGE_BUF ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_aqc_opc_get_personalization_profile_list ; 
 int i40e_asq_send_command (struct i40e_hw*,struct i40e_aq_desc*,void*,int /*<<< orphan*/ ,struct i40e_asq_cmd_details*) ; 
 int /*<<< orphan*/  i40e_fill_default_direct_cmd_desc (struct i40e_aq_desc*,int /*<<< orphan*/ ) ; 

enum
i40e_status_code i40e_aq_get_ddp_list(struct i40e_hw *hw, void *buff,
				      u16 buff_size, u8 flags,
				      struct i40e_asq_cmd_details *cmd_details)
{
	struct i40e_aq_desc desc;
	struct i40e_aqc_get_applied_profiles *cmd =
		(struct i40e_aqc_get_applied_profiles *)&desc.params.raw;
	i40e_status status;

	i40e_fill_default_direct_cmd_desc(&desc,
					  i40e_aqc_opc_get_personalization_profile_list);

	desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_BUF);
	if (buff_size > I40E_AQ_LARGE_BUF)
		desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_LB);
	desc.datalen = cpu_to_le16(buff_size);

	cmd->flags = flags;

	status = i40e_asq_send_command(hw, &desc, buff, buff_size, cmd_details);

	return status;
}