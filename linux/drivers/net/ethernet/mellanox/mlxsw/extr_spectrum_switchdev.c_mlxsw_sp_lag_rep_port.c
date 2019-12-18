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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_sp_port {int dummy; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_LAG_MEMBERS ; 
 int MLXSW_CORE_RES_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlxsw_sp_port* mlxsw_sp_port_lagged_get (struct mlxsw_sp*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct mlxsw_sp_port *mlxsw_sp_lag_rep_port(struct mlxsw_sp *mlxsw_sp,
						   u16 lag_id)
{
	struct mlxsw_sp_port *mlxsw_sp_port;
	u64 max_lag_members;
	int i;

	max_lag_members = MLXSW_CORE_RES_GET(mlxsw_sp->core,
					     MAX_LAG_MEMBERS);
	for (i = 0; i < max_lag_members; i++) {
		mlxsw_sp_port = mlxsw_sp_port_lagged_get(mlxsw_sp, lag_id, i);
		if (mlxsw_sp_port)
			return mlxsw_sp_port;
	}
	return NULL;
}