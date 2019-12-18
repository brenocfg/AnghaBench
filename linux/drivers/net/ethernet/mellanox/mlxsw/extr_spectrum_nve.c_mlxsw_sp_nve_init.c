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
struct mlxsw_sp_nve {int /*<<< orphan*/  mc_list_ht; int /*<<< orphan*/  nve_ops_arr; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {struct mlxsw_sp_nve* nve; int /*<<< orphan*/  nve_ops_arr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_nve*) ; 
 struct mlxsw_sp_nve* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mlxsw_sp_nve_ecn_init (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_nve_mc_list_ht_params ; 
 int mlxsw_sp_nve_qos_init (struct mlxsw_sp*) ; 
 int mlxsw_sp_nve_resources_query (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  rhashtable_destroy (int /*<<< orphan*/ *) ; 
 int rhashtable_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int mlxsw_sp_nve_init(struct mlxsw_sp *mlxsw_sp)
{
	struct mlxsw_sp_nve *nve;
	int err;

	nve = kzalloc(sizeof(*mlxsw_sp->nve), GFP_KERNEL);
	if (!nve)
		return -ENOMEM;
	mlxsw_sp->nve = nve;
	nve->mlxsw_sp = mlxsw_sp;
	nve->nve_ops_arr = mlxsw_sp->nve_ops_arr;

	err = rhashtable_init(&nve->mc_list_ht,
			      &mlxsw_sp_nve_mc_list_ht_params);
	if (err)
		goto err_rhashtable_init;

	err = mlxsw_sp_nve_qos_init(mlxsw_sp);
	if (err)
		goto err_nve_qos_init;

	err = mlxsw_sp_nve_ecn_init(mlxsw_sp);
	if (err)
		goto err_nve_ecn_init;

	err = mlxsw_sp_nve_resources_query(mlxsw_sp);
	if (err)
		goto err_nve_resources_query;

	return 0;

err_nve_resources_query:
err_nve_ecn_init:
err_nve_qos_init:
	rhashtable_destroy(&nve->mc_list_ht);
err_rhashtable_init:
	mlxsw_sp->nve = NULL;
	kfree(nve);
	return err;
}