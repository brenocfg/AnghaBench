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
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_pause; int /*<<< orphan*/  rx_pause; } ;
struct mlxsw_sp_port {TYPE_1__ link; } ;
struct ethtool_pauseparam {int /*<<< orphan*/  tx_pause; int /*<<< orphan*/  rx_pause; } ;

/* Variables and functions */
 struct mlxsw_sp_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void mlxsw_sp_port_get_pauseparam(struct net_device *dev,
					 struct ethtool_pauseparam *pause)
{
	struct mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);

	pause->rx_pause = mlxsw_sp_port->link.rx_pause;
	pause->tx_pause = mlxsw_sp_port->link.tx_pause;
}