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
struct mlxsw_core_port {int dummy; } ;
struct mlxsw_core {int /*<<< orphan*/  ports; scalar_t__ max_ports; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX_SYSTEM_PORT ; 
 scalar_t__ MLXSW_CORE_RES_GET (struct mlxsw_core*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLXSW_CORE_RES_VALID (struct mlxsw_core*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLXSW_PORT_MAX_PORTS_DEFAULT ; 
 int /*<<< orphan*/  kcalloc (scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxsw_ports_init(struct mlxsw_core *mlxsw_core)
{
	/* Switch ports are numbered from 1 to queried value */
	if (MLXSW_CORE_RES_VALID(mlxsw_core, MAX_SYSTEM_PORT))
		mlxsw_core->max_ports = MLXSW_CORE_RES_GET(mlxsw_core,
							   MAX_SYSTEM_PORT) + 1;
	else
		mlxsw_core->max_ports = MLXSW_PORT_MAX_PORTS_DEFAULT + 1;

	mlxsw_core->ports = kcalloc(mlxsw_core->max_ports,
				    sizeof(struct mlxsw_core_port), GFP_KERNEL);
	if (!mlxsw_core->ports)
		return -ENOMEM;

	return 0;
}