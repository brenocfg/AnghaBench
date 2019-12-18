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
struct mlxsw_sp {int /*<<< orphan*/  listeners_count; int /*<<< orphan*/  listeners; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_listener ; 
 int /*<<< orphan*/  mlxsw_sp_traps_unregister (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_sp_traps_fini(struct mlxsw_sp *mlxsw_sp)
{
	mlxsw_sp_traps_unregister(mlxsw_sp, mlxsw_sp->listeners,
				  mlxsw_sp->listeners_count);
	mlxsw_sp_traps_unregister(mlxsw_sp, mlxsw_sp_listener,
				  ARRAY_SIZE(mlxsw_sp_listener));
}