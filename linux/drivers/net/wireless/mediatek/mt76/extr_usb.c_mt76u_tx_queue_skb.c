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
typedef  size_t u16 ;
struct sk_buff {int /*<<< orphan*/ * next; int /*<<< orphan*/  prev; } ;
struct mt76_wcid {int dummy; } ;
struct mt76_tx_info {struct sk_buff* skb; } ;
struct mt76_queue {size_t tail; int queued; int ndesc; TYPE_3__* entry; int /*<<< orphan*/  hw_idx; } ;
struct mt76_dev {TYPE_2__* drv; TYPE_1__* q_tx; } ;
struct ieee80211_sta {int dummy; } ;
typedef  enum mt76_txq_id { ____Placeholder_mt76_txq_id } mt76_txq_id ;
struct TYPE_6__ {struct sk_buff* skb; int /*<<< orphan*/  urb; } ;
struct TYPE_5__ {int (* tx_prepare_skb ) (struct mt76_dev*,int /*<<< orphan*/ *,int,struct mt76_wcid*,struct ieee80211_sta*,struct mt76_tx_info*) ;} ;
struct TYPE_4__ {struct mt76_queue* q; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  USB_DIR_OUT ; 
 int /*<<< orphan*/  mt76u_complete_tx ; 
 int /*<<< orphan*/  mt76u_fill_bulk_urb (struct mt76_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int mt76u_tx_setup_buffers (struct mt76_dev*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q2ep (int /*<<< orphan*/ ) ; 
 int stub1 (struct mt76_dev*,int /*<<< orphan*/ *,int,struct mt76_wcid*,struct ieee80211_sta*,struct mt76_tx_info*) ; 

__attribute__((used)) static int
mt76u_tx_queue_skb(struct mt76_dev *dev, enum mt76_txq_id qid,
		   struct sk_buff *skb, struct mt76_wcid *wcid,
		   struct ieee80211_sta *sta)
{
	struct mt76_queue *q = dev->q_tx[qid].q;
	struct mt76_tx_info tx_info = {
		.skb = skb,
	};
	u16 idx = q->tail;
	int err;

	if (q->queued == q->ndesc)
		return -ENOSPC;

	skb->prev = skb->next = NULL;
	err = dev->drv->tx_prepare_skb(dev, NULL, qid, wcid, sta, &tx_info);
	if (err < 0)
		return err;

	err = mt76u_tx_setup_buffers(dev, tx_info.skb, q->entry[idx].urb);
	if (err < 0)
		return err;

	mt76u_fill_bulk_urb(dev, USB_DIR_OUT, q2ep(q->hw_idx),
			    q->entry[idx].urb, mt76u_complete_tx,
			    &q->entry[idx]);

	q->tail = (q->tail + 1) % q->ndesc;
	q->entry[idx].skb = tx_info.skb;
	q->queued++;

	return idx;
}