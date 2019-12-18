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
struct iwl_scd_txq_cfg_cmd {int scd_queue; int tid; int /*<<< orphan*/  tx_fifo; int /*<<< orphan*/  action; } ;
struct iwl_mvm {TYPE_1__* queue_info; int /*<<< orphan*/  mutex; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_2__ {unsigned long tid_bitmap; int txq_tid; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_TX_QUEUES (struct iwl_mvm*,char*,int,int) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,int,int) ; 
 scalar_t__ IWL_MAX_TID_COUNT ; 
 int /*<<< orphan*/  SCD_CFG_UPDATE_QUEUE_TID ; 
 int /*<<< orphan*/  SCD_QUEUE_CFG ; 
 scalar_t__ WARN (int,char*,int) ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int find_first_bit (unsigned long*,scalar_t__) ; 
 int /*<<< orphan*/ * iwl_mvm_ac_to_tx_fifo ; 
 int /*<<< orphan*/  iwl_mvm_has_new_tx_api (struct iwl_mvm*) ; 
 int iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwl_scd_txq_cfg_cmd*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 size_t* tid_to_mac80211_ac ; 

__attribute__((used)) static void iwl_mvm_change_queue_tid(struct iwl_mvm *mvm, int queue)
{
	struct iwl_scd_txq_cfg_cmd cmd = {
		.scd_queue = queue,
		.action = SCD_CFG_UPDATE_QUEUE_TID,
	};
	int tid;
	unsigned long tid_bitmap;
	int ret;

	lockdep_assert_held(&mvm->mutex);

	if (WARN_ON(iwl_mvm_has_new_tx_api(mvm)))
		return;

	tid_bitmap = mvm->queue_info[queue].tid_bitmap;

	if (WARN(!tid_bitmap, "TXQ %d has no tids assigned to it\n", queue))
		return;

	/* Find any TID for queue */
	tid = find_first_bit(&tid_bitmap, IWL_MAX_TID_COUNT + 1);
	cmd.tid = tid;
	cmd.tx_fifo = iwl_mvm_ac_to_tx_fifo[tid_to_mac80211_ac[tid]];

	ret = iwl_mvm_send_cmd_pdu(mvm, SCD_QUEUE_CFG, 0, sizeof(cmd), &cmd);
	if (ret) {
		IWL_ERR(mvm, "Failed to update owner of TXQ %d (ret=%d)\n",
			queue, ret);
		return;
	}

	mvm->queue_info[queue].txq_tid = tid;
	IWL_DEBUG_TX_QUEUES(mvm, "Changed TXQ %d ownership to tid %d\n",
			    queue, tid);
}