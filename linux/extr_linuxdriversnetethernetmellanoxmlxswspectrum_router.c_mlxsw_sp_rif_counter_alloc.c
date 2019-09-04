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
typedef  enum mlxsw_sp_rif_counter_dir { ____Placeholder_mlxsw_sp_rif_counter_dir } mlxsw_sp_rif_counter_dir ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MLXSW_SP_COUNTER_SUB_POOL_RIF ; 
 int mlxsw_sp_counter_alloc (struct mlxsw_sp*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  mlxsw_sp_counter_free (struct mlxsw_sp*,int /*<<< orphan*/ ,unsigned int) ; 
 int mlxsw_sp_rif_counter_clear (struct mlxsw_sp*,unsigned int) ; 
 int mlxsw_sp_rif_counter_edit (struct mlxsw_sp*,int /*<<< orphan*/ ,unsigned int,int,int) ; 
 int /*<<< orphan*/  mlxsw_sp_rif_counter_valid_set (struct mlxsw_sp_rif*,int,int) ; 
 unsigned int* mlxsw_sp_rif_p_counter_get (struct mlxsw_sp_rif*,int) ; 

int mlxsw_sp_rif_counter_alloc(struct mlxsw_sp *mlxsw_sp,
			       struct mlxsw_sp_rif *rif,
			       enum mlxsw_sp_rif_counter_dir dir)
{
	unsigned int *p_counter_index;
	int err;

	p_counter_index = mlxsw_sp_rif_p_counter_get(rif, dir);
	if (!p_counter_index)
		return -EINVAL;
	err = mlxsw_sp_counter_alloc(mlxsw_sp, MLXSW_SP_COUNTER_SUB_POOL_RIF,
				     p_counter_index);
	if (err)
		return err;

	err = mlxsw_sp_rif_counter_clear(mlxsw_sp, *p_counter_index);
	if (err)
		goto err_counter_clear;

	err = mlxsw_sp_rif_counter_edit(mlxsw_sp, rif->rif_index,
					*p_counter_index, true, dir);
	if (err)
		goto err_counter_edit;
	mlxsw_sp_rif_counter_valid_set(rif, dir, true);
	return 0;

err_counter_edit:
err_counter_clear:
	mlxsw_sp_counter_free(mlxsw_sp, MLXSW_SP_COUNTER_SUB_POOL_RIF,
			      *p_counter_index);
	return err;
}