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
struct sk_buff {int len; void* data; } ;
struct iwl_mvm {int dummy; } ;
struct iwl_host_cmd {int* len; scalar_t__* dataflags; void** data; int /*<<< orphan*/  flags; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEACON_TEMPLATE_CMD ; 
 int /*<<< orphan*/  CMD_ASYNC ; 
 scalar_t__ IWL_HCMD_DFL_DUP ; 
 int iwl_mvm_send_cmd (struct iwl_mvm*,struct iwl_host_cmd*) ; 

int iwl_mvm_mac_ctxt_send_beacon_cmd(struct iwl_mvm *mvm,
				     struct sk_buff *beacon,
				     void *data, int len)
{
	struct iwl_host_cmd cmd = {
		.id = BEACON_TEMPLATE_CMD,
		.flags = CMD_ASYNC,
	};

	cmd.len[0] = len;
	cmd.data[0] = data;
	cmd.dataflags[0] = 0;
	cmd.len[1] = beacon->len;
	cmd.data[1] = beacon->data;
	cmd.dataflags[1] = IWL_HCMD_DFL_DUP;

	return iwl_mvm_send_cmd(mvm, &cmd);
}