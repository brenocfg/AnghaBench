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
struct mlxsw_sp {TYPE_1__* router; } ;
struct TYPE_2__ {int /*<<< orphan*/  ipip_list; int /*<<< orphan*/  ipip_ops_arr; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int mlxsw_sp_ipip_config_tigcr (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_ipip_ops_arr ; 

__attribute__((used)) static int mlxsw_sp_ipips_init(struct mlxsw_sp *mlxsw_sp)
{
	mlxsw_sp->router->ipip_ops_arr = mlxsw_sp_ipip_ops_arr;
	INIT_LIST_HEAD(&mlxsw_sp->router->ipip_list);
	return mlxsw_sp_ipip_config_tigcr(mlxsw_sp);
}