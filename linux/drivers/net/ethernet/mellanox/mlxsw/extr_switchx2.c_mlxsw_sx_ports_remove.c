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
struct mlxsw_sx {int /*<<< orphan*/  ports; int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int mlxsw_core_max_ports (int /*<<< orphan*/ ) ; 
 scalar_t__ mlxsw_sx_port_created (struct mlxsw_sx*,int) ; 
 int /*<<< orphan*/  mlxsw_sx_port_remove (struct mlxsw_sx*,int) ; 

__attribute__((used)) static void mlxsw_sx_ports_remove(struct mlxsw_sx *mlxsw_sx)
{
	int i;

	for (i = 1; i < mlxsw_core_max_ports(mlxsw_sx->core); i++)
		if (mlxsw_sx_port_created(mlxsw_sx, i))
			mlxsw_sx_port_remove(mlxsw_sx, i);
	kfree(mlxsw_sx->ports);
}