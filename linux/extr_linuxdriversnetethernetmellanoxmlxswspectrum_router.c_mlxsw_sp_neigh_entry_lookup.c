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
struct neighbour {int dummy; } ;
struct mlxsw_sp_neigh_key {struct neighbour* n; } ;
struct mlxsw_sp_neigh_entry {int dummy; } ;
struct mlxsw_sp {TYPE_1__* router; } ;
struct TYPE_2__ {int /*<<< orphan*/  neigh_ht; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_neigh_ht_params ; 
 struct mlxsw_sp_neigh_entry* rhashtable_lookup_fast (int /*<<< orphan*/ *,struct mlxsw_sp_neigh_key*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mlxsw_sp_neigh_entry *
mlxsw_sp_neigh_entry_lookup(struct mlxsw_sp *mlxsw_sp, struct neighbour *n)
{
	struct mlxsw_sp_neigh_key key;

	key.n = n;
	return rhashtable_lookup_fast(&mlxsw_sp->router->neigh_ht,
				      &key, mlxsw_sp_neigh_ht_params);
}