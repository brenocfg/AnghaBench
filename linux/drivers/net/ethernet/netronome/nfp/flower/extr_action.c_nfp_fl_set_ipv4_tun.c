#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct rtable {int /*<<< orphan*/  dst; } ;
struct nfp_flower_priv {int flower_ext_feats; } ;
struct TYPE_6__ {size_t len_lw; int /*<<< orphan*/  jump_id; } ;
struct nfp_fl_set_ipv4_tun {int tun_flags; int tun_len; int /*<<< orphan*/  tun_proto; int /*<<< orphan*/  tos; scalar_t__ ttl; int /*<<< orphan*/  tun_id; int /*<<< orphan*/  tun_type_index; TYPE_1__ head; } ;
struct nfp_fl_pre_tunnel {int /*<<< orphan*/  ipv4_dst; } ;
struct nfp_app {struct nfp_flower_priv* priv; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_7__ {scalar_t__ sysctl_ip_default_ttl; } ;
struct net {TYPE_2__ ipv4; } ;
struct TYPE_8__ {int /*<<< orphan*/  dst; } ;
struct TYPE_9__ {TYPE_3__ ipv4; } ;
struct TYPE_10__ {int tun_flags; TYPE_4__ u; int /*<<< orphan*/  tos; scalar_t__ ttl; int /*<<< orphan*/  tun_id; } ;
struct ip_tunnel_info {int options_len; TYPE_5__ key; } ;
struct flowi4 {int /*<<< orphan*/  flowi4_proto; int /*<<< orphan*/  daddr; } ;
struct flow_action_entry {struct ip_tunnel_info* tunnel; } ;
typedef  enum nfp_flower_tun_type { ____Placeholder_nfp_flower_tun_type } nfp_flower_tun_type ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_P_TEB ; 
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  NFP_FL_ACTION_OPCODE_SET_IPV4_TUNNEL ; 
 int NFP_FL_FEATS_GENEVE_OPT ; 
 int /*<<< orphan*/  NFP_FL_IPV4_PRE_TUN_INDEX ; 
 int /*<<< orphan*/  NFP_FL_IPV4_TUNNEL_TYPE ; 
 size_t NFP_FL_LW_SIZ ; 
 int NFP_FL_SUPPORTED_IPV4_UDP_TUN_FLAGS ; 
 scalar_t__ NFP_FL_TUNNEL_CSUM ; 
 int NFP_FL_TUNNEL_GENEVE ; 
 scalar_t__ NFP_FL_TUNNEL_GENEVE_OPT ; 
 int NFP_FL_TUNNEL_KEY ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 int PTR_ERR_OR_ZERO (struct rtable*) ; 
 scalar_t__ TUNNEL_CSUM ; 
 scalar_t__ TUNNEL_GENEVE_OPT ; 
 int TUNNEL_KEY ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 struct net* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 scalar_t__ ip4_dst_hoplimit (int /*<<< orphan*/ *) ; 
 struct rtable* ip_route_output_key (struct net*,struct flowi4*) ; 
 int /*<<< orphan*/  ip_rt_put (struct rtable*) ; 

__attribute__((used)) static int
nfp_fl_set_ipv4_tun(struct nfp_app *app, struct nfp_fl_set_ipv4_tun *set_tun,
		    const struct flow_action_entry *act,
		    struct nfp_fl_pre_tunnel *pre_tun,
		    enum nfp_flower_tun_type tun_type,
		    struct net_device *netdev, struct netlink_ext_ack *extack)
{
	size_t act_size = sizeof(struct nfp_fl_set_ipv4_tun);
	const struct ip_tunnel_info *ip_tun = act->tunnel;
	struct nfp_flower_priv *priv = app->priv;
	u32 tmp_set_ip_tun_type_index = 0;
	/* Currently support one pre-tunnel so index is always 0. */
	int pretun_idx = 0;

	BUILD_BUG_ON(NFP_FL_TUNNEL_CSUM != TUNNEL_CSUM ||
		     NFP_FL_TUNNEL_KEY	!= TUNNEL_KEY ||
		     NFP_FL_TUNNEL_GENEVE_OPT != TUNNEL_GENEVE_OPT);
	if (ip_tun->options_len &&
	    (tun_type != NFP_FL_TUNNEL_GENEVE ||
	    !(priv->flower_ext_feats & NFP_FL_FEATS_GENEVE_OPT))) {
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: loaded firmware does not support geneve options offload");
		return -EOPNOTSUPP;
	}

	set_tun->head.jump_id = NFP_FL_ACTION_OPCODE_SET_IPV4_TUNNEL;
	set_tun->head.len_lw = act_size >> NFP_FL_LW_SIZ;

	/* Set tunnel type and pre-tunnel index. */
	tmp_set_ip_tun_type_index |=
		FIELD_PREP(NFP_FL_IPV4_TUNNEL_TYPE, tun_type) |
		FIELD_PREP(NFP_FL_IPV4_PRE_TUN_INDEX, pretun_idx);

	set_tun->tun_type_index = cpu_to_be32(tmp_set_ip_tun_type_index);
	set_tun->tun_id = ip_tun->key.tun_id;

	if (ip_tun->key.ttl) {
		set_tun->ttl = ip_tun->key.ttl;
	} else {
		struct net *net = dev_net(netdev);
		struct flowi4 flow = {};
		struct rtable *rt;
		int err;

		/* Do a route lookup to determine ttl - if fails then use
		 * default. Note that CONFIG_INET is a requirement of
		 * CONFIG_NET_SWITCHDEV so must be defined here.
		 */
		flow.daddr = ip_tun->key.u.ipv4.dst;
		flow.flowi4_proto = IPPROTO_UDP;
		rt = ip_route_output_key(net, &flow);
		err = PTR_ERR_OR_ZERO(rt);
		if (!err) {
			set_tun->ttl = ip4_dst_hoplimit(&rt->dst);
			ip_rt_put(rt);
		} else {
			set_tun->ttl = net->ipv4.sysctl_ip_default_ttl;
		}
	}

	set_tun->tos = ip_tun->key.tos;

	if (!(ip_tun->key.tun_flags & NFP_FL_TUNNEL_KEY) ||
	    ip_tun->key.tun_flags & ~NFP_FL_SUPPORTED_IPV4_UDP_TUN_FLAGS) {
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: loaded firmware does not support tunnel flag offload");
		return -EOPNOTSUPP;
	}
	set_tun->tun_flags = ip_tun->key.tun_flags;

	if (tun_type == NFP_FL_TUNNEL_GENEVE) {
		set_tun->tun_proto = htons(ETH_P_TEB);
		set_tun->tun_len = ip_tun->options_len / 4;
	}

	/* Complete pre_tunnel action. */
	pre_tun->ipv4_dst = ip_tun->key.u.ipv4.dst;

	return 0;
}