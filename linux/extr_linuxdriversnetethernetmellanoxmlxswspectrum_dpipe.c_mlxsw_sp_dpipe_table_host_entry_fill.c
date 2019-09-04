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
struct mlxsw_sp_rif {int dummy; } ;
struct mlxsw_sp_neigh_entry {int dummy; } ;
struct mlxsw_sp {int dummy; } ;
struct devlink_dpipe_entry {int counter_valid; int /*<<< orphan*/  counter; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  mlxsw_sp_dpipe_table_host4_entry_fill (struct devlink_dpipe_entry*,struct mlxsw_sp_neigh_entry*,struct mlxsw_sp_rif*) ; 
 int /*<<< orphan*/  mlxsw_sp_dpipe_table_host6_entry_fill (struct devlink_dpipe_entry*,struct mlxsw_sp_neigh_entry*,struct mlxsw_sp_rif*) ; 
 int mlxsw_sp_neigh_counter_get (struct mlxsw_sp*,struct mlxsw_sp_neigh_entry*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlxsw_sp_dpipe_table_host_entry_fill(struct mlxsw_sp *mlxsw_sp,
				     struct devlink_dpipe_entry *entry,
				     struct mlxsw_sp_neigh_entry *neigh_entry,
				     struct mlxsw_sp_rif *rif,
				     int type)
{
	int err;

	switch (type) {
	case AF_INET:
		mlxsw_sp_dpipe_table_host4_entry_fill(entry, neigh_entry, rif);
		break;
	case AF_INET6:
		mlxsw_sp_dpipe_table_host6_entry_fill(entry, neigh_entry, rif);
		break;
	default:
		WARN_ON(1);
		return;
	}

	err = mlxsw_sp_neigh_counter_get(mlxsw_sp, neigh_entry,
					 &entry->counter);
	if (!err)
		entry->counter_valid = true;
}