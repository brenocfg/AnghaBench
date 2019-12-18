#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct net_device {int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; } ;
struct mlxsw_m_port {size_t local_port; size_t module; struct mlxsw_m* mlxsw_m; struct net_device* dev; } ;
struct mlxsw_m {int /*<<< orphan*/  core; struct mlxsw_m_port** ports; TYPE_1__* bus_info; int /*<<< orphan*/  base_mac; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ ) ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  mlxsw_core_port_eth_set (int /*<<< orphan*/ ,size_t,struct mlxsw_m_port*,struct net_device*) ; 
 int /*<<< orphan*/  mlxsw_core_port_fini (int /*<<< orphan*/ ,size_t) ; 
 int mlxsw_core_port_init (int /*<<< orphan*/ ,size_t,size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mlxsw_m_port_dev_addr_get (struct mlxsw_m_port*) ; 
 int /*<<< orphan*/  mlxsw_m_port_ethtool_ops ; 
 int /*<<< orphan*/  mlxsw_m_port_netdev_ops ; 
 struct mlxsw_m_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int register_netdev (struct net_device*) ; 

__attribute__((used)) static int
mlxsw_m_port_create(struct mlxsw_m *mlxsw_m, u8 local_port, u8 module)
{
	struct mlxsw_m_port *mlxsw_m_port;
	struct net_device *dev;
	int err;

	err = mlxsw_core_port_init(mlxsw_m->core, local_port,
				   module + 1, false, 0,
				   mlxsw_m->base_mac,
				   sizeof(mlxsw_m->base_mac));
	if (err) {
		dev_err(mlxsw_m->bus_info->dev, "Port %d: Failed to init core port\n",
			local_port);
		return err;
	}

	dev = alloc_etherdev(sizeof(struct mlxsw_m_port));
	if (!dev) {
		err = -ENOMEM;
		goto err_alloc_etherdev;
	}

	SET_NETDEV_DEV(dev, mlxsw_m->bus_info->dev);
	mlxsw_m_port = netdev_priv(dev);
	mlxsw_m_port->dev = dev;
	mlxsw_m_port->mlxsw_m = mlxsw_m;
	mlxsw_m_port->local_port = local_port;
	mlxsw_m_port->module = module;

	dev->netdev_ops = &mlxsw_m_port_netdev_ops;
	dev->ethtool_ops = &mlxsw_m_port_ethtool_ops;

	err = mlxsw_m_port_dev_addr_get(mlxsw_m_port);
	if (err) {
		dev_err(mlxsw_m->bus_info->dev, "Port %d: Unable to get port mac address\n",
			mlxsw_m_port->local_port);
		goto err_dev_addr_get;
	}

	netif_carrier_off(dev);
	mlxsw_m->ports[local_port] = mlxsw_m_port;
	err = register_netdev(dev);
	if (err) {
		dev_err(mlxsw_m->bus_info->dev, "Port %d: Failed to register netdev\n",
			mlxsw_m_port->local_port);
		goto err_register_netdev;
	}

	mlxsw_core_port_eth_set(mlxsw_m->core, mlxsw_m_port->local_port,
				mlxsw_m_port, dev);

	return 0;

err_register_netdev:
	mlxsw_m->ports[local_port] = NULL;
	free_netdev(dev);
err_dev_addr_get:
err_alloc_etherdev:
	mlxsw_core_port_fini(mlxsw_m->core, local_port);
	return err;
}