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
typedef  int /*<<< orphan*/  u8 ;
struct udphdr {scalar_t__ dest; } ;
struct tcphdr {scalar_t__ dest; } ;
struct stmmachdr {scalar_t__ magic; scalar_t__ id; } ;
struct stmmac_test_priv {int ok; int /*<<< orphan*/  comp; TYPE_1__* packet; scalar_t__ double_vlan; } ;
struct sk_buff {int /*<<< orphan*/  hash; } ;
struct packet_type {struct stmmac_test_priv* af_packet_priv; } ;
struct net_device {int dummy; } ;
struct iphdr {scalar_t__ protocol; int ihl; } ;
struct ethhdr {scalar_t__ h_source; scalar_t__ h_dest; } ;
struct TYPE_2__ {scalar_t__ id; scalar_t__ exp_hash; int /*<<< orphan*/  dport; scalar_t__ tcp; scalar_t__ src; scalar_t__ sarc; scalar_t__ dst; } ;

/* Variables and functions */
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
 int /*<<< orphan*/  STMMAC_TEST_PKT_MAGIC ; 
 scalar_t__ STMMAC_TEST_PKT_SIZE ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 scalar_t__ cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_equal (scalar_t__,scalar_t__) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ skb_headlen (struct sk_buff*) ; 
 scalar_t__ skb_linearize (struct sk_buff*) ; 
 scalar_t__ skb_mac_header (struct sk_buff*) ; 
 scalar_t__ skb_network_header (struct sk_buff*) ; 
 struct sk_buff* skb_unshare (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stmmac_test_loopback_validate(struct sk_buff *skb,
					 struct net_device *ndev,
					 struct packet_type *pt,
					 struct net_device *orig_ndev)
{
	struct stmmac_test_priv *tpriv = pt->af_packet_priv;
	struct stmmachdr *shdr;
	struct ethhdr *ehdr;
	struct udphdr *uhdr;
	struct tcphdr *thdr;
	struct iphdr *ihdr;

	skb = skb_unshare(skb, GFP_ATOMIC);
	if (!skb)
		goto out;

	if (skb_linearize(skb))
		goto out;
	if (skb_headlen(skb) < (STMMAC_TEST_PKT_SIZE - ETH_HLEN))
		goto out;

	ehdr = (struct ethhdr *)skb_mac_header(skb);
	if (tpriv->packet->dst) {
		if (!ether_addr_equal(ehdr->h_dest, tpriv->packet->dst))
			goto out;
	}
	if (tpriv->packet->sarc) {
		if (!ether_addr_equal(ehdr->h_source, ehdr->h_dest))
			goto out;
	} else if (tpriv->packet->src) {
		if (!ether_addr_equal(ehdr->h_source, tpriv->packet->src))
			goto out;
	}

	ihdr = ip_hdr(skb);
	if (tpriv->double_vlan)
		ihdr = (struct iphdr *)(skb_network_header(skb) + 4);

	if (tpriv->packet->tcp) {
		if (ihdr->protocol != IPPROTO_TCP)
			goto out;

		thdr = (struct tcphdr *)((u8 *)ihdr + 4 * ihdr->ihl);
		if (thdr->dest != htons(tpriv->packet->dport))
			goto out;

		shdr = (struct stmmachdr *)((u8 *)thdr + sizeof(*thdr));
	} else {
		if (ihdr->protocol != IPPROTO_UDP)
			goto out;

		uhdr = (struct udphdr *)((u8 *)ihdr + 4 * ihdr->ihl);
		if (uhdr->dest != htons(tpriv->packet->dport))
			goto out;

		shdr = (struct stmmachdr *)((u8 *)uhdr + sizeof(*uhdr));
	}

	if (shdr->magic != cpu_to_be64(STMMAC_TEST_PKT_MAGIC))
		goto out;
	if (tpriv->packet->exp_hash && !skb->hash)
		goto out;
	if (tpriv->packet->id != shdr->id)
		goto out;

	tpriv->ok = true;
	complete(&tpriv->comp);
out:
	kfree_skb(skb);
	return 0;
}