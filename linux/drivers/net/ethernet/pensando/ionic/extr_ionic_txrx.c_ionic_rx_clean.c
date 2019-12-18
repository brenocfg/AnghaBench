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
struct sk_buff {scalar_t__ csum; int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  protocol; } ;
struct net_device {int features; } ;
struct ionic_rxq_comp {int pkt_type_color; int csum_flags; int /*<<< orphan*/  vlan_tci; int /*<<< orphan*/  csum; int /*<<< orphan*/  rss_hash; int /*<<< orphan*/  len; scalar_t__ status; } ;
struct ionic_rx_stats {int /*<<< orphan*/  csum_error; int /*<<< orphan*/  csum_none; int /*<<< orphan*/  csum_complete; int /*<<< orphan*/  bytes; int /*<<< orphan*/  pkts; } ;
struct ionic_queue {int /*<<< orphan*/  index; TYPE_1__* lif; } ;
struct ionic_qcq {int /*<<< orphan*/  napi; } ;
struct ionic_desc_info {int dummy; } ;
struct ionic_cq_info {struct ionic_rxq_comp* cq_desc; } ;
typedef  scalar_t__ __wsum ;
struct TYPE_2__ {int /*<<< orphan*/  state; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_COMPLETE ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  IONIC_LIF_QUEUE_RESET ; 
#define  IONIC_PKT_TYPE_IPV4 133 
#define  IONIC_PKT_TYPE_IPV4_TCP 132 
#define  IONIC_PKT_TYPE_IPV4_UDP 131 
#define  IONIC_PKT_TYPE_IPV6 130 
#define  IONIC_PKT_TYPE_IPV6_TCP 129 
#define  IONIC_PKT_TYPE_IPV6_UDP 128 
 int IONIC_RXQ_COMP_CSUM_F_CALC ; 
 int IONIC_RXQ_COMP_CSUM_F_IP_BAD ; 
 int IONIC_RXQ_COMP_CSUM_F_TCP_BAD ; 
 int IONIC_RXQ_COMP_CSUM_F_UDP_BAD ; 
 int IONIC_RXQ_COMP_CSUM_F_VLAN ; 
 int IONIC_RXQ_COMP_PKT_TYPE_MASK ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_RXHASH ; 
 int /*<<< orphan*/  PKT_HASH_TYPE_L3 ; 
 int /*<<< orphan*/  PKT_HASH_TYPE_L4 ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ionic_rx_copybreak (struct ionic_queue*,struct ionic_desc_info*,struct ionic_cq_info*,struct sk_buff**) ; 
 int /*<<< orphan*/  ionic_rx_recycle (struct ionic_queue*,struct ionic_desc_info*,struct sk_buff*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 struct ionic_qcq* q_to_qcq (struct ionic_queue*) ; 
 struct ionic_rx_stats* q_to_rx_stats (struct ionic_queue*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_record_rx_queue (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_hash (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ionic_rx_clean(struct ionic_queue *q, struct ionic_desc_info *desc_info,
			   struct ionic_cq_info *cq_info, void *cb_arg)
{
	struct ionic_rxq_comp *comp = cq_info->cq_desc;
	struct ionic_qcq *qcq = q_to_qcq(q);
	struct sk_buff *skb = cb_arg;
	struct ionic_rx_stats *stats;
	struct net_device *netdev;

	stats = q_to_rx_stats(q);
	netdev = q->lif->netdev;

	if (comp->status) {
		ionic_rx_recycle(q, desc_info, skb);
		return;
	}

	if (unlikely(test_bit(IONIC_LIF_QUEUE_RESET, q->lif->state))) {
		/* no packet processing while resetting */
		ionic_rx_recycle(q, desc_info, skb);
		return;
	}

	stats->pkts++;
	stats->bytes += le16_to_cpu(comp->len);

	ionic_rx_copybreak(q, desc_info, cq_info, &skb);

	skb_put(skb, le16_to_cpu(comp->len));
	skb->protocol = eth_type_trans(skb, netdev);

	skb_record_rx_queue(skb, q->index);

	if (netdev->features & NETIF_F_RXHASH) {
		switch (comp->pkt_type_color & IONIC_RXQ_COMP_PKT_TYPE_MASK) {
		case IONIC_PKT_TYPE_IPV4:
		case IONIC_PKT_TYPE_IPV6:
			skb_set_hash(skb, le32_to_cpu(comp->rss_hash),
				     PKT_HASH_TYPE_L3);
			break;
		case IONIC_PKT_TYPE_IPV4_TCP:
		case IONIC_PKT_TYPE_IPV6_TCP:
		case IONIC_PKT_TYPE_IPV4_UDP:
		case IONIC_PKT_TYPE_IPV6_UDP:
			skb_set_hash(skb, le32_to_cpu(comp->rss_hash),
				     PKT_HASH_TYPE_L4);
			break;
		}
	}

	if (netdev->features & NETIF_F_RXCSUM) {
		if (comp->csum_flags & IONIC_RXQ_COMP_CSUM_F_CALC) {
			skb->ip_summed = CHECKSUM_COMPLETE;
			skb->csum = (__wsum)le16_to_cpu(comp->csum);
			stats->csum_complete++;
		}
	} else {
		stats->csum_none++;
	}

	if ((comp->csum_flags & IONIC_RXQ_COMP_CSUM_F_TCP_BAD) ||
	    (comp->csum_flags & IONIC_RXQ_COMP_CSUM_F_UDP_BAD) ||
	    (comp->csum_flags & IONIC_RXQ_COMP_CSUM_F_IP_BAD))
		stats->csum_error++;

	if (netdev->features & NETIF_F_HW_VLAN_CTAG_RX) {
		if (comp->csum_flags & IONIC_RXQ_COMP_CSUM_F_VLAN)
			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q),
					       le16_to_cpu(comp->vlan_tci));
	}

	napi_gro_receive(&qcq->napi, skb);
}