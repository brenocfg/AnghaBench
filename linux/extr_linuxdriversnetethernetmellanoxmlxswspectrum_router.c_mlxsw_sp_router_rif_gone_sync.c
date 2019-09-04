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
struct mlxsw_sp_rif {int /*<<< orphan*/  rif_index; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_neigh_rif_gone_sync (struct mlxsw_sp*,struct mlxsw_sp_rif*) ; 
 int /*<<< orphan*/  mlxsw_sp_nexthop_rif_gone_sync (struct mlxsw_sp*,struct mlxsw_sp_rif*) ; 
 int /*<<< orphan*/  mlxsw_sp_router_rif_disable (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_sp_router_rif_gone_sync(struct mlxsw_sp *mlxsw_sp,
					  struct mlxsw_sp_rif *rif)
{
	mlxsw_sp_router_rif_disable(mlxsw_sp, rif->rif_index);
	mlxsw_sp_nexthop_rif_gone_sync(mlxsw_sp, rif);
	mlxsw_sp_neigh_rif_gone_sync(mlxsw_sp, rif);
}