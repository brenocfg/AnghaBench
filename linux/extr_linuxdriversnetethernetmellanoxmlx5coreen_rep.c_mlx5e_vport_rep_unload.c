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
struct net_device {int dummy; } ;
struct mlx5e_rep_priv {struct net_device* netdev; } ;
struct mlx5e_priv {TYPE_2__* mdev; void* ppriv; } ;
struct mlx5_eswitch_rep {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  eswitch; } ;
struct TYPE_4__ {TYPE_1__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  REP_ETH ; 
 int /*<<< orphan*/  kfree (void*) ; 
 struct mlx5e_rep_priv* mlx5_eswitch_get_uplink_priv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_destroy_netdev (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_detach_netdev (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_rep_neigh_cleanup (struct mlx5e_rep_priv*) ; 
 int /*<<< orphan*/  mlx5e_rep_setup_tc_cb_egdev ; 
 struct mlx5e_rep_priv* mlx5e_rep_to_rep_priv (struct mlx5_eswitch_rep*) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  tc_setup_cb_egdev_unregister (struct net_device*,int /*<<< orphan*/ ,struct mlx5e_priv*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void
mlx5e_vport_rep_unload(struct mlx5_eswitch_rep *rep)
{
	struct mlx5e_rep_priv *rpriv = mlx5e_rep_to_rep_priv(rep);
	struct net_device *netdev = rpriv->netdev;
	struct mlx5e_priv *priv = netdev_priv(netdev);
	struct mlx5e_rep_priv *uplink_rpriv;
	void *ppriv = priv->ppriv;
	struct mlx5e_priv *upriv;

	unregister_netdev(netdev);
	uplink_rpriv = mlx5_eswitch_get_uplink_priv(priv->mdev->priv.eswitch,
						    REP_ETH);
	upriv = netdev_priv(uplink_rpriv->netdev);
	tc_setup_cb_egdev_unregister(netdev, mlx5e_rep_setup_tc_cb_egdev,
				     upriv);
	mlx5e_rep_neigh_cleanup(rpriv);
	mlx5e_detach_netdev(priv);
	mlx5e_destroy_netdev(priv);
	kfree(ppriv); /* mlx5e_rep_priv */
}