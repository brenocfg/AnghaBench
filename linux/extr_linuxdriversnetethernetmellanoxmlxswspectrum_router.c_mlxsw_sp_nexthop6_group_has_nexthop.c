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
struct mlxsw_sp_nexthop_group {int count; struct mlxsw_sp_nexthop* nexthops; } ;
struct mlxsw_sp_nexthop {int ifindex; int nh_weight; scalar_t__ gw_addr; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 scalar_t__ ipv6_addr_equal (struct in6_addr const*,struct in6_addr*) ; 

__attribute__((used)) static bool
mlxsw_sp_nexthop6_group_has_nexthop(const struct mlxsw_sp_nexthop_group *nh_grp,
				    const struct in6_addr *gw, int ifindex,
				    int weight)
{
	int i;

	for (i = 0; i < nh_grp->count; i++) {
		const struct mlxsw_sp_nexthop *nh;

		nh = &nh_grp->nexthops[i];
		if (nh->ifindex == ifindex && nh->nh_weight == weight &&
		    ipv6_addr_equal(gw, (struct in6_addr *) nh->gw_addr))
			return true;
	}

	return false;
}