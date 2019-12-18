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
struct net_device {int /*<<< orphan*/ * dev_addr; } ;
struct mlxsw_sx_port {scalar_t__ local_port; struct net_device* dev; struct mlxsw_sx* mlxsw_sx; } ;
struct mlxsw_sx {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_PPAD_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_ppad_mac_memcpy_from (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_reg_ppad_pack (char*,int,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ppad ; 

__attribute__((used)) static int mlxsw_sx_port_dev_addr_get(struct mlxsw_sx_port *mlxsw_sx_port)
{
	struct mlxsw_sx *mlxsw_sx = mlxsw_sx_port->mlxsw_sx;
	struct net_device *dev = mlxsw_sx_port->dev;
	char ppad_pl[MLXSW_REG_PPAD_LEN];
	int err;

	mlxsw_reg_ppad_pack(ppad_pl, false, 0);
	err = mlxsw_reg_query(mlxsw_sx->core, MLXSW_REG(ppad), ppad_pl);
	if (err)
		return err;
	mlxsw_reg_ppad_mac_memcpy_from(ppad_pl, dev->dev_addr);
	/* The last byte value in base mac address is guaranteed
	 * to be such it does not overflow when adding local_port
	 * value.
	 */
	dev->dev_addr[ETH_ALEN - 1] += mlxsw_sx_port->local_port;
	return 0;
}