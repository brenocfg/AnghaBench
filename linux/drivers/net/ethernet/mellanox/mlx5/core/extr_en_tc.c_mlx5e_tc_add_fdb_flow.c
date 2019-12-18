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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct mlx5e_tc_flow_parse_attr {int* mirred_ifindex; int /*<<< orphan*/  spec; int /*<<< orphan*/  mod_hdr_actions; } ;
struct mlx5e_tc_flow {struct mlx5_fc** rule; struct mlx5_esw_flow_attr* esw_attr; } ;
struct mlx5e_rep_priv {int /*<<< orphan*/  rep; } ;
struct mlx5e_priv {TYPE_3__* mdev; struct mlx5e_rep_priv* ppriv; int /*<<< orphan*/  netdev; } ;
struct mlx5_fc {int dummy; } ;
struct mlx5_eswitch {int dummy; } ;
struct mlx5_esw_flow_attr {int prio; scalar_t__ chain; int action; struct mlx5_fc* counter; int /*<<< orphan*/  counter_dev; TYPE_2__* dests; struct mlx5e_tc_flow_parse_attr* parse_attr; } ;
struct TYPE_4__ {struct mlx5_eswitch* eswitch; } ;
struct TYPE_6__ {TYPE_1__ priv; } ;
struct TYPE_5__ {int flags; TYPE_3__* mdev; int /*<<< orphan*/  rep; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (struct mlx5_fc*) ; 
 int MLX5_ESW_DEST_ENCAP ; 
 int MLX5_FLOW_CONTEXT_ACTION_COUNT ; 
 int MLX5_FLOW_CONTEXT_ACTION_MOD_HDR ; 
 int MLX5_MAX_FLOW_FWD_VPORTS ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  OFFLOADED ; 
 int PTR_ERR (struct mlx5_fc*) ; 
 struct net_device* __dev_get_by_index (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flow_flag_set (struct mlx5e_tc_flow*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int mlx5_eswitch_add_vlan_action (struct mlx5_eswitch*,struct mlx5_esw_flow_attr*) ; 
 scalar_t__ mlx5_eswitch_get_chain_range (struct mlx5_eswitch*) ; 
 int mlx5_eswitch_get_prio_range (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  mlx5_eswitch_prios_supported (struct mlx5_eswitch*) ; 
 struct mlx5_fc* mlx5_fc_create (int /*<<< orphan*/ ,int) ; 
 int mlx5e_attach_encap (struct mlx5e_priv*,struct mlx5e_tc_flow*,struct net_device*,int,struct netlink_ext_ack*,struct net_device**,int*) ; 
 int mlx5e_attach_mod_hdr (struct mlx5e_priv*,struct mlx5e_tc_flow*,struct mlx5e_tc_flow_parse_attr*) ; 
 struct mlx5_fc* mlx5e_tc_offload_fdb_rules (struct mlx5_eswitch*,struct mlx5e_tc_flow*,int /*<<< orphan*/ *,struct mlx5_esw_flow_attr*) ; 
 struct mlx5_fc* mlx5e_tc_offload_to_slow_path (struct mlx5_eswitch*,struct mlx5e_tc_flow*,int /*<<< orphan*/ *,struct mlx5_esw_flow_attr*) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
mlx5e_tc_add_fdb_flow(struct mlx5e_priv *priv,
		      struct mlx5e_tc_flow *flow,
		      struct netlink_ext_ack *extack)
{
	struct mlx5_eswitch *esw = priv->mdev->priv.eswitch;
	u32 max_chain = mlx5_eswitch_get_chain_range(esw);
	struct mlx5_esw_flow_attr *attr = flow->esw_attr;
	struct mlx5e_tc_flow_parse_attr *parse_attr = attr->parse_attr;
	u16 max_prio = mlx5_eswitch_get_prio_range(esw);
	struct net_device *out_dev, *encap_dev = NULL;
	struct mlx5_fc *counter = NULL;
	struct mlx5e_rep_priv *rpriv;
	struct mlx5e_priv *out_priv;
	bool encap_valid = true;
	int err = 0;
	int out_index;

	if (!mlx5_eswitch_prios_supported(esw) && attr->prio != 1) {
		NL_SET_ERR_MSG(extack, "E-switch priorities unsupported, upgrade FW");
		return -EOPNOTSUPP;
	}

	if (attr->chain > max_chain) {
		NL_SET_ERR_MSG(extack, "Requested chain is out of supported range");
		return -EOPNOTSUPP;
	}

	if (attr->prio > max_prio) {
		NL_SET_ERR_MSG(extack, "Requested priority is out of supported range");
		return -EOPNOTSUPP;
	}

	for (out_index = 0; out_index < MLX5_MAX_FLOW_FWD_VPORTS; out_index++) {
		int mirred_ifindex;

		if (!(attr->dests[out_index].flags & MLX5_ESW_DEST_ENCAP))
			continue;

		mirred_ifindex = parse_attr->mirred_ifindex[out_index];
		out_dev = __dev_get_by_index(dev_net(priv->netdev),
					     mirred_ifindex);
		err = mlx5e_attach_encap(priv, flow, out_dev, out_index,
					 extack, &encap_dev, &encap_valid);
		if (err)
			return err;

		out_priv = netdev_priv(encap_dev);
		rpriv = out_priv->ppriv;
		attr->dests[out_index].rep = rpriv->rep;
		attr->dests[out_index].mdev = out_priv->mdev;
	}

	err = mlx5_eswitch_add_vlan_action(esw, attr);
	if (err)
		return err;

	if (attr->action & MLX5_FLOW_CONTEXT_ACTION_MOD_HDR) {
		err = mlx5e_attach_mod_hdr(priv, flow, parse_attr);
		kfree(parse_attr->mod_hdr_actions);
		if (err)
			return err;
	}

	if (attr->action & MLX5_FLOW_CONTEXT_ACTION_COUNT) {
		counter = mlx5_fc_create(attr->counter_dev, true);
		if (IS_ERR(counter))
			return PTR_ERR(counter);

		attr->counter = counter;
	}

	/* we get here if one of the following takes place:
	 * (1) there's no error
	 * (2) there's an encap action and we don't have valid neigh
	 */
	if (!encap_valid) {
		/* continue with goto slow path rule instead */
		struct mlx5_esw_flow_attr slow_attr;

		flow->rule[0] = mlx5e_tc_offload_to_slow_path(esw, flow, &parse_attr->spec, &slow_attr);
	} else {
		flow->rule[0] = mlx5e_tc_offload_fdb_rules(esw, flow, &parse_attr->spec, attr);
	}

	if (IS_ERR(flow->rule[0]))
		return PTR_ERR(flow->rule[0]);
	else
		flow_flag_set(flow, OFFLOADED);

	return 0;
}