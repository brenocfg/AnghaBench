#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct iwl_mvm {TYPE_2__* trans; } ;
struct TYPE_4__ {TYPE_1__* cfg; } ;
struct TYPE_3__ {int /*<<< orphan*/  min_txq_size; int /*<<< orphan*/  min_256_ba_txq_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_TX_QUEUES (struct iwl_mvm*,char*,int,...) ; 
 int /*<<< orphan*/  IWL_DEFAULT_QUEUE_SIZE ; 
 int /*<<< orphan*/  IWL_MAX_TID_COUNT ; 
 int /*<<< orphan*/  IWL_MGMT_QUEUE_SIZE ; 
 int /*<<< orphan*/  IWL_MGMT_TID ; 
 int /*<<< orphan*/  SCD_QUEUE_CFG ; 
 int /*<<< orphan*/  TX_QUEUE_CFG_ENABLE_QUEUE ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int iwl_trans_txq_alloc (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 
 int max_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static int iwl_mvm_tvqm_enable_txq(struct iwl_mvm *mvm,
				   u8 sta_id, u8 tid, unsigned int timeout)
{
	int queue, size = max_t(u32, IWL_DEFAULT_QUEUE_SIZE,
				mvm->trans->cfg->min_256_ba_txq_size);

	if (tid == IWL_MAX_TID_COUNT) {
		tid = IWL_MGMT_TID;
		size = max_t(u32, IWL_MGMT_QUEUE_SIZE,
			     mvm->trans->cfg->min_txq_size);
	}
	queue = iwl_trans_txq_alloc(mvm->trans,
				    cpu_to_le16(TX_QUEUE_CFG_ENABLE_QUEUE),
				    sta_id, tid, SCD_QUEUE_CFG, size, timeout);

	if (queue < 0) {
		IWL_DEBUG_TX_QUEUES(mvm,
				    "Failed allocating TXQ for sta %d tid %d, ret: %d\n",
				    sta_id, tid, queue);
		return queue;
	}

	IWL_DEBUG_TX_QUEUES(mvm, "Enabling TXQ #%d for sta %d tid %d\n",
			    queue, sta_id, tid);

	IWL_DEBUG_TX_QUEUES(mvm, "Enabling TXQ #%d\n", queue);

	return queue;
}