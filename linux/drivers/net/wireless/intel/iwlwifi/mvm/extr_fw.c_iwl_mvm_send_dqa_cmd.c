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
typedef  int /*<<< orphan*/  u32 ;
struct iwl_mvm {int dummy; } ;
struct iwl_dqa_enable_cmd {int /*<<< orphan*/  cmd_queue; } ;
typedef  int /*<<< orphan*/  dqa_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_PATH_GROUP ; 
 int /*<<< orphan*/  DQA_ENABLE_CMD ; 
 int /*<<< orphan*/  IWL_DEBUG_FW (struct iwl_mvm*,char*) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,int) ; 
 int /*<<< orphan*/  IWL_MVM_DQA_CMD_QUEUE ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_cmd_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwl_dqa_enable_cmd*) ; 

__attribute__((used)) static int iwl_mvm_send_dqa_cmd(struct iwl_mvm *mvm)
{
	struct iwl_dqa_enable_cmd dqa_cmd = {
		.cmd_queue = cpu_to_le32(IWL_MVM_DQA_CMD_QUEUE),
	};
	u32 cmd_id = iwl_cmd_id(DQA_ENABLE_CMD, DATA_PATH_GROUP, 0);
	int ret;

	ret = iwl_mvm_send_cmd_pdu(mvm, cmd_id, 0, sizeof(dqa_cmd), &dqa_cmd);
	if (ret)
		IWL_ERR(mvm, "Failed to send DQA enabling command: %d\n", ret);
	else
		IWL_DEBUG_FW(mvm, "Working in DQA mode\n");

	return ret;
}