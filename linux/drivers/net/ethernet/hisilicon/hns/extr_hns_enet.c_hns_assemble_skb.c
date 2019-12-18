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
struct sk_buff {int len; int /*<<< orphan*/  queue_mapping; int /*<<< orphan*/ * data; struct net_device* dev; } ;
struct net_device {int dummy; } ;
struct ethhdr {int /*<<< orphan*/  h_proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HNS_LB_TX_RING ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static struct sk_buff *hns_assemble_skb(struct net_device *ndev)
{
	struct sk_buff *skb;
	struct ethhdr *ethhdr;
	int frame_len;

	/* allocate test skb */
	skb = alloc_skb(64, GFP_KERNEL);
	if (!skb)
		return NULL;

	skb_put(skb, 64);
	skb->dev = ndev;
	memset(skb->data, 0xFF, skb->len);

	/* must be tcp/ip package */
	ethhdr = (struct ethhdr *)skb->data;
	ethhdr->h_proto = htons(ETH_P_IP);

	frame_len = skb->len & (~1ul);
	memset(&skb->data[frame_len / 2], 0xAA,
	       frame_len / 2 - 1);

	skb->queue_mapping = HNS_LB_TX_RING;

	return skb;
}