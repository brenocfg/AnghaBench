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
struct mlxsw_sp_vr {int /*<<< orphan*/ * mr_table; } ;
struct mlxsw_sp {TYPE_1__* router; int /*<<< orphan*/  core; } ;
struct TYPE_2__ {struct mlxsw_sp_vr* vrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_VRS ; 
 int MLXSW_CORE_RES_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_SP_L3_PROTO_IPV4 ; 
 int /*<<< orphan*/  MLXSW_SP_L3_PROTO_IPV6 ; 
 int MLXSW_SP_L3_PROTO_MAX ; 
 int /*<<< orphan*/  mlxsw_sp_mr_table_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_vr_fib_flush (struct mlxsw_sp*,struct mlxsw_sp_vr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_vr_is_used (struct mlxsw_sp_vr*) ; 

__attribute__((used)) static void mlxsw_sp_router_fib_flush(struct mlxsw_sp *mlxsw_sp)
{
	int i, j;

	for (i = 0; i < MLXSW_CORE_RES_GET(mlxsw_sp->core, MAX_VRS); i++) {
		struct mlxsw_sp_vr *vr = &mlxsw_sp->router->vrs[i];

		if (!mlxsw_sp_vr_is_used(vr))
			continue;

		for (j = 0; j < MLXSW_SP_L3_PROTO_MAX; j++)
			mlxsw_sp_mr_table_flush(vr->mr_table[j]);
		mlxsw_sp_vr_fib_flush(mlxsw_sp, vr, MLXSW_SP_L3_PROTO_IPV4);

		/* If virtual router was only used for IPv4, then it's no
		 * longer used.
		 */
		if (!mlxsw_sp_vr_is_used(vr))
			continue;
		mlxsw_sp_vr_fib_flush(mlxsw_sp, vr, MLXSW_SP_L3_PROTO_IPV6);
	}
}