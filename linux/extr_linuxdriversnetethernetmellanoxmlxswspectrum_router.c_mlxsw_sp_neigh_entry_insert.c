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
struct mlxsw_sp_neigh_entry {int /*<<< orphan*/  ht_node; } ;
struct mlxsw_sp {TYPE_1__* router; } ;
struct TYPE_2__ {int /*<<< orphan*/  neigh_ht; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_neigh_ht_params ; 
 int rhashtable_insert_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mlxsw_sp_neigh_entry_insert(struct mlxsw_sp *mlxsw_sp,
			    struct mlxsw_sp_neigh_entry *neigh_entry)
{
	return rhashtable_insert_fast(&mlxsw_sp->router->neigh_ht,
				      &neigh_entry->ht_node,
				      mlxsw_sp_neigh_ht_params);
}