#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct nfp_flower_priv {int flower_ext_feats; } ;
struct TYPE_6__ {void* shortcut; } ;
struct TYPE_5__ {struct net_device* dev; } ;
struct nfp_fl_payload {TYPE_3__ meta; TYPE_2__ pre_tun_rule; } ;
struct TYPE_4__ {size_t len_lw; int /*<<< orphan*/  jump_id; } ;
struct nfp_fl_output {void* port; void* flags; TYPE_1__ head; } ;
struct nfp_app {struct nfp_flower_priv* priv; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct flow_action_entry {struct net_device* dev; } ;
typedef  enum nfp_flower_tun_type { ____Placeholder_nfp_flower_tun_type } nfp_flower_tun_type ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  NFP_FL_ACTION_OPCODE_OUTPUT ; 
 int NFP_FL_FEATS_LAG ; 
 int NFP_FL_FEATS_PRE_TUN_RULES ; 
 int NFP_FL_LAG_OUT ; 
 size_t NFP_FL_LW_SIZ ; 
 int NFP_FL_OUT_FLAGS_LAST ; 
 int NFP_FL_OUT_FLAGS_USE_TUN ; 
 int NFP_FL_PORT_TYPE_TUN ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 void* cpu_to_be16 (int) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  netdev_port_same_parent_id (struct net_device*,struct net_device*) ; 
 scalar_t__ netif_is_lag_master (struct net_device*) ; 
 int /*<<< orphan*/  nfp_fl_netdev_is_tunnel_type (struct net_device*,int) ; 
 scalar_t__ nfp_flower_internal_port_can_offload (struct nfp_app*,struct net_device*) ; 
 int nfp_flower_lag_get_output_id (struct nfp_app*,struct net_device*) ; 
 scalar_t__ nfp_netdev_is_nfp_repr (struct net_device*) ; 
 int nfp_repr_get_port_id (struct net_device*) ; 

__attribute__((used)) static int
nfp_fl_output(struct nfp_app *app, struct nfp_fl_output *output,
	      const struct flow_action_entry *act,
	      struct nfp_fl_payload *nfp_flow,
	      bool last, struct net_device *in_dev,
	      enum nfp_flower_tun_type tun_type, int *tun_out_cnt,
	      bool pkt_host, struct netlink_ext_ack *extack)
{
	size_t act_size = sizeof(struct nfp_fl_output);
	struct nfp_flower_priv *priv = app->priv;
	struct net_device *out_dev;
	u16 tmp_flags;

	output->head.jump_id = NFP_FL_ACTION_OPCODE_OUTPUT;
	output->head.len_lw = act_size >> NFP_FL_LW_SIZ;

	out_dev = act->dev;
	if (!out_dev) {
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: invalid egress interface for mirred action");
		return -EOPNOTSUPP;
	}

	tmp_flags = last ? NFP_FL_OUT_FLAGS_LAST : 0;

	if (tun_type) {
		/* Verify the egress netdev matches the tunnel type. */
		if (!nfp_fl_netdev_is_tunnel_type(out_dev, tun_type)) {
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: egress interface does not match the required tunnel type");
			return -EOPNOTSUPP;
		}

		if (*tun_out_cnt) {
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: cannot offload more than one tunnel mirred output per filter");
			return -EOPNOTSUPP;
		}
		(*tun_out_cnt)++;

		output->flags = cpu_to_be16(tmp_flags |
					    NFP_FL_OUT_FLAGS_USE_TUN);
		output->port = cpu_to_be32(NFP_FL_PORT_TYPE_TUN | tun_type);
	} else if (netif_is_lag_master(out_dev) &&
		   priv->flower_ext_feats & NFP_FL_FEATS_LAG) {
		int gid;

		output->flags = cpu_to_be16(tmp_flags);
		gid = nfp_flower_lag_get_output_id(app, out_dev);
		if (gid < 0) {
			NL_SET_ERR_MSG_MOD(extack, "invalid entry: cannot find group id for LAG action");
			return gid;
		}
		output->port = cpu_to_be32(NFP_FL_LAG_OUT | gid);
	} else if (nfp_flower_internal_port_can_offload(app, out_dev)) {
		if (!(priv->flower_ext_feats & NFP_FL_FEATS_PRE_TUN_RULES)) {
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: pre-tunnel rules not supported in loaded firmware");
			return -EOPNOTSUPP;
		}

		if (nfp_flow->pre_tun_rule.dev || !pkt_host) {
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: pre-tunnel rules require single egress dev and ptype HOST action");
			return -EOPNOTSUPP;
		}

		nfp_flow->pre_tun_rule.dev = out_dev;

		return 0;
	} else {
		/* Set action output parameters. */
		output->flags = cpu_to_be16(tmp_flags);

		if (nfp_netdev_is_nfp_repr(in_dev)) {
			/* Confirm ingress and egress are on same device. */
			if (!netdev_port_same_parent_id(in_dev, out_dev)) {
				NL_SET_ERR_MSG_MOD(extack, "unsupported offload: ingress and egress interfaces are on different devices");
				return -EOPNOTSUPP;
			}
		}

		if (!nfp_netdev_is_nfp_repr(out_dev)) {
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: egress interface is not an nfp port");
			return -EOPNOTSUPP;
		}

		output->port = cpu_to_be32(nfp_repr_get_port_id(out_dev));
		if (!output->port) {
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: invalid port id for egress interface");
			return -EOPNOTSUPP;
		}
	}
	nfp_flow->meta.shortcut = output->port;

	return 0;
}