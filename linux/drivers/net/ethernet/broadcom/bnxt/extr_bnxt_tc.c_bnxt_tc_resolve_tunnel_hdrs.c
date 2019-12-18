#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vlan_dev_priv {int /*<<< orphan*/  vlan_proto; int /*<<< orphan*/  vlan_id; struct net_device* real_dev; } ;
struct TYPE_9__ {struct net_device* dev; } ;
struct rtable {TYPE_4__ dst; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct neighbour {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct TYPE_8__ {TYPE_2__ ipv4; } ;
struct ip_tunnel_key {int /*<<< orphan*/  ttl; TYPE_3__ u; int /*<<< orphan*/  tp_dst; } ;
struct TYPE_6__ {int /*<<< orphan*/  member_0; } ;
struct flowi4 {int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; int /*<<< orphan*/  fl4_dport; int /*<<< orphan*/  flowi4_proto; TYPE_1__ member_0; } ;
struct bnxt_tc_l2_key {int num_vlans; int /*<<< orphan*/  smac; int /*<<< orphan*/  dmac; int /*<<< orphan*/  inner_vlan_tpid; int /*<<< orphan*/  inner_vlan_tci; } ;
struct bnxt {struct net_device* dev; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 scalar_t__ IS_ERR (struct rtable*) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 struct neighbour* dst_neigh_lookup (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip4_dst_hoplimit (TYPE_4__*) ; 
 struct rtable* ip_route_output_key (int /*<<< orphan*/ ,struct flowi4*) ; 
 int /*<<< orphan*/  ip_rt_put (struct rtable*) ; 
 scalar_t__ is_vlan_dev (struct net_device*) ; 
 int /*<<< orphan*/  neigh_ha_snapshot (int /*<<< orphan*/ ,struct neighbour*,struct net_device*) ; 
 int /*<<< orphan*/  neigh_release (struct neighbour*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  netdev_name (struct net_device*) ; 
 struct vlan_dev_priv* vlan_dev_priv (struct net_device*) ; 

__attribute__((used)) static int bnxt_tc_resolve_tunnel_hdrs(struct bnxt *bp,
				       struct ip_tunnel_key *tun_key,
				       struct bnxt_tc_l2_key *l2_info)
{
#ifdef CONFIG_INET
	struct net_device *real_dst_dev = bp->dev;
	struct flowi4 flow = { {0} };
	struct net_device *dst_dev;
	struct neighbour *nbr;
	struct rtable *rt;
	int rc;

	flow.flowi4_proto = IPPROTO_UDP;
	flow.fl4_dport = tun_key->tp_dst;
	flow.daddr = tun_key->u.ipv4.dst;

	rt = ip_route_output_key(dev_net(real_dst_dev), &flow);
	if (IS_ERR(rt)) {
		netdev_info(bp->dev, "no route to %pI4b", &flow.daddr);
		return -EOPNOTSUPP;
	}

	/* The route must either point to the real_dst_dev or a dst_dev that
	 * uses the real_dst_dev.
	 */
	dst_dev = rt->dst.dev;
	if (is_vlan_dev(dst_dev)) {
#if IS_ENABLED(CONFIG_VLAN_8021Q)
		struct vlan_dev_priv *vlan = vlan_dev_priv(dst_dev);

		if (vlan->real_dev != real_dst_dev) {
			netdev_info(bp->dev,
				    "dst_dev(%s) doesn't use PF-if(%s)",
				    netdev_name(dst_dev),
				    netdev_name(real_dst_dev));
			rc = -EOPNOTSUPP;
			goto put_rt;
		}
		l2_info->inner_vlan_tci = htons(vlan->vlan_id);
		l2_info->inner_vlan_tpid = vlan->vlan_proto;
		l2_info->num_vlans = 1;
#endif
	} else if (dst_dev != real_dst_dev) {
		netdev_info(bp->dev,
			    "dst_dev(%s) for %pI4b is not PF-if(%s)",
			    netdev_name(dst_dev), &flow.daddr,
			    netdev_name(real_dst_dev));
		rc = -EOPNOTSUPP;
		goto put_rt;
	}

	nbr = dst_neigh_lookup(&rt->dst, &flow.daddr);
	if (!nbr) {
		netdev_info(bp->dev, "can't lookup neighbor for %pI4b",
			    &flow.daddr);
		rc = -EOPNOTSUPP;
		goto put_rt;
	}

	tun_key->u.ipv4.src = flow.saddr;
	tun_key->ttl = ip4_dst_hoplimit(&rt->dst);
	neigh_ha_snapshot(l2_info->dmac, nbr, dst_dev);
	ether_addr_copy(l2_info->smac, dst_dev->dev_addr);
	neigh_release(nbr);
	ip_rt_put(rt);

	return 0;
put_rt:
	ip_rt_put(rt);
	return rc;
#else
	return -EOPNOTSUPP;
#endif
}