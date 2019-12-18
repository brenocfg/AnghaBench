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
struct iwl_tx_path_flush_cmd_v1 {int /*<<< orphan*/  flush_ctl; int /*<<< orphan*/  queues_ctl; } ;
struct iwl_mvm {int dummy; } ;
typedef  int /*<<< orphan*/  flush_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_TX_FIFO_FLUSH ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,int) ; 
 int /*<<< orphan*/  TXPATH_FLUSH ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_has_new_tx_api (struct iwl_mvm*) ; 
 int iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwl_tx_path_flush_cmd_v1*) ; 

int iwl_mvm_flush_tx_path(struct iwl_mvm *mvm, u32 tfd_msk, u32 flags)
{
	int ret;
	struct iwl_tx_path_flush_cmd_v1 flush_cmd = {
		.queues_ctl = cpu_to_le32(tfd_msk),
		.flush_ctl = cpu_to_le16(DUMP_TX_FIFO_FLUSH),
	};

	WARN_ON(iwl_mvm_has_new_tx_api(mvm));

	ret = iwl_mvm_send_cmd_pdu(mvm, TXPATH_FLUSH, flags,
				   sizeof(flush_cmd), &flush_cmd);
	if (ret)
		IWL_ERR(mvm, "Failed to send flush command (%d)\n", ret);
	return ret;
}