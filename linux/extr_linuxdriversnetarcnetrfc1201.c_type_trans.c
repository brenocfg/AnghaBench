#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  pkt_type; scalar_t__ data; } ;
struct TYPE_6__ {int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_errors; } ;
struct net_device {int flags; scalar_t__* dev_addr; TYPE_3__ stats; } ;
struct TYPE_5__ {scalar_t__ dest; } ;
struct arc_rfc1201 {int proto; } ;
struct TYPE_4__ {struct arc_rfc1201 rfc1201; } ;
struct archdr {TYPE_2__ hard; TYPE_1__ soft; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int ARC_HDR_SIZE ; 
#define  ARC_P_ARP 133 
#define  ARC_P_IP 132 
#define  ARC_P_IPV6 131 
#define  ARC_P_IPX 130 
#define  ARC_P_NOVELL_EC 129 
#define  ARC_P_RARP 128 
 int /*<<< orphan*/  ETH_P_802_3 ; 
 int /*<<< orphan*/  ETH_P_ARP ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int /*<<< orphan*/  ETH_P_RARP ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  PACKET_BROADCAST ; 
 int /*<<< orphan*/  PACKET_OTHERHOST ; 
 int RFC1201_HDR_SIZE ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 

__attribute__((used)) static __be16 type_trans(struct sk_buff *skb, struct net_device *dev)
{
	struct archdr *pkt = (struct archdr *)skb->data;
	struct arc_rfc1201 *soft = &pkt->soft.rfc1201;
	int hdr_size = ARC_HDR_SIZE + RFC1201_HDR_SIZE;

	/* Pull off the arcnet header. */
	skb_reset_mac_header(skb);
	skb_pull(skb, hdr_size);

	if (pkt->hard.dest == 0) {
		skb->pkt_type = PACKET_BROADCAST;
	} else if (dev->flags & IFF_PROMISC) {
		/* if we're not sending to ourselves :) */
		if (pkt->hard.dest != dev->dev_addr[0])
			skb->pkt_type = PACKET_OTHERHOST;
	}
	/* now return the protocol number */
	switch (soft->proto) {
	case ARC_P_IP:
		return htons(ETH_P_IP);
	case ARC_P_IPV6:
		return htons(ETH_P_IPV6);
	case ARC_P_ARP:
		return htons(ETH_P_ARP);
	case ARC_P_RARP:
		return htons(ETH_P_RARP);

	case ARC_P_IPX:
	case ARC_P_NOVELL_EC:
		return htons(ETH_P_802_3);
	default:
		dev->stats.rx_errors++;
		dev->stats.rx_crc_errors++;
		return 0;
	}

	return htons(ETH_P_IP);
}