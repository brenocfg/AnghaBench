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
struct mlxsw_sp_mr_tcam_route {int /*<<< orphan*/  erif_list; int /*<<< orphan*/  counter_index; int /*<<< orphan*/  afa_block; int /*<<< orphan*/  priv; int /*<<< orphan*/  key; } ;
struct mlxsw_sp_mr_tcam_ops {int /*<<< orphan*/  (* route_destroy ) (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct mlxsw_sp_mr_tcam {int /*<<< orphan*/  priv; } ;
struct mlxsw_sp {struct mlxsw_sp_mr_tcam_ops* mr_tcam_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_flow_counter_free (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_mr_erif_list_flush (struct mlxsw_sp*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_mr_tcam_afa_block_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlxsw_sp_mr_tcam_route_destroy(struct mlxsw_sp *mlxsw_sp,
					   void *priv, void *route_priv)
{
	const struct mlxsw_sp_mr_tcam_ops *ops = mlxsw_sp->mr_tcam_ops;
	struct mlxsw_sp_mr_tcam_route *route = route_priv;
	struct mlxsw_sp_mr_tcam *mr_tcam = priv;

	ops->route_destroy(mlxsw_sp, mr_tcam->priv, route->priv, &route->key);
	kfree(route->priv);
	mlxsw_sp_mr_tcam_afa_block_destroy(route->afa_block);
	mlxsw_sp_flow_counter_free(mlxsw_sp, route->counter_index);
	mlxsw_sp_mr_erif_list_flush(mlxsw_sp, &route->erif_list);
}