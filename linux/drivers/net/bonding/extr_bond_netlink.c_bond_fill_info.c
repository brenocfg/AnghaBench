#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct slave {TYPE_1__* dev; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {unsigned int miimon; unsigned int updelay; unsigned int downdelay; unsigned int peer_notif_delay; scalar_t__ use_carrier; unsigned int arp_interval; unsigned int arp_validate; unsigned int arp_all_targets; scalar_t__ primary_reselect; scalar_t__ fail_over_mac; scalar_t__ xmit_policy; unsigned int resend_igmp; scalar_t__ num_peer_notif; scalar_t__ all_slaves_active; unsigned int min_links; unsigned int lp_interval; unsigned int packets_per_slave; scalar_t__ lacp_fast; scalar_t__ ad_select; scalar_t__ tlb_dynamic_lb; int /*<<< orphan*/  ad_actor_system; int /*<<< orphan*/  ad_user_port_key; int /*<<< orphan*/  ad_actor_sys_prio; scalar_t__* arp_targets; } ;
struct bonding {TYPE_2__ params; int /*<<< orphan*/  primary_slave; } ;
struct ad_info {int /*<<< orphan*/  partner_system; int /*<<< orphan*/  partner_key; int /*<<< orphan*/  actor_key; int /*<<< orphan*/  ports; int /*<<< orphan*/  aggregator_id; } ;
struct TYPE_3__ {unsigned int ifindex; } ;

/* Variables and functions */
 int BOND_MAX_ARP_TARGETS ; 
 scalar_t__ BOND_MODE (struct bonding*) ; 
 scalar_t__ BOND_MODE_8023AD ; 
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EMSGSIZE ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  IFLA_BOND_ACTIVE_SLAVE ; 
 int /*<<< orphan*/  IFLA_BOND_AD_ACTOR_SYSTEM ; 
 int /*<<< orphan*/  IFLA_BOND_AD_ACTOR_SYS_PRIO ; 
 int /*<<< orphan*/  IFLA_BOND_AD_INFO ; 
 int /*<<< orphan*/  IFLA_BOND_AD_INFO_ACTOR_KEY ; 
 int /*<<< orphan*/  IFLA_BOND_AD_INFO_AGGREGATOR ; 
 int /*<<< orphan*/  IFLA_BOND_AD_INFO_NUM_PORTS ; 
 int /*<<< orphan*/  IFLA_BOND_AD_INFO_PARTNER_KEY ; 
 int /*<<< orphan*/  IFLA_BOND_AD_INFO_PARTNER_MAC ; 
 int /*<<< orphan*/  IFLA_BOND_AD_LACP_RATE ; 
 int /*<<< orphan*/  IFLA_BOND_AD_SELECT ; 
 int /*<<< orphan*/  IFLA_BOND_AD_USER_PORT_KEY ; 
 int /*<<< orphan*/  IFLA_BOND_ALL_SLAVES_ACTIVE ; 
 int /*<<< orphan*/  IFLA_BOND_ARP_ALL_TARGETS ; 
 int /*<<< orphan*/  IFLA_BOND_ARP_INTERVAL ; 
 int /*<<< orphan*/  IFLA_BOND_ARP_IP_TARGET ; 
 int /*<<< orphan*/  IFLA_BOND_ARP_VALIDATE ; 
 int /*<<< orphan*/  IFLA_BOND_DOWNDELAY ; 
 int /*<<< orphan*/  IFLA_BOND_FAIL_OVER_MAC ; 
 int /*<<< orphan*/  IFLA_BOND_LP_INTERVAL ; 
 int /*<<< orphan*/  IFLA_BOND_MIIMON ; 
 int /*<<< orphan*/  IFLA_BOND_MIN_LINKS ; 
 int /*<<< orphan*/  IFLA_BOND_MODE ; 
 int /*<<< orphan*/  IFLA_BOND_NUM_PEER_NOTIF ; 
 int /*<<< orphan*/  IFLA_BOND_PACKETS_PER_SLAVE ; 
 int /*<<< orphan*/  IFLA_BOND_PEER_NOTIF_DELAY ; 
 int /*<<< orphan*/  IFLA_BOND_PRIMARY ; 
 int /*<<< orphan*/  IFLA_BOND_PRIMARY_RESELECT ; 
 int /*<<< orphan*/  IFLA_BOND_RESEND_IGMP ; 
 int /*<<< orphan*/  IFLA_BOND_TLB_DYNAMIC_LB ; 
 int /*<<< orphan*/  IFLA_BOND_UPDELAY ; 
 int /*<<< orphan*/  IFLA_BOND_USE_CARRIER ; 
 int /*<<< orphan*/  IFLA_BOND_XMIT_HASH_POLICY ; 
 int /*<<< orphan*/  bond_3ad_get_active_agg_info (struct bonding*,struct ad_info*) ; 
 int bond_option_active_slave_get_ifindex (struct bonding*) ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 
 struct bonding* netdev_priv (struct net_device const*) ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ nla_put_be32 (struct sk_buff*,int,scalar_t__) ; 
 scalar_t__ nla_put_u16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct slave* rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bond_fill_info(struct sk_buff *skb,
			  const struct net_device *bond_dev)
{
	struct bonding *bond = netdev_priv(bond_dev);
	unsigned int packets_per_slave;
	int ifindex, i, targets_added;
	struct nlattr *targets;
	struct slave *primary;

	if (nla_put_u8(skb, IFLA_BOND_MODE, BOND_MODE(bond)))
		goto nla_put_failure;

	ifindex = bond_option_active_slave_get_ifindex(bond);
	if (ifindex && nla_put_u32(skb, IFLA_BOND_ACTIVE_SLAVE, ifindex))
		goto nla_put_failure;

	if (nla_put_u32(skb, IFLA_BOND_MIIMON, bond->params.miimon))
		goto nla_put_failure;

	if (nla_put_u32(skb, IFLA_BOND_UPDELAY,
			bond->params.updelay * bond->params.miimon))
		goto nla_put_failure;

	if (nla_put_u32(skb, IFLA_BOND_DOWNDELAY,
			bond->params.downdelay * bond->params.miimon))
		goto nla_put_failure;

	if (nla_put_u32(skb, IFLA_BOND_PEER_NOTIF_DELAY,
			bond->params.peer_notif_delay * bond->params.miimon))
		goto nla_put_failure;

	if (nla_put_u8(skb, IFLA_BOND_USE_CARRIER, bond->params.use_carrier))
		goto nla_put_failure;

	if (nla_put_u32(skb, IFLA_BOND_ARP_INTERVAL, bond->params.arp_interval))
		goto nla_put_failure;

	targets = nla_nest_start_noflag(skb, IFLA_BOND_ARP_IP_TARGET);
	if (!targets)
		goto nla_put_failure;

	targets_added = 0;
	for (i = 0; i < BOND_MAX_ARP_TARGETS; i++) {
		if (bond->params.arp_targets[i]) {
			if (nla_put_be32(skb, i, bond->params.arp_targets[i]))
				goto nla_put_failure;
			targets_added = 1;
		}
	}

	if (targets_added)
		nla_nest_end(skb, targets);
	else
		nla_nest_cancel(skb, targets);

	if (nla_put_u32(skb, IFLA_BOND_ARP_VALIDATE, bond->params.arp_validate))
		goto nla_put_failure;

	if (nla_put_u32(skb, IFLA_BOND_ARP_ALL_TARGETS,
			bond->params.arp_all_targets))
		goto nla_put_failure;

	primary = rtnl_dereference(bond->primary_slave);
	if (primary &&
	    nla_put_u32(skb, IFLA_BOND_PRIMARY, primary->dev->ifindex))
		goto nla_put_failure;

	if (nla_put_u8(skb, IFLA_BOND_PRIMARY_RESELECT,
		       bond->params.primary_reselect))
		goto nla_put_failure;

	if (nla_put_u8(skb, IFLA_BOND_FAIL_OVER_MAC,
		       bond->params.fail_over_mac))
		goto nla_put_failure;

	if (nla_put_u8(skb, IFLA_BOND_XMIT_HASH_POLICY,
		       bond->params.xmit_policy))
		goto nla_put_failure;

	if (nla_put_u32(skb, IFLA_BOND_RESEND_IGMP,
		        bond->params.resend_igmp))
		goto nla_put_failure;

	if (nla_put_u8(skb, IFLA_BOND_NUM_PEER_NOTIF,
		       bond->params.num_peer_notif))
		goto nla_put_failure;

	if (nla_put_u8(skb, IFLA_BOND_ALL_SLAVES_ACTIVE,
		       bond->params.all_slaves_active))
		goto nla_put_failure;

	if (nla_put_u32(skb, IFLA_BOND_MIN_LINKS,
			bond->params.min_links))
		goto nla_put_failure;

	if (nla_put_u32(skb, IFLA_BOND_LP_INTERVAL,
			bond->params.lp_interval))
		goto nla_put_failure;

	packets_per_slave = bond->params.packets_per_slave;
	if (nla_put_u32(skb, IFLA_BOND_PACKETS_PER_SLAVE,
			packets_per_slave))
		goto nla_put_failure;

	if (nla_put_u8(skb, IFLA_BOND_AD_LACP_RATE,
		       bond->params.lacp_fast))
		goto nla_put_failure;

	if (nla_put_u8(skb, IFLA_BOND_AD_SELECT,
		       bond->params.ad_select))
		goto nla_put_failure;

	if (nla_put_u8(skb, IFLA_BOND_TLB_DYNAMIC_LB,
		       bond->params.tlb_dynamic_lb))
		goto nla_put_failure;

	if (BOND_MODE(bond) == BOND_MODE_8023AD) {
		struct ad_info info;

		if (capable(CAP_NET_ADMIN)) {
			if (nla_put_u16(skb, IFLA_BOND_AD_ACTOR_SYS_PRIO,
					bond->params.ad_actor_sys_prio))
				goto nla_put_failure;

			if (nla_put_u16(skb, IFLA_BOND_AD_USER_PORT_KEY,
					bond->params.ad_user_port_key))
				goto nla_put_failure;

			if (nla_put(skb, IFLA_BOND_AD_ACTOR_SYSTEM,
				    ETH_ALEN, &bond->params.ad_actor_system))
				goto nla_put_failure;
		}
		if (!bond_3ad_get_active_agg_info(bond, &info)) {
			struct nlattr *nest;

			nest = nla_nest_start_noflag(skb, IFLA_BOND_AD_INFO);
			if (!nest)
				goto nla_put_failure;

			if (nla_put_u16(skb, IFLA_BOND_AD_INFO_AGGREGATOR,
					info.aggregator_id))
				goto nla_put_failure;
			if (nla_put_u16(skb, IFLA_BOND_AD_INFO_NUM_PORTS,
					info.ports))
				goto nla_put_failure;
			if (nla_put_u16(skb, IFLA_BOND_AD_INFO_ACTOR_KEY,
					info.actor_key))
				goto nla_put_failure;
			if (nla_put_u16(skb, IFLA_BOND_AD_INFO_PARTNER_KEY,
					info.partner_key))
				goto nla_put_failure;
			if (nla_put(skb, IFLA_BOND_AD_INFO_PARTNER_MAC,
				    sizeof(info.partner_system),
				    &info.partner_system))
				goto nla_put_failure;

			nla_nest_end(skb, nest);
		}
	}

	return 0;

nla_put_failure:
	return -EMSGSIZE;
}