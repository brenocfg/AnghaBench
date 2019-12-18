#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {scalar_t__ cb; } ;
struct iwl_txq {int high_mark; scalar_t__ write_ptr; scalar_t__ read_ptr; int /*<<< orphan*/  lock; scalar_t__ wd_timeout; int /*<<< orphan*/  stuck_timer; TYPE_2__* entries; int /*<<< orphan*/  overflow_q; } ;
struct iwl_tx_cmd_gen3 {int /*<<< orphan*/  len; } ;
struct iwl_tx_cmd_gen2 {int /*<<< orphan*/  len; } ;
struct iwl_trans_pcie {int dev_cmd_offs; int /*<<< orphan*/  queue_used; struct iwl_txq** txq; } ;
struct iwl_trans {TYPE_3__* trans_cfg; } ;
struct TYPE_5__ {int /*<<< orphan*/  sequence; } ;
struct iwl_device_cmd {scalar_t__ payload; TYPE_1__ hdr; } ;
struct iwl_cmd_meta {scalar_t__ flags; } ;
struct TYPE_8__ {scalar_t__ nr_frags; } ;
struct TYPE_7__ {scalar_t__ device_family; } ;
struct TYPE_6__ {struct iwl_cmd_meta meta; struct iwl_device_cmd* cmd; struct sk_buff* skb; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int INDEX_TO_SEQ (int) ; 
 scalar_t__ IWL_DEVICE_FAMILY_22560 ; 
 scalar_t__ IWL_PCIE_MAX_FRAGS (struct iwl_trans_pcie*) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int QUEUE_TO_SEQ (int) ; 
 scalar_t__ WARN_ONCE (int,char*,int) ; 
 scalar_t__ __skb_linearize (struct sk_buff*) ; 
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* iwl_pcie_gen2_build_tfd (struct iwl_trans*,struct iwl_txq*,struct iwl_device_cmd*,struct sk_buff*,struct iwl_cmd_meta*) ; 
 int /*<<< orphan*/  iwl_pcie_gen2_get_num_tbs (struct iwl_trans*,void*) ; 
 int /*<<< orphan*/  iwl_pcie_gen2_txq_inc_wr_ptr (struct iwl_trans*,struct iwl_txq*) ; 
 int /*<<< orphan*/  iwl_pcie_gen2_update_byte_tbl (struct iwl_trans_pcie*,struct iwl_txq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iwl_pcie_get_cmd_index (struct iwl_txq*,scalar_t__) ; 
 scalar_t__ iwl_queue_inc_wrap (struct iwl_trans*,scalar_t__) ; 
 int iwl_queue_space (struct iwl_trans*,struct iwl_txq*) ; 
 int /*<<< orphan*/  iwl_stop_queue (struct iwl_trans*,struct iwl_txq*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ skb_is_nonlinear (struct sk_buff*) ; 
 TYPE_4__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int iwl_trans_pcie_gen2_tx(struct iwl_trans *trans, struct sk_buff *skb,
			   struct iwl_device_cmd *dev_cmd, int txq_id)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	struct iwl_cmd_meta *out_meta;
	struct iwl_txq *txq = trans_pcie->txq[txq_id];
	u16 cmd_len;
	int idx;
	void *tfd;

	if (WARN_ONCE(!test_bit(txq_id, trans_pcie->queue_used),
		      "TX on unused queue %d\n", txq_id))
		return -EINVAL;

	if (skb_is_nonlinear(skb) &&
	    skb_shinfo(skb)->nr_frags > IWL_PCIE_MAX_FRAGS(trans_pcie) &&
	    __skb_linearize(skb))
		return -ENOMEM;

	spin_lock(&txq->lock);

	if (iwl_queue_space(trans, txq) < txq->high_mark) {
		iwl_stop_queue(trans, txq);

		/* don't put the packet on the ring, if there is no room */
		if (unlikely(iwl_queue_space(trans, txq) < 3)) {
			struct iwl_device_cmd **dev_cmd_ptr;

			dev_cmd_ptr = (void *)((u8 *)skb->cb +
					       trans_pcie->dev_cmd_offs);

			*dev_cmd_ptr = dev_cmd;
			__skb_queue_tail(&txq->overflow_q, skb);
			spin_unlock(&txq->lock);
			return 0;
		}
	}

	idx = iwl_pcie_get_cmd_index(txq, txq->write_ptr);

	/* Set up driver data for this TFD */
	txq->entries[idx].skb = skb;
	txq->entries[idx].cmd = dev_cmd;

	dev_cmd->hdr.sequence =
		cpu_to_le16((u16)(QUEUE_TO_SEQ(txq_id) |
			    INDEX_TO_SEQ(idx)));

	/* Set up first empty entry in queue's array of Tx/cmd buffers */
	out_meta = &txq->entries[idx].meta;
	out_meta->flags = 0;

	tfd = iwl_pcie_gen2_build_tfd(trans, txq, dev_cmd, skb, out_meta);
	if (!tfd) {
		spin_unlock(&txq->lock);
		return -1;
	}

	if (trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_22560) {
		struct iwl_tx_cmd_gen3 *tx_cmd_gen3 =
			(void *)dev_cmd->payload;

		cmd_len = le16_to_cpu(tx_cmd_gen3->len);
	} else {
		struct iwl_tx_cmd_gen2 *tx_cmd_gen2 =
			(void *)dev_cmd->payload;

		cmd_len = le16_to_cpu(tx_cmd_gen2->len);
	}

	/* Set up entry for this TFD in Tx byte-count array */
	iwl_pcie_gen2_update_byte_tbl(trans_pcie, txq, cmd_len,
				      iwl_pcie_gen2_get_num_tbs(trans, tfd));

	/* start timer if queue currently empty */
	if (txq->read_ptr == txq->write_ptr && txq->wd_timeout)
		mod_timer(&txq->stuck_timer, jiffies + txq->wd_timeout);

	/* Tell device the write index *just past* this latest filled TFD */
	txq->write_ptr = iwl_queue_inc_wrap(trans, txq->write_ptr);
	iwl_pcie_gen2_txq_inc_wr_ptr(trans, txq);
	/*
	 * At this point the frame is "transmitted" successfully
	 * and we will get a TX status notification eventually.
	 */
	spin_unlock(&txq->lock);
	return 0;
}