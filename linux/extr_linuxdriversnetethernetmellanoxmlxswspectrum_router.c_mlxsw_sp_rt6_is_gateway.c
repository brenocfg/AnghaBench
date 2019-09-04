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
struct mlxsw_sp {int dummy; } ;
struct fib6_info {int fib6_flags; } ;

/* Variables and functions */
 int RTF_GATEWAY ; 
 scalar_t__ mlxsw_sp_nexthop6_ipip_type (struct mlxsw_sp const*,struct fib6_info const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool mlxsw_sp_rt6_is_gateway(const struct mlxsw_sp *mlxsw_sp,
				    const struct fib6_info *rt)
{
	return rt->fib6_flags & RTF_GATEWAY ||
	       mlxsw_sp_nexthop6_ipip_type(mlxsw_sp, rt, NULL);
}