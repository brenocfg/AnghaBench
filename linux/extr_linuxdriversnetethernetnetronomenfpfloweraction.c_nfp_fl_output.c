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
typedef  int u16 ;
struct tc_action {int dummy; } ;
struct nfp_flower_priv {int flower_ext_feats; } ;
struct TYPE_4__ {void* shortcut; } ;
struct nfp_fl_payload {TYPE_2__ meta; } ;
struct TYPE_3__ {size_t len_lw; int /*<<< orphan*/  jump_id; } ;
struct nfp_fl_output {void* port; void* flags; TYPE_1__ head; } ;
struct nfp_app {struct nfp_flower_priv* priv; } ;
struct net_device {int dummy; } ;
typedef  enum nfp_flower_tun_type { ____Placeholder_nfp_flower_tun_type } nfp_flower_tun_type ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  NFP_FL_ACTION_OPCODE_OUTPUT ; 
 int NFP_FL_FEATS_LAG ; 
 int NFP_FL_LAG_OUT ; 
 size_t NFP_FL_LW_SIZ ; 
 int NFP_FL_OUT_FLAGS_LAST ; 
 int NFP_FL_OUT_FLAGS_USE_TUN ; 
 int NFP_FL_PORT_TYPE_TUN ; 
 void* cpu_to_be16 (int) ; 
 void* cpu_to_be32 (int) ; 
 scalar_t__ netif_is_lag_master (struct net_device*) ; 
 int /*<<< orphan*/  nfp_fl_netdev_is_tunnel_type (struct net_device*,int) ; 
 int nfp_flower_lag_get_output_id (struct nfp_app*,struct net_device*) ; 
 int /*<<< orphan*/  nfp_netdev_is_nfp_repr (struct net_device*) ; 
 int nfp_repr_get_port_id (struct net_device*) ; 
 int /*<<< orphan*/  switchdev_port_same_parent_id (struct net_device*,struct net_device*) ; 
 struct net_device* tcf_mirred_dev (struct tc_action const*) ; 

__attribute__((used)) static int
nfp_fl_output(struct nfp_app *app, struct nfp_fl_output *output,
	      const struct tc_action *action, struct nfp_fl_payload *nfp_flow,
	      bool last, struct net_device *in_dev,
	      enum nfp_flower_tun_type tun_type, int *tun_out_cnt)
{
	size_t act_size = sizeof(struct nfp_fl_output);
	struct nfp_flower_priv *priv = app->priv;
	struct net_device *out_dev;
	u16 tmp_flags;

	output->head.jump_id = NFP_FL_ACTION_OPCODE_OUTPUT;
	output->head.len_lw = act_size >> NFP_FL_LW_SIZ;

	out_dev = tcf_mirred_dev(action);
	if (!out_dev)
		return -EOPNOTSUPP;

	tmp_flags = last ? NFP_FL_OUT_FLAGS_LAST : 0;

	if (tun_type) {
		/* Verify the egress netdev matches the tunnel type. */
		if (!nfp_fl_netdev_is_tunnel_type(out_dev, tun_type))
			return -EOPNOTSUPP;

		if (*tun_out_cnt)
			return -EOPNOTSUPP;
		(*tun_out_cnt)++;

		output->flags = cpu_to_be16(tmp_flags |
					    NFP_FL_OUT_FLAGS_USE_TUN);
		output->port = cpu_to_be32(NFP_FL_PORT_TYPE_TUN | tun_type);
	} else if (netif_is_lag_master(out_dev) &&
		   priv->flower_ext_feats & NFP_FL_FEATS_LAG) {
		int gid;

		output->flags = cpu_to_be16(tmp_flags);
		gid = nfp_flower_lag_get_output_id(app, out_dev);
		if (gid < 0)
			return gid;
		output->port = cpu_to_be32(NFP_FL_LAG_OUT | gid);
	} else {
		/* Set action output parameters. */
		output->flags = cpu_to_be16(tmp_flags);

		/* Only offload if egress ports are on the same device as the
		 * ingress port.
		 */
		if (!switchdev_port_same_parent_id(in_dev, out_dev))
			return -EOPNOTSUPP;
		if (!nfp_netdev_is_nfp_repr(out_dev))
			return -EOPNOTSUPP;

		output->port = cpu_to_be32(nfp_repr_get_port_id(out_dev));
		if (!output->port)
			return -EOPNOTSUPP;
	}
	nfp_flow->meta.shortcut = output->port;

	return 0;
}