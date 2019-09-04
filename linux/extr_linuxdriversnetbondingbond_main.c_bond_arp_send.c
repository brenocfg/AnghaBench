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
struct sk_buff {int dummy; } ;
struct net_device {int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  name; } ;
struct bond_vlan_tag {scalar_t__ vlan_id; int /*<<< orphan*/  vlan_proto; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_ARP ; 
 int /*<<< orphan*/  VLAN_N_VID ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct sk_buff* arp_create (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arp_xmit (struct sk_buff*) ; 
 int /*<<< orphan*/  net_err_ratelimited (char*) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int,scalar_t__,...) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 struct sk_buff* vlan_insert_tag_set_proto (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void bond_arp_send(struct net_device *slave_dev, int arp_op,
			  __be32 dest_ip, __be32 src_ip,
			  struct bond_vlan_tag *tags)
{
	struct sk_buff *skb;
	struct bond_vlan_tag *outer_tag = tags;

	netdev_dbg(slave_dev, "arp %d on slave %s: dst %pI4 src %pI4\n",
		   arp_op, slave_dev->name, &dest_ip, &src_ip);

	skb = arp_create(arp_op, ETH_P_ARP, dest_ip, slave_dev, src_ip,
			 NULL, slave_dev->dev_addr, NULL);

	if (!skb) {
		net_err_ratelimited("ARP packet allocation failed\n");
		return;
	}

	if (!tags || tags->vlan_proto == VLAN_N_VID)
		goto xmit;

	tags++;

	/* Go through all the tags backwards and add them to the packet */
	while (tags->vlan_proto != VLAN_N_VID) {
		if (!tags->vlan_id) {
			tags++;
			continue;
		}

		netdev_dbg(slave_dev, "inner tag: proto %X vid %X\n",
			   ntohs(outer_tag->vlan_proto), tags->vlan_id);
		skb = vlan_insert_tag_set_proto(skb, tags->vlan_proto,
						tags->vlan_id);
		if (!skb) {
			net_err_ratelimited("failed to insert inner VLAN tag\n");
			return;
		}

		tags++;
	}
	/* Set the outer tag */
	if (outer_tag->vlan_id) {
		netdev_dbg(slave_dev, "outer tag: proto %X vid %X\n",
			   ntohs(outer_tag->vlan_proto), outer_tag->vlan_id);
		__vlan_hwaccel_put_tag(skb, outer_tag->vlan_proto,
				       outer_tag->vlan_id);
	}

xmit:
	arp_xmit(skb);
}