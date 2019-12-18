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
struct sk_buff {scalar_t__ ip_summed; scalar_t__ len; } ;
struct ionic_tx_stats {int /*<<< orphan*/  bytes; int /*<<< orphan*/  pkts; } ;
struct ionic_queue {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int ionic_tx_calc_csum (struct ionic_queue*,struct sk_buff*) ; 
 int ionic_tx_calc_no_csum (struct ionic_queue*,struct sk_buff*) ; 
 int /*<<< orphan*/  ionic_tx_clean ; 
 int ionic_tx_skb_frags (struct ionic_queue*,struct sk_buff*) ; 
 int /*<<< orphan*/  ionic_txq_post (struct ionic_queue*,int,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  netdev_tx_sent_queue (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  netdev_xmit_more () ; 
 int /*<<< orphan*/  q_to_ndq (struct ionic_queue*) ; 
 struct ionic_tx_stats* q_to_tx_stats (struct ionic_queue*) ; 
 int /*<<< orphan*/  skb_tx_timestamp (struct sk_buff*) ; 

__attribute__((used)) static int ionic_tx(struct ionic_queue *q, struct sk_buff *skb)
{
	struct ionic_tx_stats *stats = q_to_tx_stats(q);
	int err;

	/* set up the initial descriptor */
	if (skb->ip_summed == CHECKSUM_PARTIAL)
		err = ionic_tx_calc_csum(q, skb);
	else
		err = ionic_tx_calc_no_csum(q, skb);
	if (err)
		return err;

	/* add frags */
	err = ionic_tx_skb_frags(q, skb);
	if (err)
		return err;

	skb_tx_timestamp(skb);
	stats->pkts++;
	stats->bytes += skb->len;

	netdev_tx_sent_queue(q_to_ndq(q), skb->len);
	ionic_txq_post(q, !netdev_xmit_more(), ionic_tx_clean, skb);

	return 0;
}