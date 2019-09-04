#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {void* protocol; scalar_t__ len; scalar_t__ ip_summed; int /*<<< orphan*/  data; } ;
struct sge_port_stats {int tx_cso; int /*<<< orphan*/  vlan_insert; int /*<<< orphan*/  tx_tso; int /*<<< orphan*/  tx_need_hdrroom; } ;
struct sge {struct sk_buff** espibug_skb; int /*<<< orphan*/ * port_stats; } ;
struct net_device {size_t if_port; scalar_t__ hard_header_len; scalar_t__ mtu; struct adapter* ml_priv; } ;
struct cpl_tx_pkt_lso {int /*<<< orphan*/  len; void* eth_type_mss; int /*<<< orphan*/  tcp_hdr_words; int /*<<< orphan*/  ip_hdr_words; scalar_t__ l4_csum_dis; scalar_t__ ip_csum_dis; int /*<<< orphan*/  opcode; } ;
struct cpl_tx_pkt {int ip_csum_dis; int l4_csum_dis; size_t iff; int vlan_valid; void* vlan; int /*<<< orphan*/  opcode; } ;
struct adapter {struct sge* sge; } ;
typedef  int netdev_tx_t ;
struct TYPE_8__ {void* ar_op; } ;
struct TYPE_7__ {scalar_t__ protocol; int /*<<< orphan*/  ihl; } ;
struct TYPE_6__ {scalar_t__ gso_size; } ;
struct TYPE_5__ {int /*<<< orphan*/  doff; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPOP_REQUEST ; 
 scalar_t__ CHECKSUM_PARTIAL ; 
 int CPL_ETH_II ; 
 int CPL_ETH_II_VLAN ; 
 int /*<<< orphan*/  CPL_TX_PKT ; 
 int /*<<< orphan*/  CPL_TX_PKT_LSO ; 
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_ARP ; 
 int /*<<< orphan*/  ETH_P_CPL5 ; 
 scalar_t__ IPPROTO_UDP ; 
 int /*<<< orphan*/  MK_ETH_TYPE_MSS (int,scalar_t__) ; 
 int NETDEV_TX_OK ; 
 struct cpl_tx_pkt* __skb_push (struct sk_buff*,int) ; 
 TYPE_4__* arp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ eth_hdr_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (scalar_t__) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 TYPE_3__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,...) ; 
 int skb_checksum_help (struct sk_buff*) ; 
 struct sk_buff* skb_get (struct sk_buff*) ; 
 scalar_t__ skb_headroom (struct sk_buff*) ; 
 scalar_t__ skb_network_offset (struct sk_buff*) ; 
 struct cpl_tx_pkt_lso* skb_push (struct sk_buff*,int) ; 
 struct sk_buff* skb_realloc_headroom (struct sk_buff*,int) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_vlan_tag_get (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 
 int t1_sge_tx (struct sk_buff*,struct adapter*,int /*<<< orphan*/ ,struct net_device*) ; 
 TYPE_1__* tcp_hdr (struct sk_buff*) ; 
 struct sge_port_stats* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

netdev_tx_t t1_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct adapter *adapter = dev->ml_priv;
	struct sge *sge = adapter->sge;
	struct sge_port_stats *st = this_cpu_ptr(sge->port_stats[dev->if_port]);
	struct cpl_tx_pkt *cpl;
	struct sk_buff *orig_skb = skb;
	int ret;

	if (skb->protocol == htons(ETH_P_CPL5))
		goto send;

	/*
	 * We are using a non-standard hard_header_len.
	 * Allocate more header room in the rare cases it is not big enough.
	 */
	if (unlikely(skb_headroom(skb) < dev->hard_header_len - ETH_HLEN)) {
		skb = skb_realloc_headroom(skb, sizeof(struct cpl_tx_pkt_lso));
		++st->tx_need_hdrroom;
		dev_kfree_skb_any(orig_skb);
		if (!skb)
			return NETDEV_TX_OK;
	}

	if (skb_shinfo(skb)->gso_size) {
		int eth_type;
		struct cpl_tx_pkt_lso *hdr;

		++st->tx_tso;

		eth_type = skb_network_offset(skb) == ETH_HLEN ?
			CPL_ETH_II : CPL_ETH_II_VLAN;

		hdr = skb_push(skb, sizeof(*hdr));
		hdr->opcode = CPL_TX_PKT_LSO;
		hdr->ip_csum_dis = hdr->l4_csum_dis = 0;
		hdr->ip_hdr_words = ip_hdr(skb)->ihl;
		hdr->tcp_hdr_words = tcp_hdr(skb)->doff;
		hdr->eth_type_mss = htons(MK_ETH_TYPE_MSS(eth_type,
							  skb_shinfo(skb)->gso_size));
		hdr->len = htonl(skb->len - sizeof(*hdr));
		cpl = (struct cpl_tx_pkt *)hdr;
	} else {
		/*
		 * Packets shorter than ETH_HLEN can break the MAC, drop them
		 * early.  Also, we may get oversized packets because some
		 * parts of the kernel don't handle our unusual hard_header_len
		 * right, drop those too.
		 */
		if (unlikely(skb->len < ETH_HLEN ||
			     skb->len > dev->mtu + eth_hdr_len(skb->data))) {
			netdev_dbg(dev, "packet size %d hdr %d mtu%d\n",
				   skb->len, eth_hdr_len(skb->data), dev->mtu);
			dev_kfree_skb_any(skb);
			return NETDEV_TX_OK;
		}

		if (skb->ip_summed == CHECKSUM_PARTIAL &&
		    ip_hdr(skb)->protocol == IPPROTO_UDP) {
			if (unlikely(skb_checksum_help(skb))) {
				netdev_dbg(dev, "unable to do udp checksum\n");
				dev_kfree_skb_any(skb);
				return NETDEV_TX_OK;
			}
		}

		/* Hmmm, assuming to catch the gratious arp... and we'll use
		 * it to flush out stuck espi packets...
		 */
		if ((unlikely(!adapter->sge->espibug_skb[dev->if_port]))) {
			if (skb->protocol == htons(ETH_P_ARP) &&
			    arp_hdr(skb)->ar_op == htons(ARPOP_REQUEST)) {
				adapter->sge->espibug_skb[dev->if_port] = skb;
				/* We want to re-use this skb later. We
				 * simply bump the reference count and it
				 * will not be freed...
				 */
				skb = skb_get(skb);
			}
		}

		cpl = __skb_push(skb, sizeof(*cpl));
		cpl->opcode = CPL_TX_PKT;
		cpl->ip_csum_dis = 1;    /* SW calculates IP csum */
		cpl->l4_csum_dis = skb->ip_summed == CHECKSUM_PARTIAL ? 0 : 1;
		/* the length field isn't used so don't bother setting it */

		st->tx_cso += (skb->ip_summed == CHECKSUM_PARTIAL);
	}
	cpl->iff = dev->if_port;

	if (skb_vlan_tag_present(skb)) {
		cpl->vlan_valid = 1;
		cpl->vlan = htons(skb_vlan_tag_get(skb));
		st->vlan_insert++;
	} else
		cpl->vlan_valid = 0;

send:
	ret = t1_sge_tx(skb, adapter, 0, dev);

	/* If transmit busy, and we reallocated skb's due to headroom limit,
	 * then silently discard to avoid leak.
	 */
	if (unlikely(ret != NETDEV_TX_OK && skb != orig_skb)) {
		dev_kfree_skb_any(skb);
		ret = NETDEV_TX_OK;
	}
	return ret;
}