#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_7__ {int num_tc; } ;
struct TYPE_9__ {int num; TYPE_1__ params; } ;
struct mlx5e_priv {TYPE_3__ channels; struct net_device* netdev; TYPE_2__* profile; } ;
struct TYPE_8__ {int rq_groups; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5e_activate_channels (TYPE_3__*) ; 
 int /*<<< orphan*/  mlx5e_add_sqs_fwd_rules (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_build_tx2sq_maps (struct mlx5e_priv*) ; 
 scalar_t__ mlx5e_is_vport_rep (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_netdev_set_tcs (struct net_device*) ; 
 int /*<<< orphan*/  mlx5e_redirect_rqts_to_channels (struct mlx5e_priv*,TYPE_3__*) ; 
 int /*<<< orphan*/  mlx5e_wait_channels_min_rx_wqes (TYPE_3__*) ; 
 int /*<<< orphan*/  mlx5e_xdp_tx_enable (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_xsk_redirect_rqts_to_channels (struct mlx5e_priv*,TYPE_3__*) ; 
 int /*<<< orphan*/  netif_set_real_num_rx_queues (struct net_device*,int) ; 
 int /*<<< orphan*/  netif_set_real_num_tx_queues (struct net_device*,int) ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (struct net_device*) ; 

void mlx5e_activate_priv_channels(struct mlx5e_priv *priv)
{
	int num_txqs = priv->channels.num * priv->channels.params.num_tc;
	int num_rxqs = priv->channels.num * priv->profile->rq_groups;
	struct net_device *netdev = priv->netdev;

	mlx5e_netdev_set_tcs(netdev);
	netif_set_real_num_tx_queues(netdev, num_txqs);
	netif_set_real_num_rx_queues(netdev, num_rxqs);

	mlx5e_build_tx2sq_maps(priv);
	mlx5e_activate_channels(&priv->channels);
	mlx5e_xdp_tx_enable(priv);
	netif_tx_start_all_queues(priv->netdev);

	if (mlx5e_is_vport_rep(priv))
		mlx5e_add_sqs_fwd_rules(priv);

	mlx5e_wait_channels_min_rx_wqes(&priv->channels);
	mlx5e_redirect_rqts_to_channels(priv, &priv->channels);

	mlx5e_xsk_redirect_rqts_to_channels(priv, &priv->channels);
}