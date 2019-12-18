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
struct neighbour {int /*<<< orphan*/  dev; } ;
struct mlxsw_sp_rif {int /*<<< orphan*/  neigh_list; int /*<<< orphan*/  rif_index; } ;
struct mlxsw_sp_neigh_entry {int /*<<< orphan*/  rif_list_node; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct mlxsw_sp_neigh_entry* ERR_PTR (int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_neigh_counter_alloc (struct mlxsw_sp*,struct mlxsw_sp_neigh_entry*) ; 
 struct mlxsw_sp_neigh_entry* mlxsw_sp_neigh_entry_alloc (struct mlxsw_sp*,struct neighbour*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_neigh_entry_free (struct mlxsw_sp_neigh_entry*) ; 
 int mlxsw_sp_neigh_entry_insert (struct mlxsw_sp*,struct mlxsw_sp_neigh_entry*) ; 
 struct mlxsw_sp_rif* mlxsw_sp_rif_find_by_dev (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mlxsw_sp_neigh_entry *
mlxsw_sp_neigh_entry_create(struct mlxsw_sp *mlxsw_sp, struct neighbour *n)
{
	struct mlxsw_sp_neigh_entry *neigh_entry;
	struct mlxsw_sp_rif *rif;
	int err;

	rif = mlxsw_sp_rif_find_by_dev(mlxsw_sp, n->dev);
	if (!rif)
		return ERR_PTR(-EINVAL);

	neigh_entry = mlxsw_sp_neigh_entry_alloc(mlxsw_sp, n, rif->rif_index);
	if (!neigh_entry)
		return ERR_PTR(-ENOMEM);

	err = mlxsw_sp_neigh_entry_insert(mlxsw_sp, neigh_entry);
	if (err)
		goto err_neigh_entry_insert;

	mlxsw_sp_neigh_counter_alloc(mlxsw_sp, neigh_entry);
	list_add(&neigh_entry->rif_list_node, &rif->neigh_list);

	return neigh_entry;

err_neigh_entry_insert:
	mlxsw_sp_neigh_entry_free(neigh_entry);
	return ERR_PTR(err);
}