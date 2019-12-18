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
struct sk_buff {scalar_t__ data; } ;
struct il_queue {int n_bd; int read_ptr; int /*<<< orphan*/  write_ptr; } ;
struct il_tx_queue {struct il_queue q; struct sk_buff** skbs; } ;
struct il_priv {TYPE_1__* ops; struct il_tx_queue* txq; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* txq_free_tfd ) (struct il_priv*,struct il_tx_queue*) ;} ;

/* Variables and functions */
 int IL4965_FIRST_AMPDU_QUEUE ; 
 int /*<<< orphan*/  IL_ERR (char*,int,int,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_data_qos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il4965_tx_status (struct il_priv*,struct sk_buff*,int) ; 
 void* il_queue_inc_wrap (int,int) ; 
 scalar_t__ il_queue_used (struct il_queue*,int) ; 
 int /*<<< orphan*/  stub1 (struct il_priv*,struct il_tx_queue*) ; 

int
il4965_tx_queue_reclaim(struct il_priv *il, int txq_id, int idx)
{
	struct il_tx_queue *txq = &il->txq[txq_id];
	struct il_queue *q = &txq->q;
	int nfreed = 0;
	struct ieee80211_hdr *hdr;
	struct sk_buff *skb;

	if (idx >= q->n_bd || il_queue_used(q, idx) == 0) {
		IL_ERR("Read idx for DMA queue txq id (%d), idx %d, "
		       "is out of range [0-%d] %d %d.\n", txq_id, idx, q->n_bd,
		       q->write_ptr, q->read_ptr);
		return 0;
	}

	for (idx = il_queue_inc_wrap(idx, q->n_bd); q->read_ptr != idx;
	     q->read_ptr = il_queue_inc_wrap(q->read_ptr, q->n_bd)) {

		skb = txq->skbs[txq->q.read_ptr];

		if (WARN_ON_ONCE(skb == NULL))
			continue;

		hdr = (struct ieee80211_hdr *) skb->data;
		if (ieee80211_is_data_qos(hdr->frame_control))
			nfreed++;

		il4965_tx_status(il, skb, txq_id >= IL4965_FIRST_AMPDU_QUEUE);

		txq->skbs[txq->q.read_ptr] = NULL;
		il->ops->txq_free_tfd(il, txq);
	}
	return nfreed;
}