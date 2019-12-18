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
typedef  scalar_t__ u32 ;
struct iwl_trans_pcie {TYPE_1__** txq; int /*<<< orphan*/  queue_used; scalar_t__ scd_base_addr; } ;
struct iwl_trans {int /*<<< orphan*/  status; } ;
struct TYPE_2__ {int frozen; int ampdu; scalar_t__ frozen_expiry_remainder; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (scalar_t__ const*) ; 
 int /*<<< orphan*/  IWL_DEBUG_TX_QUEUES (struct iwl_trans*,char*,int) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 scalar_t__ SCD_TX_STTS_QUEUE_OFFSET (int) ; 
 int /*<<< orphan*/  STATUS_DEVICE_ENABLED ; 
 int /*<<< orphan*/  WARN_ONCE (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  iwl_pcie_txq_unmap (struct iwl_trans*,int) ; 
 int /*<<< orphan*/  iwl_scd_txq_set_inactive (struct iwl_trans*,int) ; 
 int /*<<< orphan*/  iwl_trans_write_mem (struct iwl_trans*,scalar_t__,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void iwl_trans_pcie_txq_disable(struct iwl_trans *trans, int txq_id,
				bool configure_scd)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	u32 stts_addr = trans_pcie->scd_base_addr +
			SCD_TX_STTS_QUEUE_OFFSET(txq_id);
	static const u32 zero_val[4] = {};

	trans_pcie->txq[txq_id]->frozen_expiry_remainder = 0;
	trans_pcie->txq[txq_id]->frozen = false;

	/*
	 * Upon HW Rfkill - we stop the device, and then stop the queues
	 * in the op_mode. Just for the sake of the simplicity of the op_mode,
	 * allow the op_mode to call txq_disable after it already called
	 * stop_device.
	 */
	if (!test_and_clear_bit(txq_id, trans_pcie->queue_used)) {
		WARN_ONCE(test_bit(STATUS_DEVICE_ENABLED, &trans->status),
			  "queue %d not used", txq_id);
		return;
	}

	if (configure_scd) {
		iwl_scd_txq_set_inactive(trans, txq_id);

		iwl_trans_write_mem(trans, stts_addr, (void *)zero_val,
				    ARRAY_SIZE(zero_val));
	}

	iwl_pcie_txq_unmap(trans, txq_id);
	trans_pcie->txq[txq_id]->ampdu = false;

	IWL_DEBUG_TX_QUEUES(trans, "Deactivate queue %d\n", txq_id);
}