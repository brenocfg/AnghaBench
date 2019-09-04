#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct slave {int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {TYPE_3__* dev; } ;
struct rtable {TYPE_2__ dst; } ;
struct TYPE_8__ {scalar_t__ arp_validate; scalar_t__* arp_targets; } ;
struct bonding {TYPE_3__* dev; TYPE_1__ params; } ;
struct bond_vlan_tag {int dummy; } ;
typedef  scalar_t__ __be32 ;
struct TYPE_10__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPOP_REQUEST ; 
 int BOND_MAX_ARP_TARGETS ; 
 scalar_t__ IS_ERR (struct rtable*) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct bond_vlan_tag*) ; 
 int /*<<< orphan*/  RTO_ONLINK ; 
 int /*<<< orphan*/  bond_arp_send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,struct bond_vlan_tag*) ; 
 scalar_t__ bond_confirm_addr (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct bond_vlan_tag* bond_verify_device_path (TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_net (TYPE_3__*) ; 
 struct rtable* ip_route_output (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_rt_put (struct rtable*) ; 
 int /*<<< orphan*/  kfree (struct bond_vlan_tag*) ; 
 int /*<<< orphan*/  net_warn_ratelimited (char*,char*,scalar_t__*) ; 
 int /*<<< orphan*/  netdev_dbg (TYPE_3__*,char*,scalar_t__*,...) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static void bond_arp_send_all(struct bonding *bond, struct slave *slave)
{
	struct rtable *rt;
	struct bond_vlan_tag *tags;
	__be32 *targets = bond->params.arp_targets, addr;
	int i;

	for (i = 0; i < BOND_MAX_ARP_TARGETS && targets[i]; i++) {
		netdev_dbg(bond->dev, "basa: target %pI4\n", &targets[i]);
		tags = NULL;

		/* Find out through which dev should the packet go */
		rt = ip_route_output(dev_net(bond->dev), targets[i], 0,
				     RTO_ONLINK, 0);
		if (IS_ERR(rt)) {
			/* there's no route to target - try to send arp
			 * probe to generate any traffic (arp_validate=0)
			 */
			if (bond->params.arp_validate)
				net_warn_ratelimited("%s: no route to arp_ip_target %pI4 and arp_validate is set\n",
						     bond->dev->name,
						     &targets[i]);
			bond_arp_send(slave->dev, ARPOP_REQUEST, targets[i],
				      0, tags);
			continue;
		}

		/* bond device itself */
		if (rt->dst.dev == bond->dev)
			goto found;

		rcu_read_lock();
		tags = bond_verify_device_path(bond->dev, rt->dst.dev, 0);
		rcu_read_unlock();

		if (!IS_ERR_OR_NULL(tags))
			goto found;

		/* Not our device - skip */
		netdev_dbg(bond->dev, "no path to arp_ip_target %pI4 via rt.dev %s\n",
			   &targets[i], rt->dst.dev ? rt->dst.dev->name : "NULL");

		ip_rt_put(rt);
		continue;

found:
		addr = bond_confirm_addr(rt->dst.dev, targets[i], 0);
		ip_rt_put(rt);
		bond_arp_send(slave->dev, ARPOP_REQUEST, targets[i],
			      addr, tags);
		kfree(tags);
	}
}