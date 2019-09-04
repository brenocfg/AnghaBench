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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct i40e_hw {int dummy; } ;
struct i40e_asq_cmd_details {int dummy; } ;
struct i40e_aqc_debug_reg_read_write {int /*<<< orphan*/  value_low; int /*<<< orphan*/  value_high; int /*<<< orphan*/  address; } ;
struct TYPE_2__ {int /*<<< orphan*/  raw; } ;
struct i40e_aq_desc {TYPE_1__ params; } ;
typedef  int /*<<< orphan*/  i40e_status ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_ERR_PARAM ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_aqc_opc_debug_read_reg ; 
 int /*<<< orphan*/  i40e_asq_send_command (struct i40e_hw*,struct i40e_aq_desc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct i40e_asq_cmd_details*) ; 
 int /*<<< orphan*/  i40e_fill_default_direct_cmd_desc (struct i40e_aq_desc*,int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

i40e_status i40e_aq_debug_read_register(struct i40e_hw *hw,
				u32 reg_addr, u64 *reg_val,
				struct i40e_asq_cmd_details *cmd_details)
{
	struct i40e_aq_desc desc;
	struct i40e_aqc_debug_reg_read_write *cmd_resp =
		(struct i40e_aqc_debug_reg_read_write *)&desc.params.raw;
	i40e_status status;

	if (reg_val == NULL)
		return I40E_ERR_PARAM;

	i40e_fill_default_direct_cmd_desc(&desc, i40e_aqc_opc_debug_read_reg);

	cmd_resp->address = cpu_to_le32(reg_addr);

	status = i40e_asq_send_command(hw, &desc, NULL, 0, cmd_details);

	if (!status) {
		*reg_val = ((u64)le32_to_cpu(cmd_resp->value_high) << 32) |
			   (u64)le32_to_cpu(cmd_resp->value_low);
	}

	return status;
}