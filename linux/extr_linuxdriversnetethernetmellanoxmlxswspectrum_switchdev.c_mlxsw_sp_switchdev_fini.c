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
struct mlxsw_sp {TYPE_1__* bridge; } ;
struct TYPE_2__ {int /*<<< orphan*/  bridges_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_fdb_fini (struct mlxsw_sp*) ; 

void mlxsw_sp_switchdev_fini(struct mlxsw_sp *mlxsw_sp)
{
	mlxsw_sp_fdb_fini(mlxsw_sp);
	WARN_ON(!list_empty(&mlxsw_sp->bridge->bridges_list));
	kfree(mlxsw_sp->bridge);
}