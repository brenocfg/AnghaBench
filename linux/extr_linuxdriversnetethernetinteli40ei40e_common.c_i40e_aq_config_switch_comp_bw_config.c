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
typedef  int /*<<< orphan*/  u16 ;
struct i40e_hw {int dummy; } ;
struct i40e_asq_cmd_details {int dummy; } ;
struct i40e_aqc_configure_switching_comp_bw_config_data {int dummy; } ;
typedef  int /*<<< orphan*/  i40e_status ;

/* Variables and functions */
 int /*<<< orphan*/  i40e_aq_tx_sched_cmd (struct i40e_hw*,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,struct i40e_asq_cmd_details*) ; 
 int /*<<< orphan*/  i40e_aqc_opc_configure_switching_comp_bw_config ; 

i40e_status i40e_aq_config_switch_comp_bw_config(struct i40e_hw *hw,
	u16 seid,
	struct i40e_aqc_configure_switching_comp_bw_config_data *bw_data,
	struct i40e_asq_cmd_details *cmd_details)
{
	return i40e_aq_tx_sched_cmd(hw, seid, (void *)bw_data, sizeof(*bw_data),
			    i40e_aqc_opc_configure_switching_comp_bw_config,
			    cmd_details);
}