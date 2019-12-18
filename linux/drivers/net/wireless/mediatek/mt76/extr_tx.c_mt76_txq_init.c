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
struct mt76_txq {int /*<<< orphan*/ * swq; int /*<<< orphan*/  retry_q; } ;
struct mt76_dev {int /*<<< orphan*/ * q_tx; } ;
struct ieee80211_txq {scalar_t__ drv_priv; } ;

/* Variables and functions */
 size_t mt76_txq_get_qid (struct ieee80211_txq*) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

void mt76_txq_init(struct mt76_dev *dev, struct ieee80211_txq *txq)
{
	struct mt76_txq *mtxq = (struct mt76_txq *)txq->drv_priv;

	skb_queue_head_init(&mtxq->retry_q);

	mtxq->swq = &dev->q_tx[mt76_txq_get_qid(txq)];
}