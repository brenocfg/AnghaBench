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
struct fib_nh {scalar_t__ fib_nh_scope; } ;
struct fib_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ RT_SCOPE_LINK ; 
 struct fib_nh* fib_info_nh (struct fib_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ mlxsw_sp_nexthop4_ipip_type (struct mlxsw_sp const*,struct fib_nh const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool mlxsw_sp_fi_is_gateway(const struct mlxsw_sp *mlxsw_sp,
				   struct fib_info *fi)
{
	const struct fib_nh *nh = fib_info_nh(fi, 0);

	return nh->fib_nh_scope == RT_SCOPE_LINK ||
	       mlxsw_sp_nexthop4_ipip_type(mlxsw_sp, nh, NULL);
}