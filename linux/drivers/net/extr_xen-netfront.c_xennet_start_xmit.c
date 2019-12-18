#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u16 ;
struct xen_netif_tx_request {int flags; scalar_t__ size; } ;
struct TYPE_7__ {scalar_t__ features; scalar_t__ pad; int /*<<< orphan*/  type; scalar_t__ size; } ;
struct TYPE_8__ {TYPE_1__ gso; } ;
struct xen_netif_extra_info {scalar_t__ flags; int /*<<< orphan*/  type; TYPE_2__ u; } ;
struct sk_buff {scalar_t__ ip_summed; scalar_t__ len; int /*<<< orphan*/  data; } ;
struct page {int dummy; } ;
struct netfront_stats {int /*<<< orphan*/  syncp; int /*<<< orphan*/  packets; scalar_t__ bytes; } ;
struct TYPE_11__ {int /*<<< orphan*/  req_prod_pvt; } ;
struct netfront_queue {int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  id; int /*<<< orphan*/  tx_irq; TYPE_5__ tx; } ;
struct netfront_info {struct netfront_queue* queues; int /*<<< orphan*/  tx_stats; } ;
struct TYPE_9__ {int /*<<< orphan*/  tx_dropped; } ;
struct net_device {unsigned int real_num_tx_queues; TYPE_3__ stats; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_10__ {int gso_type; unsigned int nr_frags; int /*<<< orphan*/ * frags; scalar_t__ gso_size; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 scalar_t__ CHECKSUM_UNNECESSARY ; 
 unsigned int ETH_HLEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int MAX_XEN_SKB_FRAGS ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 unsigned int PAGE_SIZE ; 
 scalar_t__ RING_GET_REQUEST (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_PUSH_REQUESTS_AND_CHECK_NOTIFY (TYPE_5__*,int) ; 
 int SKB_GSO_TCPV6 ; 
 int /*<<< orphan*/  XEN_NETIF_EXTRA_TYPE_GSO ; 
 int /*<<< orphan*/  XEN_NETIF_GSO_TYPE_TCPV4 ; 
 int /*<<< orphan*/  XEN_NETIF_GSO_TYPE_TCPV6 ; 
 scalar_t__ XEN_NETIF_MAX_TX_SIZE ; 
 int XEN_NETTXF_csum_blank ; 
 int XEN_NETTXF_data_validated ; 
 int XEN_NETTXF_extra_info ; 
 int /*<<< orphan*/  dev_consume_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  net_alert_ratelimited (char*,scalar_t__) ; 
 int /*<<< orphan*/  net_dbg_ratelimited (char*,int,scalar_t__) ; 
 int /*<<< orphan*/  netdev_get_tx_queue (struct net_device*,int /*<<< orphan*/ ) ; 
 struct netfront_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netfront_tx_slot_available (struct netfront_queue*) ; 
 int /*<<< orphan*/  netif_carrier_ok (struct net_device*) ; 
 scalar_t__ netif_needs_gso (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_skb_features (struct sk_buff*) ; 
 int /*<<< orphan*/  netif_tx_stop_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notify_remote_via_irq (int /*<<< orphan*/ ) ; 
 unsigned int offset_in_page (int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_copy (struct sk_buff*,int /*<<< orphan*/ ) ; 
 unsigned int skb_frag_off (int /*<<< orphan*/ *) ; 
 struct page* skb_frag_page (int /*<<< orphan*/ *) ; 
 unsigned int skb_frag_size (int /*<<< orphan*/ *) ; 
 size_t skb_get_queue_mapping (struct sk_buff*) ; 
 unsigned int skb_headlen (struct sk_buff*) ; 
 scalar_t__ skb_linearize (struct sk_buff*) ; 
 TYPE_4__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct netfront_stats* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 struct page* virt_to_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xennet_can_sg (struct net_device*) ; 
 int xennet_count_skb_slots (struct sk_buff*) ; 
 struct xen_netif_tx_request* xennet_make_first_txreq (struct netfront_queue*,struct sk_buff*,struct page*,unsigned int,unsigned int) ; 
 struct xen_netif_tx_request* xennet_make_txreqs (struct netfront_queue*,struct xen_netif_tx_request*,struct sk_buff*,struct page*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  xennet_tx_buf_gc (struct netfront_queue*) ; 

__attribute__((used)) static netdev_tx_t xennet_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct netfront_info *np = netdev_priv(dev);
	struct netfront_stats *tx_stats = this_cpu_ptr(np->tx_stats);
	struct xen_netif_tx_request *tx, *first_tx;
	unsigned int i;
	int notify;
	int slots;
	struct page *page;
	unsigned int offset;
	unsigned int len;
	unsigned long flags;
	struct netfront_queue *queue = NULL;
	unsigned int num_queues = dev->real_num_tx_queues;
	u16 queue_index;
	struct sk_buff *nskb;

	/* Drop the packet if no queues are set up */
	if (num_queues < 1)
		goto drop;
	/* Determine which queue to transmit this SKB on */
	queue_index = skb_get_queue_mapping(skb);
	queue = &np->queues[queue_index];

	/* If skb->len is too big for wire format, drop skb and alert
	 * user about misconfiguration.
	 */
	if (unlikely(skb->len > XEN_NETIF_MAX_TX_SIZE)) {
		net_alert_ratelimited(
			"xennet: skb->len = %u, too big for wire format\n",
			skb->len);
		goto drop;
	}

	slots = xennet_count_skb_slots(skb);
	if (unlikely(slots > MAX_XEN_SKB_FRAGS + 1)) {
		net_dbg_ratelimited("xennet: skb rides the rocket: %d slots, %d bytes\n",
				    slots, skb->len);
		if (skb_linearize(skb))
			goto drop;
	}

	page = virt_to_page(skb->data);
	offset = offset_in_page(skb->data);

	/* The first req should be at least ETH_HLEN size or the packet will be
	 * dropped by netback.
	 */
	if (unlikely(PAGE_SIZE - offset < ETH_HLEN)) {
		nskb = skb_copy(skb, GFP_ATOMIC);
		if (!nskb)
			goto drop;
		dev_consume_skb_any(skb);
		skb = nskb;
		page = virt_to_page(skb->data);
		offset = offset_in_page(skb->data);
	}

	len = skb_headlen(skb);

	spin_lock_irqsave(&queue->tx_lock, flags);

	if (unlikely(!netif_carrier_ok(dev) ||
		     (slots > 1 && !xennet_can_sg(dev)) ||
		     netif_needs_gso(skb, netif_skb_features(skb)))) {
		spin_unlock_irqrestore(&queue->tx_lock, flags);
		goto drop;
	}

	/* First request for the linear area. */
	first_tx = tx = xennet_make_first_txreq(queue, skb,
						page, offset, len);
	offset += tx->size;
	if (offset == PAGE_SIZE) {
		page++;
		offset = 0;
	}
	len -= tx->size;

	if (skb->ip_summed == CHECKSUM_PARTIAL)
		/* local packet? */
		tx->flags |= XEN_NETTXF_csum_blank | XEN_NETTXF_data_validated;
	else if (skb->ip_summed == CHECKSUM_UNNECESSARY)
		/* remote but checksummed. */
		tx->flags |= XEN_NETTXF_data_validated;

	/* Optional extra info after the first request. */
	if (skb_shinfo(skb)->gso_size) {
		struct xen_netif_extra_info *gso;

		gso = (struct xen_netif_extra_info *)
			RING_GET_REQUEST(&queue->tx, queue->tx.req_prod_pvt++);

		tx->flags |= XEN_NETTXF_extra_info;

		gso->u.gso.size = skb_shinfo(skb)->gso_size;
		gso->u.gso.type = (skb_shinfo(skb)->gso_type & SKB_GSO_TCPV6) ?
			XEN_NETIF_GSO_TYPE_TCPV6 :
			XEN_NETIF_GSO_TYPE_TCPV4;
		gso->u.gso.pad = 0;
		gso->u.gso.features = 0;

		gso->type = XEN_NETIF_EXTRA_TYPE_GSO;
		gso->flags = 0;
	}

	/* Requests for the rest of the linear area. */
	tx = xennet_make_txreqs(queue, tx, skb, page, offset, len);

	/* Requests for all the frags. */
	for (i = 0; i < skb_shinfo(skb)->nr_frags; i++) {
		skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
		tx = xennet_make_txreqs(queue, tx, skb, skb_frag_page(frag),
					skb_frag_off(frag),
					skb_frag_size(frag));
	}

	/* First request has the packet length. */
	first_tx->size = skb->len;

	RING_PUSH_REQUESTS_AND_CHECK_NOTIFY(&queue->tx, notify);
	if (notify)
		notify_remote_via_irq(queue->tx_irq);

	u64_stats_update_begin(&tx_stats->syncp);
	tx_stats->bytes += skb->len;
	tx_stats->packets++;
	u64_stats_update_end(&tx_stats->syncp);

	/* Note: It is not safe to access skb after xennet_tx_buf_gc()! */
	xennet_tx_buf_gc(queue);

	if (!netfront_tx_slot_available(queue))
		netif_tx_stop_queue(netdev_get_tx_queue(dev, queue->id));

	spin_unlock_irqrestore(&queue->tx_lock, flags);

	return NETDEV_TX_OK;

 drop:
	dev->stats.tx_dropped++;
	dev_kfree_skb_any(skb);
	return NETDEV_TX_OK;
}