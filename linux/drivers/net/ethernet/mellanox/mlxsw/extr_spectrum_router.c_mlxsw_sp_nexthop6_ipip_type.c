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
struct mlxsw_sp {int dummy; } ;
struct fib6_info {TYPE_1__* fib6_nh; } ;
typedef  enum mlxsw_sp_ipip_type { ____Placeholder_mlxsw_sp_ipip_type } mlxsw_sp_ipip_type ;
struct TYPE_2__ {scalar_t__ fib_nh_dev; } ;

/* Variables and functions */
 scalar_t__ mlxsw_sp_netdev_ipip_type (struct mlxsw_sp const*,scalar_t__,int*) ; 

__attribute__((used)) static bool mlxsw_sp_nexthop6_ipip_type(const struct mlxsw_sp *mlxsw_sp,
					const struct fib6_info *rt,
					enum mlxsw_sp_ipip_type *ret)
{
	return rt->fib6_nh->fib_nh_dev &&
	       mlxsw_sp_netdev_ipip_type(mlxsw_sp, rt->fib6_nh->fib_nh_dev, ret);
}