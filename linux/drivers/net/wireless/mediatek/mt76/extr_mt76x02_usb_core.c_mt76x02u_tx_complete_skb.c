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
struct mt76_queue_entry {int /*<<< orphan*/  skb; } ;
struct mt76_dev {int dummy; } ;
typedef  enum mt76_txq_id { ____Placeholder_mt76_txq_id } mt76_txq_id ;

/* Variables and functions */
 int /*<<< orphan*/  mt76_tx_complete_skb (struct mt76_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x02u_remove_dma_hdr (int /*<<< orphan*/ ) ; 

void mt76x02u_tx_complete_skb(struct mt76_dev *mdev, enum mt76_txq_id qid,
			      struct mt76_queue_entry *e)
{
	mt76x02u_remove_dma_hdr(e->skb);
	mt76_tx_complete_skb(mdev, e->skb);
}