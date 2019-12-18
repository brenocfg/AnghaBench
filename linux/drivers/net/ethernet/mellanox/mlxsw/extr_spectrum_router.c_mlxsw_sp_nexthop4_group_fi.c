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
struct mlxsw_sp_nexthop_group {struct fib_info* priv; } ;
struct fib_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct fib_info *
mlxsw_sp_nexthop4_group_fi(const struct mlxsw_sp_nexthop_group *nh_grp)
{
	return nh_grp->priv;
}