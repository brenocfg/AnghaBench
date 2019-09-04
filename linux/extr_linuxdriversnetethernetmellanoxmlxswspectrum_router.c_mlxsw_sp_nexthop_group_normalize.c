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
struct mlxsw_sp_nexthop_group {int count; int sum_norm_weight; struct mlxsw_sp_nexthop* nexthops; } ;
struct mlxsw_sp_nexthop {int nh_weight; int norm_nh_weight; int /*<<< orphan*/  should_offload; } ;

/* Variables and functions */
 int gcd (int,int) ; 

__attribute__((used)) static void
mlxsw_sp_nexthop_group_normalize(struct mlxsw_sp_nexthop_group *nh_grp)
{
	int i, g = 0, sum_norm_weight = 0;
	struct mlxsw_sp_nexthop *nh;

	for (i = 0; i < nh_grp->count; i++) {
		nh = &nh_grp->nexthops[i];

		if (!nh->should_offload)
			continue;
		if (g > 0)
			g = gcd(nh->nh_weight, g);
		else
			g = nh->nh_weight;
	}

	for (i = 0; i < nh_grp->count; i++) {
		nh = &nh_grp->nexthops[i];

		if (!nh->should_offload)
			continue;
		nh->norm_nh_weight = nh->nh_weight / g;
		sum_norm_weight += nh->norm_nh_weight;
	}

	nh_grp->sum_norm_weight = sum_norm_weight;
}