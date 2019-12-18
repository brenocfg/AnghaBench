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
struct stmmac_priv {int /*<<< orphan*/  dev; } ;
struct stmmac_packet_attrs {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; int /*<<< orphan*/  ip_dst; int /*<<< orphan*/  ip_src; } ;
struct sk_buff {int /*<<< orphan*/  dev; int /*<<< orphan*/  pkt_type; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ARPOP_REQUEST ; 
 int /*<<< orphan*/  ETH_P_ARP ; 
 int /*<<< orphan*/  PACKET_HOST ; 
 struct sk_buff* arp_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *stmmac_test_get_arp_skb(struct stmmac_priv *priv,
					       struct stmmac_packet_attrs *attr)
{
	__be32 ip_src = htonl(attr->ip_src);
	__be32 ip_dst = htonl(attr->ip_dst);
	struct sk_buff *skb = NULL;

	skb = arp_create(ARPOP_REQUEST, ETH_P_ARP, ip_dst, priv->dev, ip_src,
			 NULL, attr->src, attr->dst);
	if (!skb)
		return NULL;

	skb->pkt_type = PACKET_HOST;
	skb->dev = priv->dev;

	return skb;
}