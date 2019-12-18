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
struct mlxsw_sx_port {int /*<<< orphan*/  dev; } ;
typedef  enum mlxsw_reg_pude_oper_status { ____Placeholder_mlxsw_reg_pude_oper_status } mlxsw_reg_pude_oper_status ;

/* Variables and functions */
 int MLXSW_PORT_OPER_STATUS_UP ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_sx_pude_eth_event_func(struct mlxsw_sx_port *mlxsw_sx_port,
					 enum mlxsw_reg_pude_oper_status status)
{
	if (status == MLXSW_PORT_OPER_STATUS_UP) {
		netdev_info(mlxsw_sx_port->dev, "link up\n");
		netif_carrier_on(mlxsw_sx_port->dev);
	} else {
		netdev_info(mlxsw_sx_port->dev, "link down\n");
		netif_carrier_off(mlxsw_sx_port->dev);
	}
}