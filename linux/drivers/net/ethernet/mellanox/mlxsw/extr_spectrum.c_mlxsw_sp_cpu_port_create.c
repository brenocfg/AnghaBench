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
struct mlxsw_sp_port {size_t local_port; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {struct mlxsw_sp_port** ports; TYPE_1__* bus_info; int /*<<< orphan*/  base_mac; int /*<<< orphan*/  core; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t MLXSW_PORT_CPU_PORT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_port*) ; 
 struct mlxsw_sp_port* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mlxsw_core_cpu_port_init (int /*<<< orphan*/ ,struct mlxsw_sp_port*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mlxsw_sp_cpu_port_create(struct mlxsw_sp *mlxsw_sp)
{
	struct mlxsw_sp_port *mlxsw_sp_port;
	int err;

	mlxsw_sp_port = kzalloc(sizeof(*mlxsw_sp_port), GFP_KERNEL);
	if (!mlxsw_sp_port)
		return -ENOMEM;

	mlxsw_sp_port->mlxsw_sp = mlxsw_sp;
	mlxsw_sp_port->local_port = MLXSW_PORT_CPU_PORT;

	err = mlxsw_core_cpu_port_init(mlxsw_sp->core,
				       mlxsw_sp_port,
				       mlxsw_sp->base_mac,
				       sizeof(mlxsw_sp->base_mac));
	if (err) {
		dev_err(mlxsw_sp->bus_info->dev, "Failed to initialize core CPU port\n");
		goto err_core_cpu_port_init;
	}

	mlxsw_sp->ports[MLXSW_PORT_CPU_PORT] = mlxsw_sp_port;
	return 0;

err_core_cpu_port_init:
	kfree(mlxsw_sp_port);
	return err;
}