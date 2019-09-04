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
struct mlxsw_sp_nexthop_group {int count; struct mlxsw_sp_nexthop* nexthops; int /*<<< orphan*/  ecmp_size; int /*<<< orphan*/  adj_index; int /*<<< orphan*/  adj_index_valid; } ;
struct mlxsw_sp_nexthop {scalar_t__ num_adj_entries; scalar_t__ offloaded; struct mlxsw_sp_nexthop_group* nh_grp; } ;

/* Variables and functions */
 int EINVAL ; 

int mlxsw_sp_nexthop_indexes(struct mlxsw_sp_nexthop *nh, u32 *p_adj_index,
			     u32 *p_adj_size, u32 *p_adj_hash_index)
{
	struct mlxsw_sp_nexthop_group *nh_grp = nh->nh_grp;
	u32 adj_hash_index = 0;
	int i;

	if (!nh->offloaded || !nh_grp->adj_index_valid)
		return -EINVAL;

	*p_adj_index = nh_grp->adj_index;
	*p_adj_size = nh_grp->ecmp_size;

	for (i = 0; i < nh_grp->count; i++) {
		struct mlxsw_sp_nexthop *nh_iter = &nh_grp->nexthops[i];

		if (nh_iter == nh)
			break;
		if (nh_iter->offloaded)
			adj_hash_index += nh_iter->num_adj_entries;
	}

	*p_adj_hash_index = adj_hash_index;
	return 0;
}