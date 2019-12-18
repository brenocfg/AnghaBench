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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct sk_buff {int dummy; } ;
struct be_queue_info {size_t tail; } ;
struct be_tx_obj {struct be_queue_info q; struct sk_buff** sent_skb_list; } ;
struct be_eth_wrb {int dummy; } ;
struct be_adapter {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_consume_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  queue_tail_inc (struct be_queue_info*) ; 
 struct be_eth_wrb* queue_tail_node (struct be_queue_info*) ; 
 scalar_t__ skb_headlen (struct sk_buff*) ; 
 int /*<<< orphan*/  unmap_tx_frag (int /*<<< orphan*/ *,struct be_eth_wrb*,int) ; 

__attribute__((used)) static u16 be_tx_compl_process(struct be_adapter *adapter,
			       struct be_tx_obj *txo, u16 last_index)
{
	struct sk_buff **sent_skbs = txo->sent_skb_list;
	struct be_queue_info *txq = &txo->q;
	struct sk_buff *skb = NULL;
	bool unmap_skb_hdr = false;
	struct be_eth_wrb *wrb;
	u16 num_wrbs = 0;
	u32 frag_index;

	do {
		if (sent_skbs[txq->tail]) {
			/* Free skb from prev req */
			if (skb)
				dev_consume_skb_any(skb);
			skb = sent_skbs[txq->tail];
			sent_skbs[txq->tail] = NULL;
			queue_tail_inc(txq);  /* skip hdr wrb */
			num_wrbs++;
			unmap_skb_hdr = true;
		}
		wrb = queue_tail_node(txq);
		frag_index = txq->tail;
		unmap_tx_frag(&adapter->pdev->dev, wrb,
			      (unmap_skb_hdr && skb_headlen(skb)));
		unmap_skb_hdr = false;
		queue_tail_inc(txq);
		num_wrbs++;
	} while (frag_index != last_index);
	dev_consume_skb_any(skb);

	return num_wrbs;
}