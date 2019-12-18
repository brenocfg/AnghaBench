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
struct mlxsw_sib {int /*<<< orphan*/  ports; } ;

/* Variables and functions */
 int MLXSW_PORT_MAX_IB_PORTS ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 scalar_t__ mlxsw_sib_port_created (struct mlxsw_sib*,int) ; 
 int /*<<< orphan*/  mlxsw_sib_port_remove (struct mlxsw_sib*,int) ; 

__attribute__((used)) static void mlxsw_sib_ports_remove(struct mlxsw_sib *mlxsw_sib)
{
	int i;

	for (i = 1; i < MLXSW_PORT_MAX_IB_PORTS; i++)
		if (mlxsw_sib_port_created(mlxsw_sib, i))
			mlxsw_sib_port_remove(mlxsw_sib, i);
	kfree(mlxsw_sib->ports);
}