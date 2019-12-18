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
struct mlxsw_sp_nve_mc_list {int /*<<< orphan*/  records_list; int /*<<< orphan*/  ht_node; } ;
struct mlxsw_sp_nve {int /*<<< orphan*/  mc_list_ht; } ;
struct mlxsw_sp {struct mlxsw_sp_nve* nve; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_nve_mc_list*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_nve_mc_list_ht_params ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_sp_nve_mc_list_destroy(struct mlxsw_sp *mlxsw_sp,
					 struct mlxsw_sp_nve_mc_list *mc_list)
{
	struct mlxsw_sp_nve *nve = mlxsw_sp->nve;

	rhashtable_remove_fast(&nve->mc_list_ht, &mc_list->ht_node,
			       mlxsw_sp_nve_mc_list_ht_params);
	WARN_ON(!list_empty(&mc_list->records_list));
	kfree(mc_list);
}