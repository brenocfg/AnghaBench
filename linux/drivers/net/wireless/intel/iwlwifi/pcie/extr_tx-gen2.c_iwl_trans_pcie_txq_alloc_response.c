#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct iwl_txq {int id; int read_ptr; int write_ptr; } ;
struct iwl_tx_queue_cfg_rsp {int /*<<< orphan*/  write_pointer; int /*<<< orphan*/  queue_number; } ;
struct iwl_trans_pcie {struct iwl_txq** txq; int /*<<< orphan*/  queue_used; } ;
struct iwl_trans {TYPE_2__* trans_cfg; } ;
struct iwl_host_cmd {TYPE_3__* resp_pkt; } ;
struct TYPE_6__ {scalar_t__ data; } ;
struct TYPE_5__ {TYPE_1__* base_params; } ;
struct TYPE_4__ {int max_tfd_queue_size; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct iwl_txq**) ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  IWL_DEBUG_TX_QUEUES (struct iwl_trans*,char*,int) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 
 int /*<<< orphan*/  iwl_free_resp (struct iwl_host_cmd*) ; 
 int /*<<< orphan*/  iwl_pcie_gen2_txq_free_memory (struct iwl_trans*,struct iwl_txq*) ; 
 int iwl_rx_packet_payload_len (TYPE_3__*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_set_bit (int,int /*<<< orphan*/ ) ; 

int iwl_trans_pcie_txq_alloc_response(struct iwl_trans *trans,
				      struct iwl_txq *txq,
				      struct iwl_host_cmd *hcmd)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	struct iwl_tx_queue_cfg_rsp *rsp;
	int ret, qid;
	u32 wr_ptr;

	if (WARN_ON(iwl_rx_packet_payload_len(hcmd->resp_pkt) !=
		    sizeof(*rsp))) {
		ret = -EINVAL;
		goto error_free_resp;
	}

	rsp = (void *)hcmd->resp_pkt->data;
	qid = le16_to_cpu(rsp->queue_number);
	wr_ptr = le16_to_cpu(rsp->write_pointer);

	if (qid >= ARRAY_SIZE(trans_pcie->txq)) {
		WARN_ONCE(1, "queue index %d unsupported", qid);
		ret = -EIO;
		goto error_free_resp;
	}

	if (test_and_set_bit(qid, trans_pcie->queue_used)) {
		WARN_ONCE(1, "queue %d already used", qid);
		ret = -EIO;
		goto error_free_resp;
	}

	txq->id = qid;
	trans_pcie->txq[qid] = txq;
	wr_ptr &= (trans->trans_cfg->base_params->max_tfd_queue_size - 1);

	/* Place first TFD at index corresponding to start sequence number */
	txq->read_ptr = wr_ptr;
	txq->write_ptr = wr_ptr;

	IWL_DEBUG_TX_QUEUES(trans, "Activate queue %d\n", qid);

	iwl_free_resp(hcmd);
	return qid;

error_free_resp:
	iwl_free_resp(hcmd);
	iwl_pcie_gen2_txq_free_memory(trans, txq);
	return ret;
}