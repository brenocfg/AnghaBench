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
struct sk_buff {unsigned int len; scalar_t__ data_len; } ;
struct efx_tx_queue {unsigned int insert_count; int (* handle_tso ) (struct efx_tx_queue*,struct sk_buff*,int*) ;int xmit_more_available; unsigned int tso_packets; scalar_t__ tx_packets; int /*<<< orphan*/  tso_bursts; int /*<<< orphan*/  core_txq; int /*<<< orphan*/  cb_packets; int /*<<< orphan*/  pio_packets; int /*<<< orphan*/  tso_fallbacks; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_2__ {unsigned int gso_segs; } ;

/* Variables and functions */
 unsigned int EFX_TX_CB_SIZE ; 
 int /*<<< orphan*/  EFX_WARN_ON_ONCE_PARANOID (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 scalar_t__ __netdev_tx_sent_queue (int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ efx_enqueue_skb_copy (struct efx_tx_queue*,struct sk_buff*) ; 
 scalar_t__ efx_enqueue_skb_pio (struct efx_tx_queue*,struct sk_buff*) ; 
 int /*<<< orphan*/  efx_enqueue_unwind (struct efx_tx_queue*,unsigned int) ; 
 scalar_t__ efx_nic_may_tx_pio (struct efx_tx_queue*) ; 
 int /*<<< orphan*/  efx_nic_push_buffers (struct efx_tx_queue*) ; 
 unsigned int efx_piobuf_size ; 
 scalar_t__ efx_tx_map_data (struct efx_tx_queue*,struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  efx_tx_maybe_stop_queue (struct efx_tx_queue*) ; 
 struct efx_tx_queue* efx_tx_queue_partner (struct efx_tx_queue*) ; 
 int efx_tx_tso_fallback (struct efx_tx_queue*,struct sk_buff*) ; 
 int netdev_xmit_more () ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 int stub1 (struct efx_tx_queue*,struct sk_buff*,int*) ; 

netdev_tx_t efx_enqueue_skb(struct efx_tx_queue *tx_queue, struct sk_buff *skb)
{
	unsigned int old_insert_count = tx_queue->insert_count;
	bool xmit_more = netdev_xmit_more();
	bool data_mapped = false;
	unsigned int segments;
	unsigned int skb_len;
	int rc;

	skb_len = skb->len;
	segments = skb_is_gso(skb) ? skb_shinfo(skb)->gso_segs : 0;
	if (segments == 1)
		segments = 0; /* Don't use TSO for a single segment. */

	/* Handle TSO first - it's *possible* (although unlikely) that we might
	 * be passed a packet to segment that's smaller than the copybreak/PIO
	 * size limit.
	 */
	if (segments) {
		EFX_WARN_ON_ONCE_PARANOID(!tx_queue->handle_tso);
		rc = tx_queue->handle_tso(tx_queue, skb, &data_mapped);
		if (rc == -EINVAL) {
			rc = efx_tx_tso_fallback(tx_queue, skb);
			tx_queue->tso_fallbacks++;
			if (rc == 0)
				return 0;
		}
		if (rc)
			goto err;
#ifdef EFX_USE_PIO
	} else if (skb_len <= efx_piobuf_size && !xmit_more &&
		   efx_nic_may_tx_pio(tx_queue)) {
		/* Use PIO for short packets with an empty queue. */
		if (efx_enqueue_skb_pio(tx_queue, skb))
			goto err;
		tx_queue->pio_packets++;
		data_mapped = true;
#endif
	} else if (skb->data_len && skb_len <= EFX_TX_CB_SIZE) {
		/* Pad short packets or coalesce short fragmented packets. */
		if (efx_enqueue_skb_copy(tx_queue, skb))
			goto err;
		tx_queue->cb_packets++;
		data_mapped = true;
	}

	/* Map for DMA and create descriptors if we haven't done so already. */
	if (!data_mapped && (efx_tx_map_data(tx_queue, skb, segments)))
		goto err;

	efx_tx_maybe_stop_queue(tx_queue);

	/* Pass off to hardware */
	if (__netdev_tx_sent_queue(tx_queue->core_txq, skb_len, xmit_more)) {
		struct efx_tx_queue *txq2 = efx_tx_queue_partner(tx_queue);

		/* There could be packets left on the partner queue if
		 * xmit_more was set. If we do not push those they
		 * could be left for a long time and cause a netdev watchdog.
		 */
		if (txq2->xmit_more_available)
			efx_nic_push_buffers(txq2);

		efx_nic_push_buffers(tx_queue);
	} else {
		tx_queue->xmit_more_available = xmit_more;
	}

	if (segments) {
		tx_queue->tso_bursts++;
		tx_queue->tso_packets += segments;
		tx_queue->tx_packets  += segments;
	} else {
		tx_queue->tx_packets++;
	}

	return NETDEV_TX_OK;


err:
	efx_enqueue_unwind(tx_queue, old_insert_count);
	dev_kfree_skb_any(skb);

	/* If we're not expecting another transmit and we had something to push
	 * on this queue or a partner queue then we need to push here to get the
	 * previous packets out.
	 */
	if (!xmit_more) {
		struct efx_tx_queue *txq2 = efx_tx_queue_partner(tx_queue);

		if (txq2->xmit_more_available)
			efx_nic_push_buffers(txq2);

		efx_nic_push_buffers(tx_queue);
	}

	return NETDEV_TX_OK;
}