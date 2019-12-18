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
struct mlxsw_m {int dummy; } ;
struct mlxsw_core {int dummy; } ;

/* Variables and functions */
 struct mlxsw_m* mlxsw_core_driver_priv (struct mlxsw_core*) ; 
 int /*<<< orphan*/  mlxsw_m_ports_remove (struct mlxsw_m*) ; 

__attribute__((used)) static void mlxsw_m_fini(struct mlxsw_core *mlxsw_core)
{
	struct mlxsw_m *mlxsw_m = mlxsw_core_driver_priv(mlxsw_core);

	mlxsw_m_ports_remove(mlxsw_m);
}