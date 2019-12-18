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
struct mlxsw_sp_nve_ops {int (* init ) (struct mlxsw_sp_nve*,struct mlxsw_sp_nve_config*) ;} ;
struct mlxsw_sp_nve_config {size_t type; } ;
struct mlxsw_sp_nve {int /*<<< orphan*/  num_nve_tunnels; int /*<<< orphan*/  tunnel_index; struct mlxsw_sp_nve_ops** nve_ops_arr; } ;
struct mlxsw_sp {struct mlxsw_sp_nve* nve; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_SP_KVDL_ENTRY_TYPE_ADJ ; 
 int mlxsw_sp_kvdl_alloc (struct mlxsw_sp*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_kvdl_free (struct mlxsw_sp*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int stub1 (struct mlxsw_sp_nve*,struct mlxsw_sp_nve_config*) ; 

__attribute__((used)) static int mlxsw_sp_nve_tunnel_init(struct mlxsw_sp *mlxsw_sp,
				    struct mlxsw_sp_nve_config *config)
{
	struct mlxsw_sp_nve *nve = mlxsw_sp->nve;
	const struct mlxsw_sp_nve_ops *ops;
	int err;

	if (nve->num_nve_tunnels++ != 0)
		return 0;

	err = mlxsw_sp_kvdl_alloc(mlxsw_sp, MLXSW_SP_KVDL_ENTRY_TYPE_ADJ, 1,
				  &nve->tunnel_index);
	if (err)
		goto err_kvdl_alloc;

	ops = nve->nve_ops_arr[config->type];
	err = ops->init(nve, config);
	if (err)
		goto err_ops_init;

	return 0;

err_ops_init:
	mlxsw_sp_kvdl_free(mlxsw_sp, MLXSW_SP_KVDL_ENTRY_TYPE_ADJ, 1,
			   nve->tunnel_index);
err_kvdl_alloc:
	nve->num_nve_tunnels--;
	return err;
}