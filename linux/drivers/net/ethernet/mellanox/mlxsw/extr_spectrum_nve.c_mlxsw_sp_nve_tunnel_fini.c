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
struct mlxsw_sp_nve_ops {int /*<<< orphan*/  (* fini ) (struct mlxsw_sp_nve*) ;} ;
struct TYPE_2__ {size_t type; } ;
struct mlxsw_sp_nve {int num_nve_tunnels; TYPE_1__ config; int /*<<< orphan*/  tunnel_index; struct mlxsw_sp_nve_ops** nve_ops_arr; } ;
struct mlxsw_sp {struct mlxsw_sp_nve* nve; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_SP_KVDL_ENTRY_TYPE_ADJ ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlxsw_sp_kvdl_free (struct mlxsw_sp*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mlxsw_sp_nve*) ; 

__attribute__((used)) static void mlxsw_sp_nve_tunnel_fini(struct mlxsw_sp *mlxsw_sp)
{
	struct mlxsw_sp_nve *nve = mlxsw_sp->nve;
	const struct mlxsw_sp_nve_ops *ops;

	ops = nve->nve_ops_arr[nve->config.type];

	if (mlxsw_sp->nve->num_nve_tunnels == 1) {
		ops->fini(nve);
		mlxsw_sp_kvdl_free(mlxsw_sp, MLXSW_SP_KVDL_ENTRY_TYPE_ADJ, 1,
				   nve->tunnel_index);
		memset(&nve->config, 0, sizeof(nve->config));
	}
	nve->num_nve_tunnels--;
}