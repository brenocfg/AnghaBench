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
typedef  int u8 ;
struct mlxsw_sp_port {int dummy; } ;
struct mlxsw_sp {int* ports; int* port_to_module; int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 
 int* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 unsigned int mlxsw_core_max_ports (int /*<<< orphan*/ ) ; 
 int mlxsw_sp_cpu_port_create (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_cpu_port_remove (struct mlxsw_sp*) ; 
 int mlxsw_sp_port_create (struct mlxsw_sp*,int,int,int,int,int) ; 
 scalar_t__ mlxsw_sp_port_created (struct mlxsw_sp*,int) ; 
 int mlxsw_sp_port_module_info_get (struct mlxsw_sp*,int,int*,int*,int*) ; 
 int /*<<< orphan*/  mlxsw_sp_port_remove (struct mlxsw_sp*,int) ; 

__attribute__((used)) static int mlxsw_sp_ports_create(struct mlxsw_sp *mlxsw_sp)
{
	unsigned int max_ports = mlxsw_core_max_ports(mlxsw_sp->core);
	u8 module, width, lane;
	size_t alloc_size;
	int i;
	int err;

	alloc_size = sizeof(struct mlxsw_sp_port *) * max_ports;
	mlxsw_sp->ports = kzalloc(alloc_size, GFP_KERNEL);
	if (!mlxsw_sp->ports)
		return -ENOMEM;

	mlxsw_sp->port_to_module = kmalloc_array(max_ports, sizeof(int),
						 GFP_KERNEL);
	if (!mlxsw_sp->port_to_module) {
		err = -ENOMEM;
		goto err_port_to_module_alloc;
	}

	err = mlxsw_sp_cpu_port_create(mlxsw_sp);
	if (err)
		goto err_cpu_port_create;

	for (i = 1; i < max_ports; i++) {
		/* Mark as invalid */
		mlxsw_sp->port_to_module[i] = -1;

		err = mlxsw_sp_port_module_info_get(mlxsw_sp, i, &module,
						    &width, &lane);
		if (err)
			goto err_port_module_info_get;
		if (!width)
			continue;
		mlxsw_sp->port_to_module[i] = module;
		err = mlxsw_sp_port_create(mlxsw_sp, i, false,
					   module, width, lane);
		if (err)
			goto err_port_create;
	}
	return 0;

err_port_create:
err_port_module_info_get:
	for (i--; i >= 1; i--)
		if (mlxsw_sp_port_created(mlxsw_sp, i))
			mlxsw_sp_port_remove(mlxsw_sp, i);
	mlxsw_sp_cpu_port_remove(mlxsw_sp);
err_cpu_port_create:
	kfree(mlxsw_sp->port_to_module);
err_port_to_module_alloc:
	kfree(mlxsw_sp->ports);
	return err;
}