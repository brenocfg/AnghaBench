#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {unsigned int priority; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
struct TYPE_7__ {size_t pidx; unsigned long stops; int /*<<< orphan*/ * desc; } ;
struct sge_ctrl_txq {TYPE_6__ sendq; TYPE_1__ q; int /*<<< orphan*/  adap; scalar_t__ full; } ;
struct fw_wr_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ TXQ_STOP_THRES ; 
 struct sk_buff* __skb_dequeue (TYPE_6__*) ; 
 int /*<<< orphan*/  ctrlq_check_stop (struct sge_ctrl_txq*,struct fw_wr_hdr*) ; 
 int /*<<< orphan*/  cxgb4_inline_tx_skb (struct sk_buff*,TYPE_1__*,struct fw_wr_hdr*) ; 
 int /*<<< orphan*/  cxgb4_ring_tx_db (int /*<<< orphan*/ ,TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  reclaim_completed_tx_imm (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txq_advance (TYPE_1__*,unsigned int) ; 
 scalar_t__ txq_avail (TYPE_1__*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void restart_ctrlq(unsigned long data)
{
	struct sk_buff *skb;
	unsigned int written = 0;
	struct sge_ctrl_txq *q = (struct sge_ctrl_txq *)data;

	spin_lock(&q->sendq.lock);
	reclaim_completed_tx_imm(&q->q);
	BUG_ON(txq_avail(&q->q) < TXQ_STOP_THRES);  /* q should be empty */

	while ((skb = __skb_dequeue(&q->sendq)) != NULL) {
		struct fw_wr_hdr *wr;
		unsigned int ndesc = skb->priority;     /* previously saved */

		written += ndesc;
		/* Write descriptors and free skbs outside the lock to limit
		 * wait times.  q->full is still set so new skbs will be queued.
		 */
		wr = (struct fw_wr_hdr *)&q->q.desc[q->q.pidx];
		txq_advance(&q->q, ndesc);
		spin_unlock(&q->sendq.lock);

		cxgb4_inline_tx_skb(skb, &q->q, wr);
		kfree_skb(skb);

		if (unlikely(txq_avail(&q->q) < TXQ_STOP_THRES)) {
			unsigned long old = q->q.stops;

			ctrlq_check_stop(q, wr);
			if (q->q.stops != old) {          /* suspended anew */
				spin_lock(&q->sendq.lock);
				goto ringdb;
			}
		}
		if (written > 16) {
			cxgb4_ring_tx_db(q->adap, &q->q, written);
			written = 0;
		}
		spin_lock(&q->sendq.lock);
	}
	q->full = 0;
ringdb:
	if (written)
		cxgb4_ring_tx_db(q->adap, &q->q, written);
	spin_unlock(&q->sendq.lock);
}