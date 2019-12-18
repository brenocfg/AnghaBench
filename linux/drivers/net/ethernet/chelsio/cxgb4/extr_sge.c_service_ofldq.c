#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct sk_buff {unsigned int priority; int /*<<< orphan*/  destructor; int /*<<< orphan*/  dev; scalar_t__ head; scalar_t__ data; } ;
struct sge_txq {size_t pidx; int size; TYPE_1__* sdesc; int /*<<< orphan*/ * desc; scalar_t__ stat; } ;
struct TYPE_7__ {int /*<<< orphan*/  lock; } ;
struct sge_uld_txq {int service_ofldq_running; struct sge_txq q; TYPE_3__* adap; TYPE_2__ sendq; int /*<<< orphan*/  full; } ;
struct fw_wr_hdr {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_8__ {int /*<<< orphan*/ * port; int /*<<< orphan*/  pdev_dev; } ;
struct TYPE_6__ {struct sk_buff* skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int TXQ_STOP_THRES ; 
 int /*<<< orphan*/  __skb_unlink (struct sk_buff*,TYPE_2__*) ; 
 int /*<<< orphan*/  cxgb4_inline_tx_skb (struct sk_buff*,struct sge_txq*,int /*<<< orphan*/ *) ; 
 scalar_t__ cxgb4_map_skb (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cxgb4_reclaim_completed_tx (TYPE_3__*,struct sge_txq*,int) ; 
 int /*<<< orphan*/  cxgb4_ring_tx_db (TYPE_3__*,struct sge_txq*,unsigned int) ; 
 int /*<<< orphan*/  cxgb4_write_sgl (struct sk_buff*,struct sge_txq*,void*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deferred_unmap_destructor ; 
 unsigned int flits_to_desc (unsigned int) ; 
 scalar_t__ inline_tx_skb_header (struct sk_buff*,struct sge_txq*,void*,int) ; 
 scalar_t__ is_ofld_imm (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ likely (unsigned int) ; 
 int /*<<< orphan*/  ofldtxq_stop (struct sge_uld_txq*,struct fw_wr_hdr*) ; 
 struct sk_buff* skb_peek (TYPE_2__*) ; 
 int skb_transport_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txq_advance (struct sge_txq*,unsigned int) ; 
 unsigned int txq_avail (struct sge_txq*) ; 
 int /*<<< orphan*/  txq_stop_maperr (struct sge_uld_txq*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void service_ofldq(struct sge_uld_txq *q)
{
	u64 *pos, *before, *end;
	int credits;
	struct sk_buff *skb;
	struct sge_txq *txq;
	unsigned int left;
	unsigned int written = 0;
	unsigned int flits, ndesc;

	/* If another thread is currently in service_ofldq() processing the
	 * Pending Send Queue then there's nothing to do. Otherwise, flag
	 * that we're doing the work and continue.  Examining/modifying
	 * the Offload Queue boolean "service_ofldq_running" must be done
	 * while holding the Pending Send Queue Lock.
	 */
	if (q->service_ofldq_running)
		return;
	q->service_ofldq_running = true;

	while ((skb = skb_peek(&q->sendq)) != NULL && !q->full) {
		/* We drop the lock while we're working with the skb at the
		 * head of the Pending Send Queue.  This allows more skbs to
		 * be added to the Pending Send Queue while we're working on
		 * this one.  We don't need to lock to guard the TX Ring
		 * updates because only one thread of execution is ever
		 * allowed into service_ofldq() at a time.
		 */
		spin_unlock(&q->sendq.lock);

		cxgb4_reclaim_completed_tx(q->adap, &q->q, false);

		flits = skb->priority;                /* previously saved */
		ndesc = flits_to_desc(flits);
		credits = txq_avail(&q->q) - ndesc;
		BUG_ON(credits < 0);
		if (unlikely(credits < TXQ_STOP_THRES))
			ofldtxq_stop(q, (struct fw_wr_hdr *)skb->data);

		pos = (u64 *)&q->q.desc[q->q.pidx];
		if (is_ofld_imm(skb))
			cxgb4_inline_tx_skb(skb, &q->q, pos);
		else if (cxgb4_map_skb(q->adap->pdev_dev, skb,
				       (dma_addr_t *)skb->head)) {
			txq_stop_maperr(q);
			spin_lock(&q->sendq.lock);
			break;
		} else {
			int last_desc, hdr_len = skb_transport_offset(skb);

			/* The WR headers  may not fit within one descriptor.
			 * So we need to deal with wrap-around here.
			 */
			before = (u64 *)pos;
			end = (u64 *)pos + flits;
			txq = &q->q;
			pos = (void *)inline_tx_skb_header(skb, &q->q,
							   (void *)pos,
							   hdr_len);
			if (before > (u64 *)pos) {
				left = (u8 *)end - (u8 *)txq->stat;
				end = (void *)txq->desc + left;
			}

			/* If current position is already at the end of the
			 * ofld queue, reset the current to point to
			 * start of the queue and update the end ptr as well.
			 */
			if (pos == (u64 *)txq->stat) {
				left = (u8 *)end - (u8 *)txq->stat;
				end = (void *)txq->desc + left;
				pos = (void *)txq->desc;
			}

			cxgb4_write_sgl(skb, &q->q, (void *)pos,
					end, hdr_len,
					(dma_addr_t *)skb->head);
#ifdef CONFIG_NEED_DMA_MAP_STATE
			skb->dev = q->adap->port[0];
			skb->destructor = deferred_unmap_destructor;
#endif
			last_desc = q->q.pidx + ndesc - 1;
			if (last_desc >= q->q.size)
				last_desc -= q->q.size;
			q->q.sdesc[last_desc].skb = skb;
		}

		txq_advance(&q->q, ndesc);
		written += ndesc;
		if (unlikely(written > 32)) {
			cxgb4_ring_tx_db(q->adap, &q->q, written);
			written = 0;
		}

		/* Reacquire the Pending Send Queue Lock so we can unlink the
		 * skb we've just successfully transferred to the TX Ring and
		 * loop for the next skb which may be at the head of the
		 * Pending Send Queue.
		 */
		spin_lock(&q->sendq.lock);
		__skb_unlink(skb, &q->sendq);
		if (is_ofld_imm(skb))
			kfree_skb(skb);
	}
	if (likely(written))
		cxgb4_ring_tx_db(q->adap, &q->q, written);

	/*Indicate that no thread is processing the Pending Send Queue
	 * currently.
	 */
	q->service_ofldq_running = false;
}