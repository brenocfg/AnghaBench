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
typedef  scalar_t__ u16 ;
struct i40e_hw {int dummy; } ;
struct i40e_asq_cmd_details {int dummy; } ;
struct i40e_aqc_configure_partition_bw_data {int dummy; } ;
struct i40e_aq_desc {int /*<<< orphan*/  datalen; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  i40e_status ;

/* Variables and functions */
 scalar_t__ I40E_AQ_FLAG_BUF ; 
 scalar_t__ I40E_AQ_FLAG_LB ; 
 scalar_t__ I40E_AQ_FLAG_RD ; 
 scalar_t__ I40E_AQ_LARGE_BUF ; 
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  i40e_aqc_opc_configure_partition_bw ; 
 int /*<<< orphan*/  i40e_asq_send_command (struct i40e_hw*,struct i40e_aq_desc*,struct i40e_aqc_configure_partition_bw_data*,scalar_t__,struct i40e_asq_cmd_details*) ; 
 int /*<<< orphan*/  i40e_fill_default_direct_cmd_desc (struct i40e_aq_desc*,int /*<<< orphan*/ ) ; 

i40e_status i40e_aq_configure_partition_bw(struct i40e_hw *hw,
			struct i40e_aqc_configure_partition_bw_data *bw_data,
			struct i40e_asq_cmd_details *cmd_details)
{
	i40e_status status;
	struct i40e_aq_desc desc;
	u16 bwd_size = sizeof(*bw_data);

	i40e_fill_default_direct_cmd_desc(&desc,
					  i40e_aqc_opc_configure_partition_bw);

	/* Indirect command */
	desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_BUF);
	desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_RD);

	if (bwd_size > I40E_AQ_LARGE_BUF)
		desc.flags |= cpu_to_le16((u16)I40E_AQ_FLAG_LB);

	desc.datalen = cpu_to_le16(bwd_size);

	status = i40e_asq_send_command(hw, &desc, bw_data, bwd_size,
				       cmd_details);

	return status;
}