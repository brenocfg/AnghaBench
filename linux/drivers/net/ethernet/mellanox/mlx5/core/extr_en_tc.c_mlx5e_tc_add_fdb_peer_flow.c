#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mlx5e_tc_flow_parse_attr {int /*<<< orphan*/  filter_dev; } ;
struct mlx5e_tc_flow {int /*<<< orphan*/  peer; struct mlx5e_tc_flow* peer_flow; TYPE_2__* esw_attr; struct mlx5e_priv* priv; } ;
struct mlx5e_rep_priv {int /*<<< orphan*/  netdev; } ;
struct mlx5e_priv {struct mlx5_core_dev* mdev; } ;
struct TYPE_7__ {int /*<<< orphan*/  peer_mutex; int /*<<< orphan*/  peer_flows; } ;
struct mlx5_eswitch {TYPE_3__ offloads; } ;
struct mlx5_devcom {int dummy; } ;
struct TYPE_5__ {struct mlx5_devcom* devcom; struct mlx5_eswitch* eswitch; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;
struct flow_cls_offload {int dummy; } ;
struct TYPE_8__ {scalar_t__ vport; } ;
struct TYPE_6__ {TYPE_4__* in_rep; struct mlx5e_tc_flow_parse_attr* parse_attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUP ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (struct mlx5e_tc_flow*) ; 
 int /*<<< orphan*/  MLX5_DEVCOM_ESW_OFFLOADS ; 
 scalar_t__ MLX5_VPORT_UPLINK ; 
 int PTR_ERR (struct mlx5e_tc_flow*) ; 
 int /*<<< orphan*/  REP_ETH ; 
 struct mlx5e_tc_flow* __mlx5e_add_fdb_flow (struct mlx5e_priv*,struct flow_cls_offload*,unsigned long,int /*<<< orphan*/ ,TYPE_4__*,struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  flow_flag_set (struct mlx5e_tc_flow*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct mlx5_eswitch* mlx5_devcom_get_peer_data (struct mlx5_devcom*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_devcom_release_peer_data (struct mlx5_devcom*,int /*<<< orphan*/ ) ; 
 struct mlx5e_rep_priv* mlx5_eswitch_get_uplink_priv (struct mlx5_eswitch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mlx5e_priv* netdev_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx5e_tc_add_fdb_peer_flow(struct flow_cls_offload *f,
				      struct mlx5e_tc_flow *flow,
				      unsigned long flow_flags)
{
	struct mlx5e_priv *priv = flow->priv, *peer_priv;
	struct mlx5_eswitch *esw = priv->mdev->priv.eswitch, *peer_esw;
	struct mlx5_devcom *devcom = priv->mdev->priv.devcom;
	struct mlx5e_tc_flow_parse_attr *parse_attr;
	struct mlx5e_rep_priv *peer_urpriv;
	struct mlx5e_tc_flow *peer_flow;
	struct mlx5_core_dev *in_mdev;
	int err = 0;

	peer_esw = mlx5_devcom_get_peer_data(devcom, MLX5_DEVCOM_ESW_OFFLOADS);
	if (!peer_esw)
		return -ENODEV;

	peer_urpriv = mlx5_eswitch_get_uplink_priv(peer_esw, REP_ETH);
	peer_priv = netdev_priv(peer_urpriv->netdev);

	/* in_mdev is assigned of which the packet originated from.
	 * So packets redirected to uplink use the same mdev of the
	 * original flow and packets redirected from uplink use the
	 * peer mdev.
	 */
	if (flow->esw_attr->in_rep->vport == MLX5_VPORT_UPLINK)
		in_mdev = peer_priv->mdev;
	else
		in_mdev = priv->mdev;

	parse_attr = flow->esw_attr->parse_attr;
	peer_flow = __mlx5e_add_fdb_flow(peer_priv, f, flow_flags,
					 parse_attr->filter_dev,
					 flow->esw_attr->in_rep, in_mdev);
	if (IS_ERR(peer_flow)) {
		err = PTR_ERR(peer_flow);
		goto out;
	}

	flow->peer_flow = peer_flow;
	flow_flag_set(flow, DUP);
	mutex_lock(&esw->offloads.peer_mutex);
	list_add_tail(&flow->peer, &esw->offloads.peer_flows);
	mutex_unlock(&esw->offloads.peer_mutex);

out:
	mlx5_devcom_release_peer_data(devcom, MLX5_DEVCOM_ESW_OFFLOADS);
	return err;
}