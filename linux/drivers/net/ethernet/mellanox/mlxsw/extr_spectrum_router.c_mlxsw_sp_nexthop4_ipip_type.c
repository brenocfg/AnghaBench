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
struct net_device {int dummy; } ;
struct mlxsw_sp {int dummy; } ;
struct fib_nh {TYPE_1__* nh_parent; struct net_device* fib_nh_dev; } ;
typedef  enum mlxsw_sp_ipip_type { ____Placeholder_mlxsw_sp_ipip_type } mlxsw_sp_ipip_type ;
struct TYPE_2__ {scalar_t__ fib_type; } ;

/* Variables and functions */
 scalar_t__ RTN_UNICAST ; 
 scalar_t__ mlxsw_sp_netdev_ipip_type (struct mlxsw_sp const*,struct net_device*,int*) ; 

__attribute__((used)) static bool mlxsw_sp_nexthop4_ipip_type(const struct mlxsw_sp *mlxsw_sp,
					const struct fib_nh *fib_nh,
					enum mlxsw_sp_ipip_type *p_ipipt)
{
	struct net_device *dev = fib_nh->fib_nh_dev;

	return dev &&
	       fib_nh->nh_parent->fib_type == RTN_UNICAST &&
	       mlxsw_sp_netdev_ipip_type(mlxsw_sp, dev, p_ipipt);
}