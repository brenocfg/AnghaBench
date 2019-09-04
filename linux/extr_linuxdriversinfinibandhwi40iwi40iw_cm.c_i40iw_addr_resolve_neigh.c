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
typedef  int /*<<< orphan*/  u32 ;
struct rtable {int /*<<< orphan*/  dst; } ;
struct net_device {int dummy; } ;
struct neighbour {int nud_state; int /*<<< orphan*/  ha; } ;
struct i40iw_device {TYPE_1__* arp_table; struct net_device* netdev; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  mac_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_ARP_ADD ; 
 int /*<<< orphan*/  I40IW_ARP_DELETE ; 
 int /*<<< orphan*/  I40IW_ARP_RESOLVE ; 
 scalar_t__ IS_ERR (struct rtable*) ; 
 int NUD_VALID ; 
 struct neighbour* dst_neigh_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int i40iw_arp_table (struct i40iw_device*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_manage_arp_cache (struct i40iw_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_pr_err (char*) ; 
 int /*<<< orphan*/  init_net ; 
 struct rtable* ip_route_output (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_rt_put (struct rtable*) ; 
 int /*<<< orphan*/  neigh_event_send (struct neighbour*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  neigh_release (struct neighbour*) ; 
 struct net_device* netdev_master_upper_dev_get (struct net_device*) ; 
 scalar_t__ netif_is_bond_slave (struct net_device*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int i40iw_addr_resolve_neigh(struct i40iw_device *iwdev,
				    u32 src_ip,
				    u32 dst_ip,
				    int arpindex)
{
	struct rtable *rt;
	struct neighbour *neigh;
	int rc = arpindex;
	struct net_device *netdev = iwdev->netdev;
	__be32 dst_ipaddr = htonl(dst_ip);
	__be32 src_ipaddr = htonl(src_ip);

	rt = ip_route_output(&init_net, dst_ipaddr, src_ipaddr, 0, 0);
	if (IS_ERR(rt)) {
		i40iw_pr_err("ip_route_output\n");
		return rc;
	}

	if (netif_is_bond_slave(netdev))
		netdev = netdev_master_upper_dev_get(netdev);

	neigh = dst_neigh_lookup(&rt->dst, &dst_ipaddr);

	rcu_read_lock();
	if (neigh) {
		if (neigh->nud_state & NUD_VALID) {
			if (arpindex >= 0) {
				if (ether_addr_equal(iwdev->arp_table[arpindex].mac_addr,
						     neigh->ha))
					/* Mac address same as arp table */
					goto resolve_neigh_exit;
				i40iw_manage_arp_cache(iwdev,
						       iwdev->arp_table[arpindex].mac_addr,
						       &dst_ip,
						       true,
						       I40IW_ARP_DELETE);
			}

			i40iw_manage_arp_cache(iwdev, neigh->ha, &dst_ip, true, I40IW_ARP_ADD);
			rc = i40iw_arp_table(iwdev, &dst_ip, true, NULL, I40IW_ARP_RESOLVE);
		} else {
			neigh_event_send(neigh, NULL);
		}
	}
 resolve_neigh_exit:

	rcu_read_unlock();
	if (neigh)
		neigh_release(neigh);

	ip_rt_put(rt);
	return rc;
}