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
struct net_device {scalar_t__ reg_state; } ;
struct mlx5e_priv {int /*<<< orphan*/  set_rx_mode_work; int /*<<< orphan*/  wq; struct mlx5_core_dev* mdev; struct net_device* netdev; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_PORT_DOWN ; 
 scalar_t__ NETREG_REGISTERED ; 
 int /*<<< orphan*/  mlx5_lag_add (struct mlx5_core_dev*,struct net_device*) ; 
 int /*<<< orphan*/  mlx5_set_port_admin_status (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_dcbnl_init_app (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_enable_async_events (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_hv_vhca_stats_create (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_init_l2_addr (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_monitor_counter_init (struct mlx5e_priv*) ; 
 scalar_t__ mlx5e_monitor_counter_supported (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_open (struct net_device*) ; 
 int /*<<< orphan*/  mlx5e_set_dev_port_mtu (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_set_netdev_mtu_boundaries (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  netif_device_attach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static void mlx5e_nic_enable(struct mlx5e_priv *priv)
{
	struct net_device *netdev = priv->netdev;
	struct mlx5_core_dev *mdev = priv->mdev;

	mlx5e_init_l2_addr(priv);

	/* Marking the link as currently not needed by the Driver */
	if (!netif_running(netdev))
		mlx5_set_port_admin_status(mdev, MLX5_PORT_DOWN);

	mlx5e_set_netdev_mtu_boundaries(priv);
	mlx5e_set_dev_port_mtu(priv);

	mlx5_lag_add(mdev, netdev);

	mlx5e_enable_async_events(priv);
	if (mlx5e_monitor_counter_supported(priv))
		mlx5e_monitor_counter_init(priv);

	mlx5e_hv_vhca_stats_create(priv);
	if (netdev->reg_state != NETREG_REGISTERED)
		return;
#ifdef CONFIG_MLX5_CORE_EN_DCB
	mlx5e_dcbnl_init_app(priv);
#endif

	queue_work(priv->wq, &priv->set_rx_mode_work);

	rtnl_lock();
	if (netif_running(netdev))
		mlx5e_open(netdev);
	netif_device_attach(netdev);
	rtnl_unlock();
}