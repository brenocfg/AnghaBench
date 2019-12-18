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
struct mlxsw_sp_nexthop_group_cmp_arg {struct fib_info* fi; int /*<<< orphan*/  proto; } ;
struct mlxsw_sp_nexthop_group {int dummy; } ;
struct mlxsw_sp {TYPE_1__* router; } ;
struct fib_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nexthop_group_ht; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_SP_L3_PROTO_IPV4 ; 
 int /*<<< orphan*/  mlxsw_sp_nexthop_group_ht_params ; 
 struct mlxsw_sp_nexthop_group* rhashtable_lookup_fast (int /*<<< orphan*/ *,struct mlxsw_sp_nexthop_group_cmp_arg*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mlxsw_sp_nexthop_group *
mlxsw_sp_nexthop4_group_lookup(struct mlxsw_sp *mlxsw_sp,
			       struct fib_info *fi)
{
	struct mlxsw_sp_nexthop_group_cmp_arg cmp_arg;

	cmp_arg.proto = MLXSW_SP_L3_PROTO_IPV4;
	cmp_arg.fi = fi;
	return rhashtable_lookup_fast(&mlxsw_sp->router->nexthop_group_ht,
				      &cmp_arg,
				      mlxsw_sp_nexthop_group_ht_params);
}