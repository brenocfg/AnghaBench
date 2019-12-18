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
struct net_device {int real_num_tx_queues; } ;
struct TYPE_4__ {int num_tc; } ;
struct mlx5e_channels {int num; TYPE_2__ params; } ;
struct mlx5e_priv {TYPE_1__* profile; struct mlx5e_channels channels; struct net_device* netdev; } ;
typedef  int /*<<< orphan*/  (* mlx5e_fp_hw_modify ) (struct mlx5e_priv*) ;
struct TYPE_3__ {int /*<<< orphan*/  (* update_rx ) (struct mlx5e_priv*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5e_activate_priv_channels (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_close_channels (struct mlx5e_channels*) ; 
 int /*<<< orphan*/  mlx5e_deactivate_priv_channels (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  netif_set_real_num_tx_queues (struct net_device*,int) ; 
 int /*<<< orphan*/  stub1 (struct mlx5e_priv*) ; 

__attribute__((used)) static void mlx5e_switch_priv_channels(struct mlx5e_priv *priv,
				       struct mlx5e_channels *new_chs,
				       mlx5e_fp_hw_modify hw_modify)
{
	struct net_device *netdev = priv->netdev;
	int new_num_txqs;
	int carrier_ok;

	new_num_txqs = new_chs->num * new_chs->params.num_tc;

	carrier_ok = netif_carrier_ok(netdev);
	netif_carrier_off(netdev);

	if (new_num_txqs < netdev->real_num_tx_queues)
		netif_set_real_num_tx_queues(netdev, new_num_txqs);

	mlx5e_deactivate_priv_channels(priv);
	mlx5e_close_channels(&priv->channels);

	priv->channels = *new_chs;

	/* New channels are ready to roll, modify HW settings if needed */
	if (hw_modify)
		hw_modify(priv);

	priv->profile->update_rx(priv);
	mlx5e_activate_priv_channels(priv);

	/* return carrier back if needed */
	if (carrier_ok)
		netif_carrier_on(netdev);
}