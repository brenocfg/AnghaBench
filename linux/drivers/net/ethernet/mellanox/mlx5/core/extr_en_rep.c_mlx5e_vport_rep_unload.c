#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct net_device {int dummy; } ;
struct mlx5e_rep_priv {int /*<<< orphan*/  dl_port; struct net_device* netdev; } ;
struct mlx5e_priv {struct mlx5_core_dev* mdev; void* ppriv; } ;
struct mlx5_eswitch_rep {scalar_t__ vport; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ MLX5_VPORT_UPLINK ; 
 int /*<<< orphan*/  devlink_port_type_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ is_devlink_port_supported (struct mlx5_core_dev*,struct mlx5e_rep_priv*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  mlx5e_destroy_mdev_resources (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5e_destroy_netdev (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_detach_netdev (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_rep_neigh_cleanup (struct mlx5e_rep_priv*) ; 
 struct mlx5e_rep_priv* mlx5e_rep_to_rep_priv (struct mlx5_eswitch_rep*) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  unregister_devlink_port (struct mlx5_core_dev*,struct mlx5e_rep_priv*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void
mlx5e_vport_rep_unload(struct mlx5_eswitch_rep *rep)
{
	struct mlx5e_rep_priv *rpriv = mlx5e_rep_to_rep_priv(rep);
	struct net_device *netdev = rpriv->netdev;
	struct mlx5e_priv *priv = netdev_priv(netdev);
	struct mlx5_core_dev *dev = priv->mdev;
	void *ppriv = priv->ppriv;

	if (is_devlink_port_supported(dev, rpriv))
		devlink_port_type_clear(&rpriv->dl_port);
	unregister_netdev(netdev);
	unregister_devlink_port(dev, rpriv);
	mlx5e_rep_neigh_cleanup(rpriv);
	mlx5e_detach_netdev(priv);
	if (rep->vport == MLX5_VPORT_UPLINK)
		mlx5e_destroy_mdev_resources(priv->mdev);
	mlx5e_destroy_netdev(priv);
	kfree(ppriv); /* mlx5e_rep_priv */
}