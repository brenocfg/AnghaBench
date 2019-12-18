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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct sge_txq {size_t in_use; size_t size; size_t pidx; int gen; int /*<<< orphan*/  cntxt_id; int /*<<< orphan*/  lock; int /*<<< orphan*/  stops; int /*<<< orphan*/  sendq; int /*<<< orphan*/ * desc; } ;
struct sge_qset {int /*<<< orphan*/  adap; int /*<<< orphan*/  txq_stopped; struct sge_txq* txq; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_SG_KDOORBELL ; 
 int F_SELEGRCNTX ; 
 size_t TXQ_CTRL ; 
 int V_EGRCNTX (int /*<<< orphan*/ ) ; 
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reclaim_completed_tx_imm (struct sge_txq*) ; 
 int /*<<< orphan*/  set_bit (size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ should_restart_tx (struct sge_txq*) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t3_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_and_clear_bit (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  write_imm (int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void restart_ctrlq(unsigned long data)
{
	struct sk_buff *skb;
	struct sge_qset *qs = (struct sge_qset *)data;
	struct sge_txq *q = &qs->txq[TXQ_CTRL];

	spin_lock(&q->lock);
      again:reclaim_completed_tx_imm(q);

	while (q->in_use < q->size &&
	       (skb = __skb_dequeue(&q->sendq)) != NULL) {

		write_imm(&q->desc[q->pidx], skb, skb->len, q->gen);

		if (++q->pidx >= q->size) {
			q->pidx = 0;
			q->gen ^= 1;
		}
		q->in_use++;
	}

	if (!skb_queue_empty(&q->sendq)) {
		set_bit(TXQ_CTRL, &qs->txq_stopped);
		smp_mb__after_atomic();

		if (should_restart_tx(q) &&
		    test_and_clear_bit(TXQ_CTRL, &qs->txq_stopped))
			goto again;
		q->stops++;
	}

	spin_unlock(&q->lock);
	wmb();
	t3_write_reg(qs->adap, A_SG_KDOORBELL,
		     F_SELEGRCNTX | V_EGRCNTX(q->cntxt_id));
}