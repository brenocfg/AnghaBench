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
struct i40e_aqc_configure_switching_comp_ets_data {int dummy; } ;
typedef  int /*<<< orphan*/  i40e_status ;
typedef  enum i40e_admin_queue_opc { ____Placeholder_i40e_admin_queue_opc } i40e_admin_queue_opc ;

/* Variables and functions */
 int /*<<< orphan*/  i40e_aq_tx_sched_cmd (struct i40e_hw*,int /*<<< orphan*/ ,void*,int,int,struct i40e_asq_cmd_details*) ; 

i40e_status i40e_aq_config_switch_comp_ets(struct i40e_hw *hw,
		u16 seid,
		struct i40e_aqc_configure_switching_comp_ets_data *ets_data,
		enum i40e_admin_queue_opc opcode,
		struct i40e_asq_cmd_details *cmd_details)
{
	return i40e_aq_tx_sched_cmd(hw, seid, (void *)ets_data,
				    sizeof(*ets_data), opcode, cmd_details);
}