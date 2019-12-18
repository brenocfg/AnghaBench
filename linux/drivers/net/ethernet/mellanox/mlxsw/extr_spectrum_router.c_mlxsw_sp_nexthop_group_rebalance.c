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
typedef  int u16 ;
struct mlxsw_sp_nexthop_group {int sum_norm_weight; int ecmp_size; int count; struct mlxsw_sp_nexthop* nexthops; } ;
struct mlxsw_sp_nexthop {int num_adj_entries; scalar_t__ norm_nh_weight; int /*<<< orphan*/  should_offload; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (int,int) ; 

__attribute__((used)) static void
mlxsw_sp_nexthop_group_rebalance(struct mlxsw_sp_nexthop_group *nh_grp)
{
	int total = nh_grp->sum_norm_weight;
	u16 ecmp_size = nh_grp->ecmp_size;
	int i, weight = 0, lower_bound = 0;

	for (i = 0; i < nh_grp->count; i++) {
		struct mlxsw_sp_nexthop *nh = &nh_grp->nexthops[i];
		int upper_bound;

		if (!nh->should_offload)
			continue;
		weight += nh->norm_nh_weight;
		upper_bound = DIV_ROUND_CLOSEST(ecmp_size * weight, total);
		nh->num_adj_entries = upper_bound - lower_bound;
		lower_bound = upper_bound;
	}
}