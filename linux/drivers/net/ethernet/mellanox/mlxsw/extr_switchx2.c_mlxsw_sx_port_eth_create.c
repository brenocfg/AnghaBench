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
typedef  scalar_t__ u8 ;
struct mlxsw_sx {int /*<<< orphan*/  core; TYPE_1__* bus_info; int /*<<< orphan*/  hw_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int __mlxsw_sx_port_eth_create (struct mlxsw_sx*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  mlxsw_core_port_fini (int /*<<< orphan*/ ,scalar_t__) ; 
 int mlxsw_core_port_init (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mlxsw_sx_port_eth_create(struct mlxsw_sx *mlxsw_sx, u8 local_port,
				    u8 module, u8 width)
{
	int err;

	err = mlxsw_core_port_init(mlxsw_sx->core, local_port,
				   module + 1, false, 0,
				   mlxsw_sx->hw_id, sizeof(mlxsw_sx->hw_id));
	if (err) {
		dev_err(mlxsw_sx->bus_info->dev, "Port %d: Failed to init core port\n",
			local_port);
		return err;
	}
	err = __mlxsw_sx_port_eth_create(mlxsw_sx, local_port, module, width);
	if (err)
		goto err_port_create;

	return 0;

err_port_create:
	mlxsw_core_port_fini(mlxsw_sx->core, local_port);
	return err;
}