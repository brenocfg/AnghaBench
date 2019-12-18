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
typedef  int /*<<< orphan*/  u16 ;
struct slave {int /*<<< orphan*/  dev; TYPE_1__* bond; } ;
struct sk_buff {int /*<<< orphan*/  dev; int /*<<< orphan*/  priority; int /*<<< orphan*/  protocol; scalar_t__ mac_header; scalar_t__ network_header; } ;
struct learning_pkt {int /*<<< orphan*/  type; int /*<<< orphan*/  mac_src; int /*<<< orphan*/  mac_dst; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_LOOPBACK ; 
 int /*<<< orphan*/  TC_PRIO_CONTROL ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  dev_queue_xmit (struct sk_buff*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct learning_pkt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,struct learning_pkt*,int) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  slave_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void alb_send_lp_vid(struct slave *slave, u8 mac_addr[],
			    __be16 vlan_proto, u16 vid)
{
	struct learning_pkt pkt;
	struct sk_buff *skb;
	int size = sizeof(struct learning_pkt);

	memset(&pkt, 0, size);
	ether_addr_copy(pkt.mac_dst, mac_addr);
	ether_addr_copy(pkt.mac_src, mac_addr);
	pkt.type = cpu_to_be16(ETH_P_LOOPBACK);

	skb = dev_alloc_skb(size);
	if (!skb)
		return;

	skb_put_data(skb, &pkt, size);

	skb_reset_mac_header(skb);
	skb->network_header = skb->mac_header + ETH_HLEN;
	skb->protocol = pkt.type;
	skb->priority = TC_PRIO_CONTROL;
	skb->dev = slave->dev;

	slave_dbg(slave->bond->dev, slave->dev,
		  "Send learning packet: mac %pM vlan %d\n", mac_addr, vid);

	if (vid)
		__vlan_hwaccel_put_tag(skb, vlan_proto, vid);

	dev_queue_xmit(skb);
}