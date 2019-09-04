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
typedef  int /*<<< orphan*/  u8 ;
struct mlxsw_sib {int /*<<< orphan*/  core; TYPE_1__* bus_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int __mlxsw_sib_port_create (struct mlxsw_sib*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_core_port_fini (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_core_port_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxsw_sib_port_create(struct mlxsw_sib *mlxsw_sib, u8 local_port,
				 u8 module, u8 width)
{
	int err;

	err = mlxsw_core_port_init(mlxsw_sib->core, local_port);
	if (err) {
		dev_err(mlxsw_sib->bus_info->dev, "Port %d: Failed to init core port\n",
			local_port);
		return err;
	}
	err = __mlxsw_sib_port_create(mlxsw_sib, local_port, module, width);
	if (err)
		goto err_port_create;

	return 0;

err_port_create:
	mlxsw_core_port_fini(mlxsw_sib->core, local_port);
	return err;
}