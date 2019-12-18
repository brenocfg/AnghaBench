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
struct sk_buff {unsigned int len; scalar_t__ data_len; } ;
struct ef4_tx_queue {unsigned int tx_min_size; int /*<<< orphan*/  tx_packets; scalar_t__ xmit_more_available; int /*<<< orphan*/  core_txq; int /*<<< orphan*/  cb_packets; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 unsigned int EF4_TX_CB_SIZE ; 
 int /*<<< orphan*/  EF4_WARN_ON_PARANOID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ ef4_enqueue_skb_copy (struct ef4_tx_queue*,struct sk_buff*) ; 
 int /*<<< orphan*/  ef4_enqueue_unwind (struct ef4_tx_queue*) ; 
 int /*<<< orphan*/  ef4_nic_push_buffers (struct ef4_tx_queue*) ; 
 scalar_t__ ef4_tx_map_data (struct ef4_tx_queue*,struct sk_buff*) ; 
 int /*<<< orphan*/  ef4_tx_maybe_stop_queue (struct ef4_tx_queue*) ; 
 struct ef4_tx_queue* ef4_tx_queue_partner (struct ef4_tx_queue*) ; 
 int /*<<< orphan*/  netdev_tx_sent_queue (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ netdev_xmit_more () ; 
 scalar_t__ netif_xmit_stopped (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_is_gso (struct sk_buff*) ; 

netdev_tx_t ef4_enqueue_skb(struct ef4_tx_queue *tx_queue, struct sk_buff *skb)
{
	bool data_mapped = false;
	unsigned int skb_len;

	skb_len = skb->len;
	EF4_WARN_ON_PARANOID(skb_is_gso(skb));

	if (skb_len < tx_queue->tx_min_size ||
			(skb->data_len && skb_len <= EF4_TX_CB_SIZE)) {
		/* Pad short packets or coalesce short fragmented packets. */
		if (ef4_enqueue_skb_copy(tx_queue, skb))
			goto err;
		tx_queue->cb_packets++;
		data_mapped = true;
	}

	/* Map for DMA and create descriptors if we haven't done so already. */
	if (!data_mapped && (ef4_tx_map_data(tx_queue, skb)))
		goto err;

	/* Update BQL */
	netdev_tx_sent_queue(tx_queue->core_txq, skb_len);

	/* Pass off to hardware */
	if (!netdev_xmit_more() || netif_xmit_stopped(tx_queue->core_txq)) {
		struct ef4_tx_queue *txq2 = ef4_tx_queue_partner(tx_queue);

		/* There could be packets left on the partner queue if those
		 * SKBs had skb->xmit_more set. If we do not push those they
		 * could be left for a long time and cause a netdev watchdog.
		 */
		if (txq2->xmit_more_available)
			ef4_nic_push_buffers(txq2);

		ef4_nic_push_buffers(tx_queue);
	} else {
		tx_queue->xmit_more_available = netdev_xmit_more();
	}

	tx_queue->tx_packets++;

	ef4_tx_maybe_stop_queue(tx_queue);

	return NETDEV_TX_OK;


err:
	ef4_enqueue_unwind(tx_queue);
	dev_kfree_skb_any(skb);
	return NETDEV_TX_OK;
}