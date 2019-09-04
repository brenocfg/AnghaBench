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
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_sp_mr_tcam_route {scalar_t__ action; int /*<<< orphan*/  erif_list; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 scalar_t__ MLXSW_SP_MR_ROUTE_ACTION_TRAP ; 
 int mlxsw_sp_mr_erif_list_add (struct mlxsw_sp*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mlxsw_sp_mr_erif_list_commit (struct mlxsw_sp*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlxsw_sp_mr_tcam_route_erif_add(struct mlxsw_sp *mlxsw_sp,
					   void *route_priv, u16 erif_index)
{
	struct mlxsw_sp_mr_tcam_route *route = route_priv;
	int err;

	err = mlxsw_sp_mr_erif_list_add(mlxsw_sp, &route->erif_list,
					erif_index);
	if (err)
		return err;

	/* Commit the action only if the route action is not TRAP */
	if (route->action != MLXSW_SP_MR_ROUTE_ACTION_TRAP)
		return mlxsw_sp_mr_erif_list_commit(mlxsw_sp,
						    &route->erif_list);
	return 0;
}