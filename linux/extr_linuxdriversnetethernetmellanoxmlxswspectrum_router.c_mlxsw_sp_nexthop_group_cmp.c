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
struct rhashtable_compare_arg {struct mlxsw_sp_nexthop_group_cmp_arg* key; } ;
struct mlxsw_sp_nexthop_group_cmp_arg {int proto; int /*<<< orphan*/  fib6_entry; int /*<<< orphan*/  fi; } ;
struct mlxsw_sp_nexthop_group {int dummy; } ;

/* Variables and functions */
#define  MLXSW_SP_L3_PROTO_IPV4 129 
#define  MLXSW_SP_L3_PROTO_IPV6 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  mlxsw_sp_nexthop4_group_fi (struct mlxsw_sp_nexthop_group const*) ; 
 int /*<<< orphan*/  mlxsw_sp_nexthop6_group_cmp (struct mlxsw_sp_nexthop_group const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mlxsw_sp_nexthop_group_cmp(struct rhashtable_compare_arg *arg, const void *ptr)
{
	const struct mlxsw_sp_nexthop_group_cmp_arg *cmp_arg = arg->key;
	const struct mlxsw_sp_nexthop_group *nh_grp = ptr;

	switch (cmp_arg->proto) {
	case MLXSW_SP_L3_PROTO_IPV4:
		return cmp_arg->fi != mlxsw_sp_nexthop4_group_fi(nh_grp);
	case MLXSW_SP_L3_PROTO_IPV6:
		return !mlxsw_sp_nexthop6_group_cmp(nh_grp,
						    cmp_arg->fib6_entry);
	default:
		WARN_ON(1);
		return 1;
	}
}