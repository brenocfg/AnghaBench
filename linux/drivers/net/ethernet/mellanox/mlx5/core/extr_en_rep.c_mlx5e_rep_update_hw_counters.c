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
struct rtnl_link_stats64 {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct mlx5e_rep_priv {struct mlx5_eswitch_rep* rep; } ;
struct TYPE_4__ {struct rtnl_link_stats64 vf_vport; } ;
struct mlx5e_priv {TYPE_1__ stats; struct mlx5e_rep_priv* ppriv; TYPE_2__* mdev; } ;
struct mlx5_eswitch_rep {int /*<<< orphan*/  vport; } ;
struct mlx5_eswitch {int dummy; } ;
struct ifla_vf_stats {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct TYPE_6__ {struct mlx5_eswitch* eswitch; } ;
struct TYPE_5__ {TYPE_3__ priv; } ;

/* Variables and functions */
 int mlx5_eswitch_get_vport_stats (struct mlx5_eswitch*,int /*<<< orphan*/ ,struct ifla_vf_stats*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mlx5e_rep_update_hw_counters(struct mlx5e_priv *priv)
{
	struct mlx5_eswitch *esw = priv->mdev->priv.eswitch;
	struct mlx5e_rep_priv *rpriv = priv->ppriv;
	struct mlx5_eswitch_rep *rep = rpriv->rep;
	struct rtnl_link_stats64 *vport_stats;
	struct ifla_vf_stats vf_stats;
	int err;

	err = mlx5_eswitch_get_vport_stats(esw, rep->vport, &vf_stats);
	if (err) {
		pr_warn("vport %d error %d reading stats\n", rep->vport, err);
		return;
	}

	vport_stats = &priv->stats.vf_vport;
	/* flip tx/rx as we are reporting the counters for the switch vport */
	vport_stats->rx_packets = vf_stats.tx_packets;
	vport_stats->rx_bytes   = vf_stats.tx_bytes;
	vport_stats->tx_packets = vf_stats.rx_packets;
	vport_stats->tx_bytes   = vf_stats.rx_bytes;
}