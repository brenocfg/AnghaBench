#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  pkt_type; struct net_device* dev; scalar_t__ data; } ;
struct TYPE_14__ {char src_mac; int /*<<< orphan*/  vlan_id; } ;
struct TYPE_15__ {TYPE_3__ rx; } ;
struct TYPE_16__ {int flags; int ext_flags; TYPE_4__ next_hop; int /*<<< orphan*/  vlan_id; } ;
struct TYPE_17__ {TYPE_5__ l3; } ;
struct qeth_hdr {TYPE_6__ hdr; } ;
struct TYPE_13__ {scalar_t__ sniffer; } ;
struct qeth_card {TYPE_2__ options; TYPE_7__* dev; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct af_iucv_trans_hdr {scalar_t__ magic; } ;
struct TYPE_19__ {int /*<<< orphan*/  daddr; } ;
struct TYPE_18__ {TYPE_1__* header_ops; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  broadcast; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* create ) (struct sk_buff*,TYPE_7__*,int /*<<< orphan*/ ,unsigned char*,char*,int /*<<< orphan*/ ) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  daddr; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 scalar_t__ ETH_P_AF_IUCV ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 scalar_t__ IS_IQD (struct qeth_card*) ; 
 int /*<<< orphan*/  PACKET_OTHERHOST ; 
 int /*<<< orphan*/  QETH_CARD_STAT_INC (struct qeth_card*,int /*<<< orphan*/ ) ; 
#define  QETH_CAST_BROADCAST 129 
#define  QETH_CAST_MULTICAST 128 
 int QETH_HDR_CAST_MASK ; 
 int QETH_HDR_EXT_INCLUDE_VLAN_TAG ; 
 int QETH_HDR_EXT_SRC_MAC_ADDR ; 
 int QETH_HDR_EXT_VLAN_FRAME ; 
 int QETH_HDR_IPV6 ; 
 int QETH_HDR_PASSTHRU ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_hard_header (struct sk_buff*,struct net_device*,scalar_t__,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_eth_mc_map (int /*<<< orphan*/ ,unsigned char*) ; 
 TYPE_10__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipv6_eth_mc_map (int /*<<< orphan*/ *,unsigned char*) ; 
 TYPE_9__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  qeth_rx_csum (struct qeth_card*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  rx_multicast ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (struct sk_buff*,TYPE_7__*,int /*<<< orphan*/ ,unsigned char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct sk_buff*,TYPE_7__*,int /*<<< orphan*/ ,unsigned char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qeth_l3_rebuild_skb(struct qeth_card *card, struct sk_buff *skb,
				struct qeth_hdr *hdr)
{
	struct af_iucv_trans_hdr *iucv = (struct af_iucv_trans_hdr *) skb->data;
	struct net_device *dev = skb->dev;

	if (IS_IQD(card) && iucv->magic == ETH_P_AF_IUCV) {
		dev_hard_header(skb, dev, ETH_P_AF_IUCV, dev->dev_addr,
				"FAKELL", skb->len);
		return;
	}

	if (!(hdr->hdr.l3.flags & QETH_HDR_PASSTHRU)) {
		u16 prot = (hdr->hdr.l3.flags & QETH_HDR_IPV6) ? ETH_P_IPV6 :
								 ETH_P_IP;
		unsigned char tg_addr[ETH_ALEN];

		skb_reset_network_header(skb);
		switch (hdr->hdr.l3.flags & QETH_HDR_CAST_MASK) {
		case QETH_CAST_MULTICAST:
			if (prot == ETH_P_IP)
				ip_eth_mc_map(ip_hdr(skb)->daddr, tg_addr);
			else
				ipv6_eth_mc_map(&ipv6_hdr(skb)->daddr, tg_addr);
			QETH_CARD_STAT_INC(card, rx_multicast);
			break;
		case QETH_CAST_BROADCAST:
			ether_addr_copy(tg_addr, card->dev->broadcast);
			QETH_CARD_STAT_INC(card, rx_multicast);
			break;
		default:
			if (card->options.sniffer)
				skb->pkt_type = PACKET_OTHERHOST;
			ether_addr_copy(tg_addr, card->dev->dev_addr);
		}

		if (hdr->hdr.l3.ext_flags & QETH_HDR_EXT_SRC_MAC_ADDR)
			card->dev->header_ops->create(skb, card->dev, prot,
				tg_addr, &hdr->hdr.l3.next_hop.rx.src_mac,
				skb->len);
		else
			card->dev->header_ops->create(skb, card->dev, prot,
				tg_addr, "FAKELL", skb->len);
	}

	/* copy VLAN tag from hdr into skb */
	if (!card->options.sniffer &&
	    (hdr->hdr.l3.ext_flags & (QETH_HDR_EXT_VLAN_FRAME |
				      QETH_HDR_EXT_INCLUDE_VLAN_TAG))) {
		u16 tag = (hdr->hdr.l3.ext_flags & QETH_HDR_EXT_VLAN_FRAME) ?
				hdr->hdr.l3.vlan_id :
				hdr->hdr.l3.next_hop.rx.vlan_id;
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), tag);
	}

	qeth_rx_csum(card, skb, hdr->hdr.l3.ext_flags);
}