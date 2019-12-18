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
struct mlxsw_sp_mr_tcam_route {scalar_t__ action; int /*<<< orphan*/  irif_index; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MLXSW_SP_MR_ROUTE_ACTION_TRAP ; 

__attribute__((used)) static int mlxsw_sp_mr_tcam_route_irif_update(struct mlxsw_sp *mlxsw_sp,
					      void *route_priv, u16 irif_index)
{
	struct mlxsw_sp_mr_tcam_route *route = route_priv;

	if (route->action != MLXSW_SP_MR_ROUTE_ACTION_TRAP)
		return -EINVAL;
	route->irif_index = irif_index;
	return 0;
}