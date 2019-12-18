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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct mlxsw_sp_nexthop_group {int count; int adj_index_valid; int /*<<< orphan*/  adj_index; scalar_t__ ecmp_size; struct mlxsw_sp_nexthop* nexthops; scalar_t__ sum_norm_weight; int /*<<< orphan*/  gateway; } ;
struct mlxsw_sp_nexthop {scalar_t__ should_offload; scalar_t__ offloaded; int update; } ;
struct mlxsw_sp {TYPE_1__* bus_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_SP_KVDL_ENTRY_TYPE_ADJ ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int mlxsw_sp_adj_index_mass_update (struct mlxsw_sp*,struct mlxsw_sp_nexthop_group*,int /*<<< orphan*/ ,scalar_t__) ; 
 int mlxsw_sp_fix_adj_grp_size (struct mlxsw_sp*,scalar_t__*) ; 
 int mlxsw_sp_kvdl_alloc (struct mlxsw_sp*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_kvdl_free (struct mlxsw_sp*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_nexthop_fib_entries_refresh (struct mlxsw_sp_nexthop_group*) ; 
 int mlxsw_sp_nexthop_fib_entries_update (struct mlxsw_sp*,struct mlxsw_sp_nexthop_group*) ; 
 int /*<<< orphan*/  mlxsw_sp_nexthop_group_normalize (struct mlxsw_sp_nexthop_group*) ; 
 int /*<<< orphan*/  mlxsw_sp_nexthop_group_rebalance (struct mlxsw_sp_nexthop_group*) ; 
 int mlxsw_sp_nexthop_group_update (struct mlxsw_sp*,struct mlxsw_sp_nexthop_group*,int) ; 

__attribute__((used)) static void
mlxsw_sp_nexthop_group_refresh(struct mlxsw_sp *mlxsw_sp,
			       struct mlxsw_sp_nexthop_group *nh_grp)
{
	u16 ecmp_size, old_ecmp_size;
	struct mlxsw_sp_nexthop *nh;
	bool offload_change = false;
	u32 adj_index;
	bool old_adj_index_valid;
	u32 old_adj_index;
	int i;
	int err;

	if (!nh_grp->gateway) {
		mlxsw_sp_nexthop_fib_entries_update(mlxsw_sp, nh_grp);
		return;
	}

	for (i = 0; i < nh_grp->count; i++) {
		nh = &nh_grp->nexthops[i];

		if (nh->should_offload != nh->offloaded) {
			offload_change = true;
			if (nh->should_offload)
				nh->update = 1;
		}
	}
	if (!offload_change) {
		/* Nothing was added or removed, so no need to reallocate. Just
		 * update MAC on existing adjacency indexes.
		 */
		err = mlxsw_sp_nexthop_group_update(mlxsw_sp, nh_grp, false);
		if (err) {
			dev_warn(mlxsw_sp->bus_info->dev, "Failed to update neigh MAC in adjacency table.\n");
			goto set_trap;
		}
		return;
	}
	mlxsw_sp_nexthop_group_normalize(nh_grp);
	if (!nh_grp->sum_norm_weight)
		/* No neigh of this group is connected so we just set
		 * the trap and let everthing flow through kernel.
		 */
		goto set_trap;

	ecmp_size = nh_grp->sum_norm_weight;
	err = mlxsw_sp_fix_adj_grp_size(mlxsw_sp, &ecmp_size);
	if (err)
		/* No valid allocation size available. */
		goto set_trap;

	err = mlxsw_sp_kvdl_alloc(mlxsw_sp, MLXSW_SP_KVDL_ENTRY_TYPE_ADJ,
				  ecmp_size, &adj_index);
	if (err) {
		/* We ran out of KVD linear space, just set the
		 * trap and let everything flow through kernel.
		 */
		dev_warn(mlxsw_sp->bus_info->dev, "Failed to allocate KVD linear area for nexthop group.\n");
		goto set_trap;
	}
	old_adj_index_valid = nh_grp->adj_index_valid;
	old_adj_index = nh_grp->adj_index;
	old_ecmp_size = nh_grp->ecmp_size;
	nh_grp->adj_index_valid = 1;
	nh_grp->adj_index = adj_index;
	nh_grp->ecmp_size = ecmp_size;
	mlxsw_sp_nexthop_group_rebalance(nh_grp);
	err = mlxsw_sp_nexthop_group_update(mlxsw_sp, nh_grp, true);
	if (err) {
		dev_warn(mlxsw_sp->bus_info->dev, "Failed to update neigh MAC in adjacency table.\n");
		goto set_trap;
	}

	if (!old_adj_index_valid) {
		/* The trap was set for fib entries, so we have to call
		 * fib entry update to unset it and use adjacency index.
		 */
		err = mlxsw_sp_nexthop_fib_entries_update(mlxsw_sp, nh_grp);
		if (err) {
			dev_warn(mlxsw_sp->bus_info->dev, "Failed to add adjacency index to fib entries.\n");
			goto set_trap;
		}
		return;
	}

	err = mlxsw_sp_adj_index_mass_update(mlxsw_sp, nh_grp,
					     old_adj_index, old_ecmp_size);
	mlxsw_sp_kvdl_free(mlxsw_sp, MLXSW_SP_KVDL_ENTRY_TYPE_ADJ,
			   old_ecmp_size, old_adj_index);
	if (err) {
		dev_warn(mlxsw_sp->bus_info->dev, "Failed to mass-update adjacency index for nexthop group.\n");
		goto set_trap;
	}

	/* Offload state within the group changed, so update the flags. */
	mlxsw_sp_nexthop_fib_entries_refresh(nh_grp);

	return;

set_trap:
	old_adj_index_valid = nh_grp->adj_index_valid;
	nh_grp->adj_index_valid = 0;
	for (i = 0; i < nh_grp->count; i++) {
		nh = &nh_grp->nexthops[i];
		nh->offloaded = 0;
	}
	err = mlxsw_sp_nexthop_fib_entries_update(mlxsw_sp, nh_grp);
	if (err)
		dev_warn(mlxsw_sp->bus_info->dev, "Failed to set traps for fib entries.\n");
	if (old_adj_index_valid)
		mlxsw_sp_kvdl_free(mlxsw_sp, MLXSW_SP_KVDL_ENTRY_TYPE_ADJ,
				   nh_grp->ecmp_size, nh_grp->adj_index);
}