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
struct fib_info {TYPE_1__* fib_nh; } ;
struct TYPE_2__ {scalar_t__ nh_scope; } ;

/* Variables and functions */
 scalar_t__ RT_SCOPE_LINK ; 
 scalar_t__ mlxsw_sp_nexthop4_ipip_type (struct mlxsw_sp const*,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool mlxsw_sp_fi_is_gateway(const struct mlxsw_sp *mlxsw_sp,
				   const struct fib_info *fi)
{
	return fi->fib_nh->nh_scope == RT_SCOPE_LINK ||
	       mlxsw_sp_nexthop4_ipip_type(mlxsw_sp, fi->fib_nh, NULL);
}