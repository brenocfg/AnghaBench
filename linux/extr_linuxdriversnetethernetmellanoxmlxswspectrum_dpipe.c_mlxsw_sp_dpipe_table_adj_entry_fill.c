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
typedef  int /*<<< orphan*/  u32 ;
struct mlxsw_sp_rif {int dummy; } ;
struct mlxsw_sp_nexthop {int dummy; } ;
struct mlxsw_sp {int dummy; } ;
struct devlink_dpipe_entry {int counter_valid; int /*<<< orphan*/  counter; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mlxsw_sp_dpipe_table_adj_entry_fill (struct devlink_dpipe_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,struct mlxsw_sp_rif*) ; 
 int mlxsw_sp_nexthop_counter_get (struct mlxsw_sp*,struct mlxsw_sp_nexthop*,int /*<<< orphan*/ *) ; 
 unsigned char* mlxsw_sp_nexthop_ha (struct mlxsw_sp_nexthop*) ; 
 int /*<<< orphan*/  mlxsw_sp_nexthop_indexes (struct mlxsw_sp_nexthop*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct mlxsw_sp_rif* mlxsw_sp_nexthop_rif (struct mlxsw_sp_nexthop*) ; 

__attribute__((used)) static void mlxsw_sp_dpipe_table_adj_entry_fill(struct mlxsw_sp *mlxsw_sp,
						struct mlxsw_sp_nexthop *nh,
						struct devlink_dpipe_entry *entry)
{
	struct mlxsw_sp_rif *rif = mlxsw_sp_nexthop_rif(nh);
	unsigned char *ha = mlxsw_sp_nexthop_ha(nh);
	u32 adj_hash_index = 0;
	u32 adj_index = 0;
	u32 adj_size = 0;
	int err;

	mlxsw_sp_nexthop_indexes(nh, &adj_index, &adj_size, &adj_hash_index);
	__mlxsw_sp_dpipe_table_adj_entry_fill(entry, adj_index, adj_size,
					      adj_hash_index, ha, rif);
	err = mlxsw_sp_nexthop_counter_get(mlxsw_sp, nh, &entry->counter);
	if (!err)
		entry->counter_valid = true;
}