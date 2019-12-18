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
struct mlxsw_sp_nve_mc_list_key {int dummy; } ;
struct mlxsw_sp_nve_mc_list {int /*<<< orphan*/  ht_node; struct mlxsw_sp_nve_mc_list_key key; int /*<<< orphan*/  records_list; } ;
struct mlxsw_sp_nve {int /*<<< orphan*/  mc_list_ht; } ;
struct mlxsw_sp {struct mlxsw_sp_nve* nve; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct mlxsw_sp_nve_mc_list* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_nve_mc_list*) ; 
 struct mlxsw_sp_nve_mc_list* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_nve_mc_list_ht_params ; 
 int rhashtable_insert_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mlxsw_sp_nve_mc_list *
mlxsw_sp_nve_mc_list_create(struct mlxsw_sp *mlxsw_sp,
			    const struct mlxsw_sp_nve_mc_list_key *key)
{
	struct mlxsw_sp_nve *nve = mlxsw_sp->nve;
	struct mlxsw_sp_nve_mc_list *mc_list;
	int err;

	mc_list = kmalloc(sizeof(*mc_list), GFP_KERNEL);
	if (!mc_list)
		return ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&mc_list->records_list);
	mc_list->key = *key;

	err = rhashtable_insert_fast(&nve->mc_list_ht, &mc_list->ht_node,
				     mlxsw_sp_nve_mc_list_ht_params);
	if (err)
		goto err_rhashtable_insert;

	return mc_list;

err_rhashtable_insert:
	kfree(mc_list);
	return ERR_PTR(err);
}