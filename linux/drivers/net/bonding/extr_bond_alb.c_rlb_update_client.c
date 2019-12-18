#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {TYPE_3__* dev; } ;
struct rlb_client_info {scalar_t__ vlan_id; TYPE_2__* slave; int /*<<< orphan*/  mac_dst; int /*<<< orphan*/  ip_src; int /*<<< orphan*/  ip_dst; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev_addr; } ;
struct TYPE_6__ {TYPE_3__* dev; TYPE_1__* bond; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPOP_REPLY ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  ETH_P_ARP ; 
 int RLB_ARP_BURST_SIZE ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct sk_buff* arp_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arp_xmit (struct sk_buff*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slave_err (int /*<<< orphan*/ ,TYPE_3__*,char*) ; 

__attribute__((used)) static void rlb_update_client(struct rlb_client_info *client_info)
{
	int i;

	if (!client_info->slave || !is_valid_ether_addr(client_info->mac_dst))
		return;

	for (i = 0; i < RLB_ARP_BURST_SIZE; i++) {
		struct sk_buff *skb;

		skb = arp_create(ARPOP_REPLY, ETH_P_ARP,
				 client_info->ip_dst,
				 client_info->slave->dev,
				 client_info->ip_src,
				 client_info->mac_dst,
				 client_info->slave->dev->dev_addr,
				 client_info->mac_dst);
		if (!skb) {
			slave_err(client_info->slave->bond->dev,
				  client_info->slave->dev,
				  "failed to create an ARP packet\n");
			continue;
		}

		skb->dev = client_info->slave->dev;

		if (client_info->vlan_id) {
			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q),
					       client_info->vlan_id);
		}

		arp_xmit(skb);
	}
}