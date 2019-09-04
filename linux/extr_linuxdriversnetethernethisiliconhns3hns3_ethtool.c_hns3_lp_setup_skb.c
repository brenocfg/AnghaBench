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
struct sk_buff {struct net_device* dev; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct ethhdr {int /*<<< orphan*/  h_proto; int /*<<< orphan*/  h_source; int /*<<< orphan*/  h_dest; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  ETH_P_ARP ; 
 unsigned int HNS3_NIC_LB_TEST_PACKET_SIZE ; 
 int /*<<< orphan*/  NET_IP_ALIGN ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* skb_put (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 

__attribute__((used)) static void hns3_lp_setup_skb(struct sk_buff *skb)
{
	struct net_device *ndev = skb->dev;
	unsigned char *packet;
	struct ethhdr *ethh;
	unsigned int i;

	skb_reserve(skb, NET_IP_ALIGN);
	ethh = skb_put(skb, sizeof(struct ethhdr));
	packet = skb_put(skb, HNS3_NIC_LB_TEST_PACKET_SIZE);

	memcpy(ethh->h_dest, ndev->dev_addr, ETH_ALEN);
	eth_zero_addr(ethh->h_source);
	ethh->h_proto = htons(ETH_P_ARP);
	skb_reset_mac_header(skb);

	for (i = 0; i < HNS3_NIC_LB_TEST_PACKET_SIZE; i++)
		packet[i] = (unsigned char)(i & 0xff);
}