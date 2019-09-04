#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct tx_desc {int dummy; } ;
struct sk_buff {unsigned int priority; int /*<<< orphan*/  len; } ;
struct TYPE_7__ {int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {size_t pidx; int /*<<< orphan*/ * desc; } ;
struct sge_ctrl_txq {int full; TYPE_5__ sendq; TYPE_1__ q; int /*<<< orphan*/  adap; } ;
struct fw_wr_hdr {int dummy; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int NET_XMIT_CN ; 
 int NET_XMIT_DROP ; 
 int NET_XMIT_SUCCESS ; 
 scalar_t__ TXQ_STOP_THRES ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __skb_queue_tail (TYPE_5__*,struct sk_buff*) ; 
 int /*<<< orphan*/  ctrlq_check_stop (struct sge_ctrl_txq*,struct fw_wr_hdr*) ; 
 int /*<<< orphan*/  cxgb4_inline_tx_skb (struct sk_buff*,TYPE_1__*,struct fw_wr_hdr*) ; 
 int /*<<< orphan*/  cxgb4_ring_tx_db (int /*<<< orphan*/ ,TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  is_imm (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txq_advance (TYPE_1__*,unsigned int) ; 
 scalar_t__ txq_avail (TYPE_1__*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ctrl_xmit(struct sge_ctrl_txq *q, struct sk_buff *skb)
{
	unsigned int ndesc;
	struct fw_wr_hdr *wr;

	if (unlikely(!is_imm(skb))) {
		WARN_ON(1);
		dev_kfree_skb(skb);
		return NET_XMIT_DROP;
	}

	ndesc = DIV_ROUND_UP(skb->len, sizeof(struct tx_desc));
	spin_lock(&q->sendq.lock);

	if (unlikely(q->full)) {
		skb->priority = ndesc;                  /* save for restart */
		__skb_queue_tail(&q->sendq, skb);
		spin_unlock(&q->sendq.lock);
		return NET_XMIT_CN;
	}

	wr = (struct fw_wr_hdr *)&q->q.desc[q->q.pidx];
	cxgb4_inline_tx_skb(skb, &q->q, wr);

	txq_advance(&q->q, ndesc);
	if (unlikely(txq_avail(&q->q) < TXQ_STOP_THRES))
		ctrlq_check_stop(q, wr);

	cxgb4_ring_tx_db(q->adap, &q->q, ndesc);
	spin_unlock(&q->sendq.lock);

	kfree_skb(skb);
	return NET_XMIT_SUCCESS;
}