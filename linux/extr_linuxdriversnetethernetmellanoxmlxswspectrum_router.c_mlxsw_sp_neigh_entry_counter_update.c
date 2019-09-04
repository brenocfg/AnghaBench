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
struct mlxsw_sp_neigh_entry {int dummy; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_neigh_counter_alloc (struct mlxsw_sp*,struct mlxsw_sp_neigh_entry*) ; 
 int /*<<< orphan*/  mlxsw_sp_neigh_counter_free (struct mlxsw_sp*,struct mlxsw_sp_neigh_entry*) ; 
 int /*<<< orphan*/  mlxsw_sp_neigh_entry_update (struct mlxsw_sp*,struct mlxsw_sp_neigh_entry*,int) ; 

void
mlxsw_sp_neigh_entry_counter_update(struct mlxsw_sp *mlxsw_sp,
				    struct mlxsw_sp_neigh_entry *neigh_entry,
				    bool adding)
{
	if (adding)
		mlxsw_sp_neigh_counter_alloc(mlxsw_sp, neigh_entry);
	else
		mlxsw_sp_neigh_counter_free(mlxsw_sp, neigh_entry);
	mlxsw_sp_neigh_entry_update(mlxsw_sp, neigh_entry, true);
}