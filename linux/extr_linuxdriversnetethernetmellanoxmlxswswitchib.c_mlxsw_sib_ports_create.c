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
typedef  int /*<<< orphan*/  u8 ;
struct mlxsw_sib_port {int dummy; } ;
struct mlxsw_sib {int /*<<< orphan*/  ports; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MLXSW_PORT_MAX_IB_PORTS ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int mlxsw_sib_port_create (struct mlxsw_sib*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mlxsw_sib_port_created (struct mlxsw_sib*,int) ; 
 int mlxsw_sib_port_module_info_get (struct mlxsw_sib*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sib_port_remove (struct mlxsw_sib*,int) ; 

__attribute__((used)) static int mlxsw_sib_ports_create(struct mlxsw_sib *mlxsw_sib)
{
	size_t alloc_size;
	u8 module, width;
	int i;
	int err;

	alloc_size = sizeof(struct mlxsw_sib_port *) * MLXSW_PORT_MAX_IB_PORTS;
	mlxsw_sib->ports = kzalloc(alloc_size, GFP_KERNEL);
	if (!mlxsw_sib->ports)
		return -ENOMEM;

	for (i = 1; i < MLXSW_PORT_MAX_IB_PORTS; i++) {
		err = mlxsw_sib_port_module_info_get(mlxsw_sib, i, &module,
						     &width);
		if (err)
			goto err_port_module_info_get;
		if (!width)
			continue;
		err = mlxsw_sib_port_create(mlxsw_sib, i, module, width);
		if (err)
			goto err_port_create;
	}
	return 0;

err_port_create:
err_port_module_info_get:
	for (i--; i >= 1; i--)
		if (mlxsw_sib_port_created(mlxsw_sib, i))
			mlxsw_sib_port_remove(mlxsw_sib, i);
	kfree(mlxsw_sib->ports);
	return err;
}