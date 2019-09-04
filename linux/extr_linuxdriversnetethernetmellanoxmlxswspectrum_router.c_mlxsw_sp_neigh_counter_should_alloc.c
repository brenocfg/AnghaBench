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
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 char* MLXSW_SP_DPIPE_TABLE_NAME_HOST4 ; 
 char* MLXSW_SP_DPIPE_TABLE_NAME_HOST6 ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int devlink_dpipe_table_counter_enabled (struct devlink*,char const*) ; 
 int mlxsw_sp_neigh_entry_type (struct mlxsw_sp_neigh_entry*) ; 
 struct devlink* priv_to_devlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
mlxsw_sp_neigh_counter_should_alloc(struct mlxsw_sp *mlxsw_sp,
				    struct mlxsw_sp_neigh_entry *neigh_entry)
{
	struct devlink *devlink;
	const char *table_name;

	switch (mlxsw_sp_neigh_entry_type(neigh_entry)) {
	case AF_INET:
		table_name = MLXSW_SP_DPIPE_TABLE_NAME_HOST4;
		break;
	case AF_INET6:
		table_name = MLXSW_SP_DPIPE_TABLE_NAME_HOST6;
		break;
	default:
		WARN_ON(1);
		return false;
	}

	devlink = priv_to_devlink(mlxsw_sp->core);
	return devlink_dpipe_table_counter_enabled(devlink, table_name);
}